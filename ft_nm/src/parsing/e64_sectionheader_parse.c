#include "../../include/ft_nm.h"


// - Print section names
static int print_Sh_name(t_data64 *data)
{
	int i;

	i = 1;
	while (i < data->e_64_Hdr.e_shnum)
	{
    	printf("%s\n", data->sh_strTable + data->e_64_Shdr[i].sh_name);
		i++;
	}
}


// - Go through each section index until finding symbol table
static int find_symTable(unsigned char *mem, t_data64 *data)
{	
	int i;


	i = 0;
	while (i < data->e_64_Hdr.e_shnum)
	{
		if (data->e_64_Shdr[i].sh_type == 2)
		{
			data->st_symTable = (char *)(mem + data->e_64_Shdr[i].sh_offset);
			break;
		}
		i++;
	}
	if(!data->st_symTable)
	{
		printf("Error. SHT_SYMTAB not found\n");
		data->nb_symbols = 0;
		return(-1);
	}
	data->nb_symbols = data->e_64_Shdr[i].sh_size / data->e_64_Shdr[i].sh_entsize;
	data->sym_string_index = data->e_64_Shdr[i].sh_link;
	return(0);
}



int e_64Shdr_parse(void *mapped_memory, t_data64 *data)
{
	unsigned char *mem;

	mem = (unsigned char *)mapped_memory;

	// TO DO : Add functions return checks

	// --- 1ST PART
	// mem = address of where program is loaded in RAM 
	// Move start of structure e_shoff bytes
	// casting as (t_ELF64_SectionHeader *) = interpret this part of the memory as an array of section headers
	// basically cast as ptr * = get a list of arrays of shdr[]
	// So, e_64_Shdr = RAM ADDRESS + BYTES TO SECTION HEADERS
	// SO, e_64_Shdr became the start of the section string table
	data->e_64_Shdr = (t_ELF64_SectionHeader *)(mem + data->e_64_Hdr.e_shoff);

	// SECTION HEADER STRING TABLE
	//  e_shstrndx = points to the string table
	// data->sh_strTable = (char *)(mem + data->e_64_Shdr[data->e_64_Hdr.e_shstrndx].sh_offset);
	// @DEBUG print_Sh_name(data)

	//SYMBOL TABLE
	find_symTable(mem, data);
	// Now data->st_symTable points to the symbol table data
    // You can cast it to t_ELF64_Sym* and iterate over the symbols
    // The number of symbols is given by sh_size / sh_entsize in the symbol table's section header
	data->e_64_Sym = (t_ELF64_Sym *)data->st_symTable;

	// - Now that we got the symbol table, we need to locate the Symbol String Table
	// Replace st_symTable now to save space
	// 
	data->st_symTable = (char *)(mem + data->e_64_Shdr[data->sym_string_index].sh_offset);

	unsigned char dt;
	char *sym_name;
	char *st_symTable = data->st_symTable;


	// TO DO: FIND The discrepancy between nm and my files

	for (int j = 0; j < data->nb_symbols; j++) 
	{
    	unsigned char binding = ELF64_ST_BIND(data->e_64_Sym[j].st_info);
    	unsigned char type = ELF64_ST_TYPE(data->e_64_Sym[j].st_info);
    	ELF64_Halfword section = data->e_64_Sym[j].st_shndx;

    	// if (binding == 0 || type == 3 || type == 4 || section == SHN_UNDEF) 
        // 	continue;

    	char *sym_name = data->st_symTable + data->e_64_Sym[j].st_name;
    	printf("%s\n", sym_name);
	}
	
}

