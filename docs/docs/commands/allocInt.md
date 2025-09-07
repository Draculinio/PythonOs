# allocInt

✅ **Status:** Working  

The `allocInt` command allocates space for a single integer on the heap and initializes it with the given value.  
It’s essentially a specialized version of `malloc` for integers.

---

## Usage

allocInt <value>

- `<value>` → integer to be stored in the allocated memory.

---

## Example

allocInt 42

Allocated int at 0x1000 with value = 42

If allocation fails:

allocInt 99

alloc_int failed


---

## Details

- Internally calls `malloc(sizeof(int))`.  
- If allocation succeeds, the memory is filled with the provided value.  
- If the heap is exhausted, the command prints an error and returns `0`.

---

## When to use

- To test heap allocation with a simple, typed object.  
- For quick experiments with dynamic integers.  
- As a building block for higher-level data structures.

---

## See also

- [malloc](malloc.md)  
- [free](free.md)  
- [meminfo](meminfo.md)  
