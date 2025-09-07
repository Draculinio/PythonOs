# dump

The `dump` command inspects the current state of the heap memory.  
It prints useful information about memory management at runtime.

---

## Details

When executed, `dump` shows:

- **Heap start** → the starting address of the heap.
- **Current pointer** → the current position where the next allocation will occur.
- **Heap end** → the maximum heap boundary.
- **Used bytes** → total memory allocated so far.
- **Free bytes** → remaining memory available for future allocations.

This command is especially useful for debugging memory management, since it gives a snapshot of memory usage and availability.

---

## Example Output

Heap map:
start : 1000
current : 1200
end : 2000
used : 200 bytes
free : 800 bytes

---

---

## When to use

Use `dump` to:

- Debug allocation issues.
- Detect potential memory leaks.
- Monitor how your OS memory manager is working internally.