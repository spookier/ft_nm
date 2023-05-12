#ifndef FT_NM_32_H
# define FT_NM_32_H

#include "ft_nm.h"

// TO DO: ADD EQUIVALENT OF 32 BITS VARIABLES

typedef struct s_ELF32_Header
{
	int something32;
	int something322;
	
} t_ELF32_Header;

typedef struct s_ELF32_SectionHeader
{
	int something32;
	int something322;

} t_ELF32_SectionHeader;

typedef struct s_data32
{
    t_ELF32_Header e_32_Hdr;
    t_ELF32_SectionHeader e_32_Shdr;
	off_t file_size;

} t_data32;

// ELF 32 Header Parsing function
int e_32hdr_parse(void *mapped_memory, t_data32 *data);

#endif