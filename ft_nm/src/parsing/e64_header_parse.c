#include "../../include/ft_nm.h"

// TO DO:     Parse data into ELF64 struct
// @DEBUG   - Make the printf statements in parsing optional


void	*ft_memcpy(void *dst, const void *src, size_t length)
{
	size_t	i;
	i = 0;
	if (!dst && !src)
		return (dst);
	while (i < length)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

static int p_ident(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    size_t end = *i + max;
    while (*i < end)
    {
        data->e_64_Hdr.e_ident[*i] = mem[*i];
        (*i)++;
    }
    return (0);
}

static int p_type(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_type, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_machine(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_machine, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_version(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_version, mem + *i, sizeof(ELF64_Word));
    *i += max;  // advance i by max bytes
    return (0);
}
static int p_entry(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_entry, mem + *i, sizeof(ELF64_Addr));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_phoff(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_phoff, mem + *i, sizeof(ELF64_Offset));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_shoff(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_shoff, mem + *i, sizeof(ELF64_Offset));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_flags(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_flags, mem + *i, sizeof(ELF64_Word));
    *i += max;  // advance i by max bytes
    return (0);
}
static int p_ehsize(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_ehsize, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_phentsize(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_phentsize, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_phnum(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_phnum, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_shentsize(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_shentsize, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_shnum(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_shnum, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}

static int p_shstrndx(unsigned char *mem, t_data64 *data, size_t *i, size_t max)
{
    ft_memcpy(&data->e_64_Hdr.e_shstrndx, mem + *i, sizeof(ELF64_Halfword));
    *i += max;  // advance i by max bytes
    return (0);
}


static void print_everything(t_data64 *data)
{
    printf("type: %d\n", data->e_64_Hdr.e_type);
    printf("machine: %d\n", data->e_64_Hdr.e_machine);
    printf("version: %d\n", data->e_64_Hdr.e_version);
    printf("entry: %lu\n", data->e_64_Hdr.e_entry);
    printf("phoff: %lu\n", data->e_64_Hdr.e_phoff);
    printf("shoff: %lu\n", data->e_64_Hdr.e_shoff);
    printf("flags: %d\n", data->e_64_Hdr.e_flags);
    printf("ehsize: %d\n", data->e_64_Hdr.e_ehsize);
    printf("phentsize: %d\n", data->e_64_Hdr.e_phentsize);
    printf("phnum: %d\n", data->e_64_Hdr.e_phnum);
    printf("shentsize: %d\n", data->e_64_Hdr.e_shentsize);
    printf("shnum: %d\n", data->e_64_Hdr.e_shnum);
    printf("shstrndx: %d\n", data->e_64_Hdr.e_shstrndx);
}

int e_64hdr_parse(void *mapped_memory, t_data64 *data)
{
	size_t i;
	unsigned char *mem;

	i = 0;
	mem = (unsigned char *)mapped_memory;

	printf("\ndetected 64bit!\n\n");

    p_ident(mem, data, &i,     sizeof(unsigned char) * 16);
    p_type(mem, data, &i,      sizeof(ELF64_Halfword));
    p_machine(mem, data, &i,    sizeof(ELF64_Halfword));
    p_version(mem, data, &i,    sizeof(ELF64_Word));
    p_entry(mem, data, &i,      sizeof(ELF64_Addr));
    p_phoff(mem, data, &i,      sizeof(ELF64_Offset));
    p_shoff(mem, data, &i,      sizeof(ELF64_Offset));
    p_flags(mem, data, &i,      sizeof(ELF64_Word));
    p_ehsize(mem, data, &i,     sizeof(ELF64_Halfword));
    p_phentsize(mem, data, &i,  sizeof(ELF64_Halfword));
    p_phnum(mem, data, &i,      sizeof(ELF64_Halfword));
    p_shentsize(mem, data, &i,  sizeof(ELF64_Halfword));
    p_shnum(mem, data, &i,      sizeof(ELF64_Halfword));
    p_shstrndx(mem, data, &i,   sizeof(ELF64_Halfword));


    print_everything(data);
    // @DEBUG


	printf("\n");
	return (0);
}