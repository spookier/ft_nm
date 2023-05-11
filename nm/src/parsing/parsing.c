#include "../../include/ft_nm64.h"
#include "../../include/ft_nm.h"


int map_memory(int argc, char **argv, int fd, t_FSTRUCT *fstruct)
{
	void *mapped_memory;
	unsigned char *data;
	size_t i;

	mapped_memory = mmap(NULL, fstruct->file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if(mapped_memory == MAP_FAILED)
	{
		printf("Error. mmap() failed\n");
		return(-1);
	}
	data = (unsigned char *)mapped_memory;
	i = 0;
	while (i < fstruct->file_size)
	{
		printf("%02x ", data[i]);
		i++;
	}

	//free it with munmap
	munmap(mapped_memory, fstruct->file_size);
}

// save in memory and read the elf file with mmap();
int get_size(int argc, char **argv, int fd)
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

int processing(int argc, char **argv, int fd)
{
	if(get_size(argc, argv, fd) == -1)
		return(-1);
	return(0);
}

int argc_parsing(int argc, char **argv)
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
				// DO THE PROCESSING HERE
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