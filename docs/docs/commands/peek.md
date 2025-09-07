# peek

✅ **Status:** Working  

Reads an integer value directly from a given memory address.
This command is intended as a low-level memory inspection tool and should be used with caution.

---

## Usage

peek <address>

- `<address>` → The memory address to read from in decimal


---

## Example

peek 123

---

## Notes

* The address must point to a valid memory location.

* Using an invalid address may cause undefined behavior or crash the system.

* Useful for debugging and inspecting allocated memory.

---

## See also

- [peek](peek.md)  
- [dump](dump.md)  
