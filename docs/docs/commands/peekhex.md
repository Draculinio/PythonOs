# peek

✅ **Status:** Working  

Reads an integer value directly from a memory address provided in hexadecimal format.
This command is identical to peek, but it expects the address as hexadecimal instead of decimal.

---

## Usage

peekHex <hex_address>

- `<hex_address>` → The memory address to read from, written in hexadecimal (must start with 0x).


---

## Example

peekHex 0x1000

---

## Notes

* If you prefer decimal addresses, use peek.

* Both commands return the integer stored at the given memory address.

* Using an invalid address may cause undefined behavior or system crash.

---

## See also

- [peek](peek.md)  
- [dump](dump.md)  
