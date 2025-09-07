# gdump

The `gdump` command provides a graphical-style view of the heap memory.  
Instead of showing numeric values, it prints a bar made of characters that represent used and free memory blocks.

---

## Details

- **`#` (hash)** → represents memory already used/allocated.  
- **`.` (dot)** → represents free memory still available.  
- The output is scaled, showing progress in chunks (32 bytes per symbol).

This makes it easier to get an at-a-glance idea of how much memory is currently consumed.

---

## Example Output

Heap: [#####..............]

In this example:
- The left side (`#####`) means those segments are used.
- The right side (`..............`) means they are free.

---

## Status

⚠️ This command is still experimental and may not always show accurate results. It should not be fully relied upon for debugging, but it can serve as a quick visual indicator of heap usage.
