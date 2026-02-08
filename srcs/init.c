#include "init.h"
#include <fcntl.h>      // open, close
#include <stdio.h>      // perror
#include <sys/mman.h>   // mmap, munmap
#include <sys/stat.h>   // fstat
#include <unistd.h>     // close, write

void *init_file_mapping(char *filename, size_t *filesize)
{
    int         fd;
    struct stat sstruct;
    void        *map;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (MAP_FAILED);
    }

    if (fstat(fd, &sstruct) == -1)
    {
        perror("Error fstat");
        close(fd);
        return (MAP_FAILED);
    }

    *filesize = sstruct.st_size;
    map = mmap(NULL, sstruct.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    // Close the fd immediately after mmap / the mapping stays active anyway
    close(fd);

    if (map == MAP_FAILED)
        perror("Error mmap");

    return (map);
}
