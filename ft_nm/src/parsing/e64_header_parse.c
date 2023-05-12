#include "../../include/ft_nm.h"


// TO DO: Parse data into ELF64 struct

static int parse_ident(void *mapped_memory, t_data64 *data)
{
	int i;

	unsigned char *mem;

	mem = (unsigned char*)mapped_memory;

	i = 0;
	while (i < 16)
	{
		data->e_64_Hdr.e_ident[i] = mem[i];
		i++;
	}
	return(0);
}

int e_64hdr_parse(void *mapped_memory, t_data64 *data)
{
	printf("detected 64bit!\n");
	parse_ident(mapped_memory, data);
	return(0);
}