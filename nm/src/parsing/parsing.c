#include "../../include/ft_nm64.h"

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
				//do the processing here
				printf("processing: %s\n", argv[i]);	
			}
			if(fd != -1)
				close(fd);
			i++;
		}
	}
}