#ifndef HANDLE64_H
# define HANDLE64_H

#include <stdint.h>


// --------------------------------------------------

#define SHT_SYMTAB  2

// ELF64 VARIABLES
typedef uint64_t    Elf64_Addr;
typedef uint16_t    Elf64_Half;
typedef uint64_t    Elf64_Off;
typedef int32_t     Elf64_Sword;
typedef int64_t     Elf64_Sxword;
typedef uint32_t    Elf64_Word;
typedef uint64_t    Elf64_Lword;
typedef uint64_t    Elf64_Xword;


// --------------------------------------------------
// ELF64 HEADER FILE
#define EI_NIDENT 16
typedef struct
{
        unsigned char   e_ident[EI_NIDENT];
        Elf64_Half      e_type;
        Elf64_Half      e_machine;
        Elf64_Word      e_version;
        Elf64_Addr      e_entry;
        Elf64_Off       e_phoff;
        Elf64_Off       e_shoff;
        Elf64_Word      e_flags;
        Elf64_Half      e_ehsize;
        Elf64_Half      e_phentsize;
        Elf64_Half      e_phnum;
        Elf64_Half      e_shentsize;
        Elf64_Half      e_shnum;
        Elf64_Half      e_shstrndx;
} Elf64_Ehdr;
// --------------------------------------------------


// SECTION HEADER (from e_shoff from the ELF header)

typedef struct
{
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
} Elf64_Shdr;


// --------------------------------------------------
// SYMBOL TABLE
typedef struct
{
    Elf64_Word 		st_name;
	unsigned char 	st_info;
    unsigned char 	st_other;
    Elf64_Half 		st_shndx;
    Elf64_Addr 		st_value;
    Elf64_Xword 	st_size;
} Elf64_Sym;

// -------------------------------------------------

// -----------------------------------------------


// SYMBOL TABLE Type (->st_shndx / ->st_info)
#define SHT_NOBITS  8

#define SHN_UNDEF       0
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2


// ->sh_flags
#define SHF_WRITE		0x1
#define SHF_ALLOC		0x2
#define SHF_EXECINSTR	0x4


// ->st_info
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

// ->st_info Type (it's in the lower 4 bits of st_info)
#define STT_FILE   4

// Macros to extract information from the st_info byte
// Binding is the upper 4 bits, Type is the lower 4 bits
#define ELF64_ST_BIND(i) ((i) >> 4)
#define ELF64_ST_TYPE(i) ((i) & 0xf)


// --------------------------------------------------------

int handle64(void *memorymap);


#endif
