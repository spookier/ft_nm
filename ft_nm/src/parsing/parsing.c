#include "../../include/ft_nm64.h"
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


// TO DO:
// - OPTIMIZATION: check if file->size is at least min size of an ELF file
// - OPTIMIZATION: remove multiple typecasts conversions && unsigned char *mem;

// FIX is_32_or_64() function

static int is_32_or_64(void *mapped_memory)
{
	unsigned char *mem;


	printf("HEXA = %02x ", mem[4]);
	mem = (unsigned char *)mapped_memory;
	if (mem[4] == 0x01)
		return(32);
	else if (mem[4] == 0x02)
		return(64);
	else
		return(-1);
}

// checks if its a valid ELF 64 file by comparing each hexa value
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



// use mmap() to map memory then parse header
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
	// DO THE PARSING PROCESSING HERE


	//debug_print_mem(mapped_memory, fstruct->file_size);
	if (is_valid_elf_file(mapped_memory) == -1)
	{
		printf("nm: %s: file format not recognized\n", argv);
		return(-1);
	}
	// Program flows to 2 different paths -> 64 or 32 BASED on ret value
	if (is_32_or_64(mapped_memory) == -1)
	{
		printf("Error. Unknown class\n");
		return(-1);
	}
	else if (is_32_or_64(map_memory) == 32)
		e_32hdr_parse(mapped_memory, fstruct->file_size);
	else if (is_32_or_64(map_memory) == 64)
		e_64hdr_parse(map_memory, fstruct->file_size);

	//printf("[OK] - %s\n", argv);

	// ---------------------------------
	// free memory once parsing is done
	printf("we done here!\n");
	if(munmap(mapped_memory, fstruct->file_size) == -1)
		return(-1);
	return(0);
}

// use fstat to save info about size of file
static int processing(int argc, char *argv, int fd)
{
	t_FSTRUCT *fstruct;
	int status;

    fstruct = malloc(sizeof(struct stat));
	if(!fstruct)
	{
		printf("Error. malloc() failled to allocate\n");
		return(-1);
	}
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


// start of parsing
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