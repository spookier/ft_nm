#ifndef FT_NM_H_64
# define FT_NM_H_64

#include "libraries.h"

/* Macros for accessing the fields of st_info. */
#define SHN_UNDEF	0
#define	ELF64_ST_BIND(info)		((info) >> 4)
#define	ELF64_ST_TYPE(info)		((info) & 0xf)


# define EI_NIDENT 16
typedef __uint64_t		ELF64_Addr;		// 8 bytes
typedef __uint16_t		ELF64_Halfword; // 2 bytes
typedef __uint64_t		ELF64_Offset; 	// 8 bytes
typedef __uint32_t		ELF64_Word; 	// 4 bytes
typedef __uint64_t		ELF64_Xword; 	// 8 bytes

typedef struct s_ELF64_Header
{
	unsigned char	e_ident[EI_NIDENT];
	ELF64_Halfword	e_type;		
	ELF64_Halfword	e_machine;	
	ELF64_Word		e_version;	
	ELF64_Addr		e_entry;	
	ELF64_Offset	e_phoff;	
	ELF64_Offset	e_shoff;	
	ELF64_Word		e_flags;	
	ELF64_Halfword	e_ehsize;	
	ELF64_Halfword	e_phentsize;	
	ELF64_Halfword	e_phnum;	
	ELF64_Halfword	e_shentsize;	
	ELF64_Halfword	e_shnum;	
	ELF64_Halfword	e_shstrndx;	

} t_ELF64_Header;


typedef struct s_ELF64_SectionHeader
{
	ELF64_Word		sh_name;
	ELF64_Word		sh_type;	
	ELF64_Xword		sh_flags;	
	ELF64_Addr		sh_addr;	
	ELF64_Offset	sh_offset;	
	ELF64_Xword		sh_size;	
	ELF64_Word		sh_link;
	ELF64_Word		sh_info;	
	ELF64_Xword		sh_addralign;	
	ELF64_Xword		sh_entsize;	 

} t_ELF64_SectionHeader;


typedef struct s_ELF64_Sym 
{
  ELF64_Word 		st_name;		
  unsigned char		st_info;	
  unsigned char		st_other;	
  ELF64_Halfword 	st_shndx;		
  ELF64_Addr 		st_value;		
  ELF64_Xword 		st_size;

} t_ELF64_Sym;


typedef struct s_data64
{
    t_ELF64_Header 			e_64_Hdr;
    t_ELF64_SectionHeader 	*e_64_Shdr;
	t_ELF64_Sym				*e_64_Sym;
	off_t 					file_size;
	char 					*sh_strTable;
	char 					*st_symTable;
	int						nb_symbols;
	int						sym_string_index;			

} t_data64;




// ELF64 Header Parsing 
int e_64hdr_parse(void *mapped_memory, t_data64 *data);

// ELF64 SECTION Header parsing
int e_64Shdr_parse(void *mapped_memory, t_data64 *data);

#endif
