# KFS-1 (Kernel From Scratch 1)

KFS-1 is a project from 42 School that introduces the fundamentals of operating system development.
The goal of this project is to create a basic x86 kernel from scratch, capable of booting via GRUB, handling the VGA text buffer, and providing a foundational I/O interface.

## 🚀 Features

### Mandatory
* **Custom Bootloader Configuration**: Fully Multiboot compliant, booted via GRUB.
* **Memory Management**: Custom Linker Script (`linker.ld`) to map the kernel correctly into memory starting at `1MB`.
* **VGA Text Mode**: Direct manipulation of the VGA text buffer (`0xB8000`) to output characters to the screen without relying on standard C libraries.
* **Display**: Prints `"42"` to the screen as proof of successful execution.

### Bonus
* **Hardware Cursor Support**: Direct communication with VGA controller registers via I/O ports (`outb`) to display and update the blinking hardware cursor.
* **Screen Scrolling**: Memory-shifting implementation that shifts the screen upwards and clears the last line when the terminal reaches the bottom of the screen.
* **Color Support**: I/O interface allows changing the text and background colors dynamically.
* **Custom `printk`**: A custom implementation of variadic functions to format and print strings, integers (`%d`), hexadecimals (`%x`), and characters (`%c`).

## 🛠️ Prerequisites

To build and run this kernel, you will need an x86 Linux environment (or a cross-compiler) with the following packages installed:

* `gcc` (or `i686-linux-gnu-gcc` for cross-compiling)
* `ld` (GNU Binutils)
* `qemu-system-x86` (for emulation)
* `grub-pc-bin` & `grub-common` (for building the bootable ISO)
* `xorriso` (for ISO creation)

## 💻 Installation & Usage

1. Clone the repository:
   ```bash
   git clone (...) kfs-1
   cd kfs-1
2. Build the kernel and create the ISO:
   make
3. Run the kernel in QEMU:
   make run
4. Run the ISO in QEMU:
   make run-iso
5. Clean up build files:
   make clean      # Removes object files
   make fclean     # Removes object files, binaries, and ISOs 
📂 Project Structure
.
├── Makefile        # Automated build and run scripts
├── src/
│   ├── boot.S      # Assembly entry point, Multiboot header, and stack setup
│   ├── main.c      # Kernel main function and demo execution
│   └── tool.c      # VGA manipulation, I/O ports, scrolling, and printk implementation
├── include/
│   └── kernel.h    # Prototypes and custom type definitions
└── linker.ld       # Linker script defining the memory layout



