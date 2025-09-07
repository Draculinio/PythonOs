# malloc

✅ **Status:** Working  

The `malloc` command allocates a block of memory from the heap.  
It first tries to reuse a free block, and if none is available, it grows the heap using bump allocation.

---

## Usage

malloc <size>

- `<size>` → number of bytes to allocate.

---

## Example

malloc 128

Allocated 128 bytes at 0x1000

If there is not enough memory:

malloc 4096

Out of memory!

---

## Details

Allocation works in two stages:

1. **Free list allocation** – reuse a suitable free block if available.  
2. **Bump allocation** – if not, allocate from the current bump pointer until heap end.

Each allocated block has a header storing metadata (size, next pointer).  

---

## When to use

- To dynamically reserve memory for buffers or data structures.  
- To test and debug the heap manager.

---

## See also

- [free](free.md)  
- [meminfo](meminfo.md)  
- [dump](dump.md)  