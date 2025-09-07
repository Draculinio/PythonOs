# poke

✅ **Status:** Working  

The `poke` command writes a given integer directly into a specified memory address.  
It’s a low-level debugging tool that allows direct manipulation of memory.

---

## Usage

poke <address> <value>


- `<address>` → memory address to modify.  
- `<value>` → integer value to write at that address.

---

## Example

poke 0x1000 123

Wrote value 123 at address 0x1000


---

## Details

- Internally casts the given address to an `int*` and writes the value.  
- There are **no safety checks** — writing to invalid or protected memory can corrupt the system or cause crashes.  
- Primarily intended for testing and debugging memory-related behavior.

---

## When to use

- To experiment with direct memory manipulation.  
- For low-level debugging of data structures or allocations.  
- To inspect how the OS reacts to changes in raw memory.

---

## Warning ⚠️

Use with extreme caution.  
Unlike `malloc` or `free`, this command bypasses all safety mechanisms. Writing into the wrong address can destabilize the entire system.

---

## See also

- [peek](peek.md)  
- [dump](dump.md)  
