#include "handle32.h"
#include "utils.h"
#include "ft_printf.h"
#include <stdlib.h>     // malloc, free


char get_symbol_type32(Elf32_Sym *current_symbol, Elf32_Shdr *sectionheader)
{
	char symbol_type;
	Elf32_Shdr *dest_section;

	symbol_type = 'U';
	if (current_symbol->st_shndx == SHN_UNDEF)
		symbol_type = 'U';
	else if (current_symbol->st_shndx == SHN_ABS)
		symbol_type = 'A';
	else if (current_symbol->st_shndx == SHN_COMMON)
		symbol_type = 'C';
	else
	{
		dest_section = &sectionheader[current_symbol->st_shndx];
		if (dest_section->sh_type == SHT_NOBITS)
			symbol_type = 'B';
		else if (dest_section->sh_flags & SHF_EXECINSTR)
			symbol_type = 'T';
		else if (dest_section->sh_flags & SHF_WRITE)
			symbol_type = 'D';
		else if (dest_section->sh_flags & SHF_ALLOC)
			symbol_type = 'R';
	}
	if (ELF32_ST_BIND(current_symbol->st_info) == STB_WEAK)
	{
		if (symbol_type == 'U')
			symbol_type = 'w';
		else
			symbol_type = 'W';
	}
	else if (ELF32_ST_BIND(current_symbol->st_info) == STB_LOCAL)
	{
		if (symbol_type != '?')
			symbol_type += 32;
	}
	return (symbol_type);
}


int handle32(void *memorymap)
{
	Elf32_Ehdr *header;
	Elf32_Shdr *sectionheader;
	Elf32_Sym *symboltable;

	int i;
	int symbol_count;
	char *sym_stringtable;

	header = (Elf32_Ehdr *)memorymap;
	
	sectionheader = (Elf32_Shdr *)((unsigned char *)memorymap + header->e_shoff);


	i = 0;
	while(i < header->e_shnum)
	{
		if (sectionheader[i].sh_type == SHT_SYMTAB)
		{
			break ;
		}
		i++;
	}

	symboltable = (Elf32_Sym *)((unsigned char *)memorymap + sectionheader[i].sh_offset);

	if (sectionheader[i].sh_size == 0 || sectionheader[i].sh_entsize == 0)
	{
		ft_printf("No symbols.\n");
		return (-1);
	}
	else
	{
		symbol_count = sectionheader[i].sh_size / sectionheader[i].sh_entsize;
	}

	int stringtable_index = sectionheader[i].sh_link;

	sym_stringtable = (char *)((unsigned char *)memorymap + sectionheader[stringtable_index].sh_offset);

	char *symbol_name;
	Elf32_Addr hexa_addr;
	char symbol_type;
	int j;

	t_symbol *saved_symbols;

	saved_symbols = malloc(sizeof(t_symbol) * symbol_count);
	if (!saved_symbols)
		return (-1);

	int list_index = 0;
	j = 0;
	while(j < symbol_count)
	{
		if (ELF32_ST_TYPE(symboltable[j].st_info) == STT_FILE)
		{
			j++;
			continue;
		}
		
		symbol_name = sym_stringtable + symboltable[j].st_name;
		hexa_addr = symboltable[j].st_value;

		symbol_type = get_symbol_type32(&symboltable[j], sectionheader);
		
		if (symbol_name[0] != '\0')
		{
			if (hexa_addr != 0) 
			{
				saved_symbols[list_index].name = symbol_name;
				saved_symbols[list_index].type = symbol_type;
				saved_symbols[list_index].value = hexa_addr;
			} 
			else 
			{
				saved_symbols[list_index].name = symbol_name;
				saved_symbols[list_index].type = symbol_type;
				saved_symbols[list_index].value = 0;
			}
			list_index++;
		}
		j++;
	 }
	 print_symbol(saved_symbols, list_index, 0);
	 free(saved_symbols);
	 return (0);
}