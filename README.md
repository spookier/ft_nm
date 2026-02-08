# ft_nm

Reimplementation from scratch of the Unix `nm` command in **C**

Reads **ELF** files (executables, `.o`, `.so`) and prints their symbols  
The file is `mmap`'d in memory and parsed directly

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
