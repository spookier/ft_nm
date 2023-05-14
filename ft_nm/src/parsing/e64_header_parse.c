#include "../../include/ft_nm.h"

// TO DO:   Parse data into ELF64 struct
// @DEBUG   - Make the printf statements in parsing optional


static int print(t_data64 *data, size_t max)
{
	int j;
	j = 0;
	while (j < max)
	{
		printf("%02x ", data->e_64_Hdr.e_ident[j]);
		j++;
	}
	printf("\n");
}

static int p_eident(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_ident[*i] = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_ident[*i]);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_etype(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_type = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_type);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_emachine(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_machine = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_machine);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eversion(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_version = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_version);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eentry(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_entry = mem[*i];
        printf("%02lx ", data->e_64_Hdr.e_entry);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_ephoff(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_phoff = mem[*i];
        printf("%02lx ", data->e_64_Hdr.e_phoff);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eshoff(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_shoff = mem[*i];
        printf("%02lx ", data->e_64_Hdr.e_shoff);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eflags(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_flags = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_flags);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_ehsize(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_ehsize = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_ehsize);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_ephentsize(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_phentsize = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_phentsize);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_ephnum(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_phnum = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_phnum);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eshentsize(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_shentsize = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_shentsize);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eshnum(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_shnum = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_shnum);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}

static int p_eshstrndx(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_shstrndx = mem[*i];
        printf("%02x ", data->e_64_Hdr.e_shstrndx);
		if ((*i + 1) % 16 == 0) // prints newline every 16 lines
			printf("\n");
        (*i)++;
    }
    return (0);
}


int e_64hdr_parse(void *mapped_memory, t_data64 *data)
{
	size_t i;
	unsigned char *mem;

	i = 0;
	mem = (unsigned char *)mapped_memory;

	printf("\ndetected 64bit!\n");

	p_eident(mem, data, &i,     sizeof(unsigned char) * 16);
	p_etype(mem, data, &i,      sizeof(ELF64_Halfword));
	p_emachine(mem, data, &i,   sizeof(ELF64_Halfword));
	p_eversion(mem, data, &i,   sizeof(ELF64_Word));
	p_eentry(mem, data, &i,     sizeof(ELF64_Addr));
	p_ephoff(mem, data, &i,     sizeof(ELF64_Offset));
	p_eshoff(mem, data, &i,     sizeof(ELF64_Offset));
	p_eflags(mem, data, &i,     sizeof(ELF64_Word));
	p_ehsize(mem, data, &i,     sizeof(ELF64_Halfword));
	p_ephentsize(mem, data, &i, sizeof(ELF64_Halfword));
	p_ephnum(mem, data, &i,     sizeof(ELF64_Halfword));
	p_eshentsize(mem, data, &i, sizeof(ELF64_Halfword));
	p_eshnum(mem, data, &i,     sizeof(ELF64_Halfword));
	p_eshstrndx(mem, data, &i,  sizeof(ELF64_Halfword));

    //printf("i has looped = %ld times", i);
	printf("\n");
	return (0);
}