#include "../../include/ft_nm.h"

// @DEBUG - CUSTOM 16bit hexdump viewer for debug (endianness of --C option)
static void debug_print_mem(void *mapped_memory, size_t file_size)
{
	size_t i;
	size_t j;
	unsigned char *mem;

	mem = (unsigned char *)mapped_memory;
	i = 0;
	while (i < file_size)
	{
		j = 0;
		while (j < 16 && i < file_size)
		{
			printf("%02x ", mem[i]);
			j++;
			i++;
		}
		printf("\n");
	}
}





static void *alloc_struct(size_t struct_size)
{
    void *mem = malloc(struct_size);
    if (!mem) 
	{
        printf("Error. Memory allocation failed\n");
        return (NULL);
    }
    return (mem);
}


// TO DO:
// - OPTIMIZATION: check if file->size is at least min size of an ELF file
// - OPTIMIZATION: remove multiple typecasts conversions && unsigned char *mem;
// - FIX is_32_or_64() function


static int is_32_or_64(void *mapped_memory, t_FSTRUCT *fstruct)
{
	unsigned char *mem;
	t_data64 *e_64;
	t_data32 *e_32;

	mem = (unsigned char *)mapped_memory;
	if (mem[4] == 0x01)
	{
		e_32 = alloc_struct(sizeof(t_data32));
		if(!e_32)
			return(-1);
		
		// TO DO: Set ident_e to 0x01 to the elf32 header
		// TO DO: Error checking of function
		e_32->file_size = fstruct->file_size;
		e_32hdr_parse(mapped_memory, e_32);
		free(e_32);
	}
	else if (mem[4] == 0x02)
	{
		e_64 = alloc_struct(sizeof(t_data64));
		if(!e_64)
			return(-1);
		e_64->file_size = fstruct->file_size;
		e_64->e_64_Hdr.e_ident[4] = 0x02;

		// TO DO: Error checking of functions
		e_64hdr_parse(mapped_memory, e_64);
		e_64Shdr_parse(mapped_memory, e_64);
		free(e_64);
	}
	else
		return(-1);
	return(0);
}

// Checks valid ELF 64 file by comparing each hexa value with stored value
static int is_valid_elf_file(void *mapped_memory)
{
	unsigned char *mem;
	unsigned char elf64[] = {0x7f, 0x45, 0x4c, 0x46};
	int i;

	i = 0;
	mem = (unsigned char *)mapped_memory;
	while (i <= 3)
	{
		if (mem[i] == elf64[i])
			i++;
		else
			return (-1);
	}
	return (0);
}


// Use mmap() to map memory then validity of ELF -> splitting -> parsing
static int map_memory(int argc, char *argv, int fd, t_FSTRUCT *fstruct)
{
	void *mapped_memory;

	mapped_memory = mmap(NULL, fstruct->file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if(mapped_memory == MAP_FAILED)
	{
		printf("Error. mmap() failed\n");
		return(-1);
	}
	// ---------------------------------
	// PROCESSING STARTS HERE

	// @DEBUG - memory print
	//debug_print_mem(mapped_memory, fstruct->file_size);
	//printf("-----------------------\n\n");

	if (is_valid_elf_file(mapped_memory) == -1)
	{
		printf("nm: %s: file format not recognized\n", argv);
		return(-1);
	}

	// Program splits into 2 different paths from here -> 32 or 64
	if (is_32_or_64(mapped_memory, fstruct) == -1)
	{
		printf("Error. Unknown class\n");
		return(-1);
	}
	// ---------------------------------
	// free memory once parsing is done
	if(munmap(mapped_memory, fstruct->file_size) == -1)
		return(-1);
	return(0);
}



// Use fstat() to retrieve file's size
static int processing(int argc, char *argv, int fd)
{
	t_FSTRUCT *fstruct;
	int status;

    //fstruct = malloc(sizeof(struct stat));
    fstruct = alloc_struct(sizeof(struct stat));
	if(!fstruct)
		return(-1);
	status = fstat(fd, (struct stat *)fstruct);
	if(status == -1)
	{
		printf("Error. fstat() failed\n");
		return(-1);
	}
	if(fstruct->file_size > 0)
		map_memory(argc, argv, fd, fstruct);
	free(fstruct);
	return(0);
}


// Starts here
int start_parsing(int argc, char **argv)
{
	int fd;
	int i;
	int flag;

	if (argc <= 1)
	{
		fd = open("a.out", O_RDONLY);
		if (fd == -1)
		{
			printf("nm: 'a.out': No such file\n");
			return (-1);
		}
	}
	else
	{
		i = 1;
		while(i < argc)
		{
			flag = 0;
			fd = open(argv[i], O_RDONLY);
			if (fd == -1)
			{
				printf("nm: '%s': No such file\n", argv[i]);
				flag = -1;
			}
			if(flag != -1)
			{
				// parsing process starts here
				if(processing(argc, argv[i], fd) == -1)
					return(-1);
			}
			if(fd != -1)
				close(fd);
			i++;
		}
	}
	return(0);
}