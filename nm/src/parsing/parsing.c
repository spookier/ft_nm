#include "../../include/ft_nm64.h"
#include "../../include/ft_nm.h"

// save in memory and read the elf file with mmap();
int get_size(int argc, char **argv, int fd)
{
	t_FSTRUCT *fstruct;
	int status;

	//printf("ok\n");
	//find out why it crash when no printf
    fstruct = malloc(sizeof(t_FSTRUCT));
	if(!fstruct)
		return(-1);
	status = fstat(fd, (struct stat *)fstruct);
	if(status == -1)
	{
		printf("fstat() failed\n");
		return(-1);
	}
	//printf("file size %ld\n", fstruct->file_size);
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
				//printf("processing: %s\n", argv[i]);
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