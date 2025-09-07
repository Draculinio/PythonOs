# free

✅ **Status:** Working  

The `free` command releases a previously allocated block of memory back to the heap.  
Internally, it inserts the block into the free list and attempts to coalesce adjacent free blocks to reduce fragmentation.

---

## Usage

free <address>

- `<address>` → memory address returned by a previous `malloc` call.

---

## Example

malloc 128

Allocated 128 bytes at 0x1000

free 0x1000

Freed 128 bytes

---

## Details

- A block header is stored right before the payload of every allocated block.  
- When `free` is called, the allocator moves back from the payload pointer to locate the header.  
- The block is then inserted into the free list.  
- If adjacent blocks are also free, they are merged (*coalesced*) to form a larger free block, reducing fragmentation.

---

## When to use

- To release memory no longer needed.  
- To keep the heap healthy and avoid running out of space.  
- To reduce fragmentation by allowing the allocator to reuse blocks.

---

## See also

- [malloc](malloc.md)  
- [meminfo](meminfo.md)  
- [dump_heap_visual](dump_heap_visual.md)  