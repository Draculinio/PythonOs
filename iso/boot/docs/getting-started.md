# Getting Started

This guide will help you build and run **Python OS** on your machine.  
No prior experience with operating systems is required — just some command line skills and curiosity.

---

## 🛠️ Requirements

Before building, make sure you have the following installed:

- **GNU Make**  
- **GCC cross-compiler (i386-elf)**  
- **NASM assembler**  
- **QEMU** (to run the OS)  
- **GRUB utilities** (for generating boot images)

> On Linux, most of these can be installed with your package manager.  
> On macOS, use [Homebrew](https://brew.sh/).  
> On Windows, consider using WSL2.

---

## 📦 Clone the repository

```bash
git clone https://github.com/yourusername/python-os.git
cd python-os
make
```

This will:

1. Compile the assembly and C sources.
2. Link everything into a kernel binary.
3. Generate a bootable ISO with GRUB.
4. The resulting ISO will be placed in the build/ folder.

## ▶️ Run in QEMU

```bash
make run
```

This will start QEMU and boot into Python OS.
You should see the kernel message and interact with the system console.

## 🧹 Clean up

If you want to rebuild from scratch:

```bash
make clean
```

## ✅ Next Steps

* Read the Architecture Overview to understand the code layout.
* Explore the source and try editing something small (like the welcome message).
* Contribute or fork to make your own version!