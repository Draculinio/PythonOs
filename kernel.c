// Dirección base del buffer de video
#define VIDEO_MEMORY (char*)0xb8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void clear_screen() {
    char *video = VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video[i * 2] = ' ';      // espacio
        video[i * 2 + 1] = 0x07; // atributo: blanco sobre negro
    }
}

void kernel_main(void) {
    clear_screen();

    const char *msg = "Welcome to the Pythonist OS!";
    char *video = VIDEO_MEMORY;

    for (int i = 0; msg[i] != '\0'; i++) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }

    while (1); // loop infinito
}
