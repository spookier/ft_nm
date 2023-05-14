#include "../../include/ft_nm.h"


static int p_sh_name(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
	return(0);
}

int e_64Shdr_parse(void *mapped_memory, t_data64 *data)
{
	size_t i;
	unsigned char *mem;

	i = 0;
	mem = (unsigned char *)mapped_memory;

	//p_sh_name(mem, data, &i,     sizeof(unsigned char) * 16);
}