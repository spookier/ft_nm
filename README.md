# ft_nm

Reimplementation from scratch of the Unix `nm` command in **C**

Reads **ELF** files (executables, `.o`, `.so`) and prints their symbols  
The file is `mmap`'d in memory and parsed directly

## Preview

### ELF64 — ft_nm vs GNU nm

<p align="center">
  <em>ft_nm output (left) compared with GNU nm (right) on the same ELF64 binary</em><br><br>
  <img width="800" alt="ELF64 ft_nm vs nm"
       src="https://github.com/user-attachments/assets/3a806551-32ac-41b1-8989-53826094126d" />
</p>

### ELF32 — ft_nm vs GNU nm

<p align="center">
  <em>ft_nm output (left) compared with GNU nm (right) on the same ELF32 binary</em><br><br>
  <img width="800" alt="ELF32 ft_nm vs nm"
       src="https://github.com/user-attachments/assets/3b61a978-494c-41e1-a185-82f907fb133c" />
</p>




## Highlights

- Supports both **ELF64** (x86_64) and **ELF32** (x86_32) binaries
- Parses ELF headers, section headers, and symbol tables with `mmap`
- Prints `nm`-style output: address, type, name (sorted)
- 64-bit addresses: 16-char hex (`0000000000004ba0`), 32-bit: 8-char hex (`00001234`)
- Symbol types: `T`, `D`, `B`, `R`, `U`, `A`, `C`, `W` (and local/weak case rules)
- Bounds checks to avoid crashes on bad inputs

How it works: map the file, find `SHT_SYMTAB` + string table, classify symbols from section flags/binding, then sort and print

## Build

```bash
make
```

## Run

```bash
./ft_nm <elf_file>
```

```
$ ./ft_nm /usr/bin/ls
0000000000004ba0 T main
                 U malloc
0000000000008280 D optind
```

Output mirrors system `nm`: hex address, type character, symbol name. sorted alphabetically.

## References

- [ELF Specification](https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html) · [Linux elf.h](https://github.com/torvalds/linux/blob/master/include/uapi/linux/elf.h) · [elf(5) man page](https://man7.org/linux/man-pages/man5/elf.5.html) · [ELF-64 Format (PDF)](https://www.uclibc.org/docs/elf-64-gen.pdf)
