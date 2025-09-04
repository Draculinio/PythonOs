#include "memory.h"
#include "video.h"   // print, print_color, print_int

// Alineamos a 8 bytes para mantener cabeceras bien ubicadas
#define ALIGN        8u
#define ALIGN_UP(x)  (((x) + (ALIGN-1)) & ~(ALIGN-1))

typedef struct block_header {
    uint32_t size;                 // tamaño útil del payload (ya alineado)
    struct block_header* next;     // siguiente en la free list
} block_header;

static uint32_t heap_start;
static uint32_t heap_end;
static uint32_t current;           // bump ptr (tope alcanzado)
static block_header* free_list = 0;

// Helpers para aritmética de punteros
static inline uint8_t* ptr_add(void* p, uint32_t off) {
    return (uint8_t*)p + off;
}
static inline uint32_t hdr_total_size(block_header* h) {
    return (uint32_t)(sizeof(block_header)) + h->size;
}

// Inserta un bloque a la free list manteniéndola ordenada por dirección
// y coalesce con vecinos contiguos si corresponde.
static void freelist_insert_and_coalesce(block_header* blk) {
    if (!blk) return;
    blk->next = 0;

    // Caso lista vacía
    if (!free_list) {
        free_list = blk;
        return;
    }

    block_header* prev = 0;
    block_header* curr = free_list;

    // Insertar ordenado por dirección
    while (curr && curr < blk) {
        prev = curr;
        curr = curr->next;
    }
    // Enlazar
    blk->next = curr;
    if (prev) {
        prev->next = blk;
    } else {
        free_list = blk;
    }

    // Intentar coalescer con "next"
    if (blk->next) {
        uint8_t* blk_end = ptr_add(blk, hdr_total_size(blk));
        if (blk_end == (uint8_t*)blk->next) {
            // fusionar blk y blk->next
            blk->size += sizeof(block_header) + blk->next->size;
            blk->next = blk->next->next;
        }
    }

    // Intentar coalescer con "prev"
    if (prev) {
        uint8_t* prev_end = ptr_add(prev, hdr_total_size(prev));
        if (prev_end == (uint8_t*)blk) {
            // fusionar prev y blk (ya fusionado con next si correspondía)
            prev->size += sizeof(block_header) + blk->size;
            prev->next = blk->next;
        }
    }
}

void memory_init(uint32_t start, uint32_t size) {
    heap_start = ALIGN_UP(start);
    heap_end = start + size;
    heap_end = heap_end & ~(ALIGN-1); // asegurar múltiplo de 8
    current    = heap_start;
    free_list  = 0;
}

static void* alloc_from_freelist(uint32_t need) {
    block_header* prev = 0;
    block_header* curr = free_list;

    while (curr) {
        if (curr->size >= need) {
            // ¿Conviene partir el bloque?
            uint32_t remain = curr->size - need;
            if (remain >= (uint32_t)(sizeof(block_header) + ALIGN)) {
                // Split: dejamos curr con 'need' y creamos un bloque libre con el resto
                uint8_t* payload = ptr_add(curr, sizeof(block_header));
                block_header* newblk = (block_header*)ptr_add(payload, need);
                newblk->size = remain - sizeof(block_header);
                newblk->next = curr->next;

                // curr pasa a estar "asignado" (ya no en free list)
                curr->size = need;
                if (prev) prev->next = newblk; else free_list = newblk;
            } else {
                // Tomamos el bloque entero sin split
                if (prev) prev->next = curr->next; else free_list = curr->next;
            }
            return ptr_add(curr, sizeof(block_header)); // payload
        }
        prev = curr;
        curr = curr->next;
    }
    return 0; // no hay bloque libre suficientemente grande
}

void* kmalloc(size_t size) {
    if (!size) return 0;

    uint32_t need = ALIGN_UP((uint32_t)size);

    // 1) Intentar reutilizar un bloque libre
    void* from_free = alloc_from_freelist(need);
    if (from_free) return from_free;

    // 2) Crecer por bump
    uint32_t hdr_addr = ALIGN_UP(current);
    uint32_t total    = sizeof(block_header) + need;

    if (hdr_addr + total > heap_end) {
        print_color("Out of memory!\n", RED_ON_BLACK);
        return 0;
    }

    block_header* hdr = (block_header*)hdr_addr;
    hdr->size = need;
    hdr->next = 0;

    current = hdr_addr + total;
    return ptr_add(hdr, sizeof(block_header)); // payload
}

uint32_t kfree(void* ptr) {
    if (!ptr) return 0;
    block_header* hdr = (block_header*)((uint8_t*)ptr - sizeof(block_header));
    uint32_t size = hdr->size;
    // Insertar y coalescer en la freelist
    freelist_insert_and_coalesce(hdr);
    return size;
}

void meminfo() {
    uint32_t total      = heap_end - heap_start;
    uint32_t bumped     = current - heap_start;

    // Sumar bytes libres en freelist
    uint32_t free_bytes = 0;
    for (block_header* it = free_list; it; it = it->next) {
        free_bytes += it->size;
    }

    uint32_t used = (bumped >= free_bytes) ? (bumped - free_bytes) : 0;

    print_color("Heap total: ", GREEN_ON_BLACK);
    print_int((int)total);
    print_color(" bytes\nBumped: ", GREEN_ON_BLACK);
    print_int((int)bumped);
    print_color(" bytes\nFree list: ", GREEN_ON_BLACK);
    print_int((int)free_bytes);
    print_color(" bytes\nUsed (approx): ", GREEN_ON_BLACK);
    print_int((int)used);
    print("\n");
}

void dump_heap() {
    print("Heap map:\n");
    print("  start   : ");
    print_int(heap_start);
    print("\n");

    print("  current : ");
    print_int(current);

    print("  end     : ");
    print_int(heap_end);
    print("\n");

    uint32_t used = (uint32_t)current - (uint32_t)heap_start;
    uint32_t free = (uint32_t)heap_end - (uint32_t)current;

    print("  used    : ");
    print_int(used);
    print(" bytes\n");
    print("  free    : ");
    print_int(free);
    print(" bytes\n");

}

void dump_heap_visual() {
    uint32_t total = (uint32_t)heap_end - (uint32_t)heap_start;
    uint32_t used  = (uint32_t)current - (uint32_t)heap_start;

    print("Heap: [");
    for (uint32_t i = 0; i < total; i += 32) {
        if (i < used)
            print("#");  // ocupado
        else
            print(".");  // libre
    }
    print("]\n");
}

//----

// Añadir estas funciones a tu memory.c

// Verifica si una dirección está dentro de algún bloque libre
static int is_in_free_block(uint32_t addr) {
    for (block_header* blk = free_list; blk; blk = blk->next) {
        uint32_t blk_start = (uint32_t)blk;
        uint32_t blk_end = blk_start + sizeof(block_header) + blk->size;
        
        if (addr >= blk_start && addr < blk_end) {
            return 1;
        }
    }
    return 0;
}

// Determina el estado de un bloque de memoria
static char get_memory_state(uint32_t offset) {
    uint32_t addr = heap_start + offset;
    uint32_t used_boundary = current;
    
    if (addr >= used_boundary) {
        return '.';  // Memoria virgen (nunca bumpeada)
    } else if (is_in_free_block(addr)) {
        return 'F';  // Liberada y reutilizable
    } else {
        return '#';  // Actualmente asignada
    }
}

void dump_heap_visual_detailed() {
    uint32_t total = heap_end - heap_start;
    uint32_t bumped = current - heap_start;
    
    const uint32_t BLOCK_SIZE = 32;  // bytes por carácter
    const uint32_t WIDTH = 64;       // caracteres por línea
    
    print_color("=== HEAP VISUALIZATION ===\n", CYAN_ON_BLACK);
    print_color("Legend: ", WHITE_ON_BLACK);
    print_color("#", GREEN_ON_BLACK);
    print_color(" = Allocated, ", WHITE_ON_BLACK);
    print_color("F", YELLOW_ON_BLACK);
    print_color(" = Freed (reusable), ", WHITE_ON_BLACK);
    print_color(".", BLUE_ON_BLACK);
    print_color(" = Virgin memory\n", WHITE_ON_BLACK);
    print("Each character = ");
    print_int(BLOCK_SIZE);
    print(" bytes\n\n");
    
    // Contar estados para estadísticas
    uint32_t allocated_count = 0;
    uint32_t freed_count = 0;
    uint32_t virgin_count = 0;
    
    for (uint32_t i = 0; i < total; i += BLOCK_SIZE) {
        char state = get_memory_state(i);
        switch(state) {
            case '#': allocated_count++; break;
            case 'F': freed_count++; break;
            case '.': virgin_count++; break;
        }
    }
    
    // Mostrar estadísticas
    print_color("Stats: ", WHITE_ON_BLACK);
    print_color("Allocated=", GREEN_ON_BLACK);
    print_int(allocated_count);
    print_color(", Freed=", YELLOW_ON_BLACK);
    print_int(freed_count);
    print_color(", Virgin=", BLUE_ON_BLACK);
    print_int(virgin_count);
    print("\n");
    
    print("Bump pointer at: ");
    print_int((int)((float)bumped * 100.0 / total));
    print("% of heap\n\n");
    
    // Visualización con colores
    uint32_t chars_printed = 0;
    for (uint32_t i = 0; i < total; i += BLOCK_SIZE) {
        char state = get_memory_state(i);
        
        switch(state) {
            case '#': 
                print_color("#", GREEN_ON_BLACK);
                break;
            case 'F': 
                print_color("F", YELLOW_ON_BLACK);
                break;
            case '.': 
                print_color(".", BLUE_ON_BLACK);
                break;
        }
        
        chars_printed++;
        if (chars_printed % WIDTH == 0) {
            print_color("  ", WHITE_ON_BLACK);
            print_int(heap_start + i);
            print("\n");
        }
    }
    
    if (chars_printed % WIDTH != 0) {
        print("\n");
    }
    
    print_color("\nBoundaries:\n", WHITE_ON_BLACK);
    print("  Start:       ");
    print_int(heap_start);
    print("\n  Current:     ");
    print_int(current);
    print(" (bump ptr)\n  End:         ");
    print_int(heap_end);
    print("\n");
}

// Función para mostrar detalles de la free list
void dump_free_list() {
    print_color("=== FREE LIST DETAILS ===\n", CYAN_ON_BLACK);
    
    if (!free_list) {
        print_color("Free list is empty\n", RED_ON_BLACK);
        return;
    }
    
    int count = 0;
    uint32_t total_free = 0;
    
    for (block_header* blk = free_list; blk; blk = blk->next) {
        count++;
        total_free += blk->size;
        
        print_color("Block ", WHITE_ON_BLACK);
        print_int(count);
        print(": addr=");
        print_int((uint32_t)blk);
        print(", payload_size=");
        print_int(blk->size);
        print(" bytes");
        
        // Mostrar si está coalescido calculando distancias
        if (blk->next) {
            uint32_t this_end = (uint32_t)blk + sizeof(block_header) + blk->size;
            uint32_t next_start = (uint32_t)blk->next;
            if (this_end == next_start) {
                print_color(" [COULD COALESCE!]", RED_ON_BLACK);
            }
        }
        print("\n");
    }
    
    print_color("Total: ", WHITE_ON_BLACK);
    print_int(count);
    print(" blocks, ");
    print_int(total_free);
    print(" bytes free\n");
}

// Versión compacta para uso frecuente
void dump_heap_compact() {
    uint32_t total = heap_end - heap_start;
    uint32_t bumped = current - heap_start;
    
    // Calcular bytes realmente libres en free_list
    uint32_t free_bytes = 0;
    for (block_header* blk = free_list; blk; blk = blk->next) {
        free_bytes += blk->size;
    }
    
    uint32_t allocated = bumped - free_bytes;
    
    print_color("Heap: ", WHITE_ON_BLACK);
    print_int(allocated);
    print("/");
    print_int(total);
    print(" bytes (");
    print_int((int)((float)allocated * 100.0 / total));
    print("% used) | Free blocks: ");
    print_int(free_bytes);
    print(" bytes\n");
    
    // Barra de progreso simple
    const int BAR_WIDTH = 50;
    int used_chars = (allocated * BAR_WIDTH) / total;
    int free_chars = (free_bytes * BAR_WIDTH) / total;
    int virgin_chars = BAR_WIDTH - used_chars - free_chars;
    
    print("[");
    
    // Parte asignada
    for (int i = 0; i < used_chars; i++) {
        print_color("#", GREEN_ON_BLACK);
    }
    
    // Parte libre (reutilizable)
    for (int i = 0; i < free_chars; i++) {
        print_color("F", YELLOW_ON_BLACK);
    }
    
    // Parte virgen
    for (int i = 0; i < virgin_chars; i++) {
        print_color(".", BLUE_ON_BLACK);
    }
    
    print_color("]\n", WHITE_ON_BLACK);
}

int* alloc_int(int value) {
    int* p = (int*)kmalloc(sizeof(int));
    if (!p) {
        print_color("alloc_int failed\n", RED_ON_BLACK);
        return 0;
    }
    *p = value;
    return p;
}

//writes a value at a given address
void poke(uint32_t addr, int value){
    int *p = (int*)addr;
    *p = value;
}

int peek(uint32_t addr){
    int *p = (int*)addr;
    return *p;
}