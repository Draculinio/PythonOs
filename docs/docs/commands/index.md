# Command Index

Below is a list of available (and planned) commands in Python OS.  
This list will grow as the system evolves.

| Command     | Description                       | Status      |
|-------------|-----------------------------------|-------------|
| [help](help.md)      | Show list of available commands   | ✅ working  |
| [clear](clear.md)     | Clear the screen                 | ✅ working  |
| [dump](dump.md)     | Displays the current heap state: start, current pointer, end, used, and free memory. | ✅ working  |
| [gdump](gdump.md)     | Displays a visual representation of the heap usage (experimental). | 🔄 partial  |
| [version](version.md)      | Prints the current PythonOS version   | ✅ working  |
| [meminfo](meminfo.md)      | Shows detailed heap statistics: total, bumped, free list, and approximate used memory      | ✅ working  |
| [malloc](malloc.md)      | Allocates a block of memory: `malloc <size>`             | ✅ working |
| [free](free.md)      | Frees a previously allocated block: `free <address>`             | ✅ working |
| [allocInt](allocInt.md)      | Allocates an integer on the heap and initializes it with a value: `allocInt <value>` | ✅ working |
| [poke](poke.md)      | Writes an integer value directly into a memory address: `poke <address> <value>` | ✅ working |
| [peek](peek.md)      | Reads an integer value directly from a given memory address | ✅ working |
| [peekHex](peekhex.md)      | Reads an integer value directly from a given memory address (in hexadecimal) | ✅ working |
| `reboot`    | Reboot the system                 | ⬜ planned  |
| `time`      | Display system uptime             | ⬜ planned  |
