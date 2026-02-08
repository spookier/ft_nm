#ifndef HANDLE32_H
# define HANDLE32_H

#include <stdint.h>

// --------------------------------------------------

#define SHT_SYMTAB  2

// ELF32 VARIABLES
typedef uint32_t    Elf32_Addr;
typedef uint16_t    Elf32_Half;
typedef uint32_t    Elf32_Off;
typedef int32_t     Elf32_Sword;
typedef uint32_t    Elf32_Word;

// --------------------------------------------------
// ELF32 HEADER FILE
#define EI_NIDENT 16
typedef struct
{
        unsigned char   e_ident[EI_NIDENT];
        Elf32_Half      e_type;
        Elf32_Half      e_machine;
        Elf32_Word      e_version;
        Elf32_Addr      e_entry;
        Elf32_Off       e_phoff;
        Elf32_Off       e_shoff;
        Elf32_Word      e_flags;
        Elf32_Half      e_ehsize;
        Elf32_Half      e_phentsize;
        Elf32_Half      e_phnum;
        Elf32_Half      e_shentsize;
        Elf32_Half      e_shnum;
        Elf32_Half      e_shstrndx;
} Elf32_Ehdr;

// --------------------------------------------------
// SECTION HEADER (from e_shoff from the ELF header)
typedef struct
{
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

// --------------------------------------------------
// SYMBOL TABLE
typedef struct
{
    Elf32_Word 		st_name;
    Elf32_Addr 		st_value;
    Elf32_Word 		st_size;
    unsigned char 	st_info;
    unsigned char 	st_other;
    Elf32_Half 		st_shndx;
} Elf32_Sym;

// -------------------------------------------------

// -------------------------------------------------

// SYMBOL TABLE Type (->st_shndx / ->st_info)
#define SHT_NOBITS  8

#define SHN_UNDEF       0
#define SHN_ABS         0xfff1
#define SHN_COMMON      0xfff2

// ->sh_flags
#define SHF_WRITE       0x1
#define SHF_ALLOC       0x2
#define SHF_EXECINSTR   0x4

// ->st_info
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

// ->st_info Type (it's in the lower 4 bits of st_info)
#define STT_FILE   4

// Macros to extract information from the st_info byte
// Binding is the upper 4 bits, Type is the lower 4 bits
#define ELF32_ST_BIND(i) ((i) >> 4)
#define ELF32_ST_TYPE(i) ((i) & 0xf)

// --------------------------------------------------------

int handle32(void *memorymap);

#endif
