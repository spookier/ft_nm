#include "../../include/ft_nm64.h"
#include "../../include/ft_nm.h"

// CUSTOM hexdump viewer for debug
void print_mem(void *mapped_memory, size_t file_size)
{
	size_t i;
	size_t j;
	unsigned char *data;

	data = (unsigned char *)mapped_memory;
	i = 0;
	while (i < file_size)
	{
		j = 0;
		while (j < 16)
		{
			printf("%02x ", data[i]);
			j++;
			i++;
		}
		printf("\n");
	}
}

// use mmap to map memory then parse header
int map_memory(int argc, char **argv, int fd, t_FSTRUCT *fstruct)
{
	void *mapped_memory;

	mapped_memory = mmap(NULL, fstruct->file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if(mapped_memory == MAP_FAILED)
	{
		printf("Error. mmap() failed\n");
		return(-1);
	}

	// DO THE PARSING PROCESSING HERE
	print_mem(mapped_memory, fstruct->file_size);


	// free memory once parsing is done
	if(munmap(mapped_memory, fstruct->file_size) == -1)
		return(-1);
	return(0);
}

// use fstat to save info about size of file
int processing(int argc, char **argv, int fd)
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
				if(processing(argc, argv, fd) == -1)
					return(-1);
			}
			if(fd != -1)
				close(fd);
			i++;
		}
	}
	return(0);
}