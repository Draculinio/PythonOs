# meminfo

✅ **Status:** Working  

The `meminfo` command provides a detailed overview of the heap memory usage.  
Unlike `dump`, which only reports start, current, and end, `meminfo` also accounts for free blocks inside the free list, giving a more accurate picture of memory usage.

---

## Details

- **Heap total** → the total heap size in bytes.  
- **Bumped** → the offset from the start of the heap to the current allocation pointer (how much memory has been "bumped" forward).  
- **Free list** → total number of bytes currently available for reuse (freed blocks).  
- **Used (approx)** → estimated memory in use, calculated as `bumped - free_list`.

This makes `meminfo` especially useful for understanding fragmentation and memory efficiency in the OS.

---

## Example Output

Heap total: 4096 bytes
Bumped: 1024 bytes
Free list: 512 bytes
Used (approx): 512 bytes

---

## When to use

- To analyze memory fragmentation.  
- To debug allocation/free behavior.  
- To compare actual memory use versus available free list space.  