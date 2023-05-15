#include "../../include/ft_nm.h"


static int p_sh_name(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
	return(0);
}

int e_64Shdr_parse(void *mapped_memory, t_data64 *data)
{
	unsigned char *mem;

	mem = (unsigned char *)mapped_memory;

	// --- 1ST PART
	// mem = address of where program is loaded in RAM 
	// Move start of structure e_shoff bytes
	// casting as (t_ELF64_SectionHeader *) = interpret this part of the memory as an array of section headers
	// basically cast as ptr * = get a list of arrays of shdr[]
	// So, e_64_Shdr = RAM ADDRESS + BYTES TO SECTION HEADERS

	data->e_64_Shdr = (t_ELF64_SectionHeader *)(mem + data->e_64_Hdr.e_shoff);
	// -> just like that, e_64_Shdr became the start of the section string table

	//printf("%d\n", data->e_64_Hdr.e_shstrndx);

	// --- 2ND PART
	//  e_shstrndx = points to the string table
	//  so the structure array = index of the string table
	// .sh_offset = beginning of the string

	data->sh_strTable = (char *)(mem + data->e_64_Shdr[data->e_64_Hdr.e_shstrndx].sh_offset);


    // Print the name of the first section
    printf("First section name: %s\n", data->sh_strTable + data->e_64_Shdr[1].sh_name);

}

