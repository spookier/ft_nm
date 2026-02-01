#include "../incs/ft_nm.h"

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
    
    // Close the fd immediately after mmap because the mapping stays active
    close(fd);

    if (map == MAP_FAILED)
        perror("Error mmap");

    return (map);
}

int identify_elf(void *memorymap)
{
    // 1 byte increment
    unsigned char *byte = (unsigned char *)memorymap;
    
    if (*byte != 0x7F || *(byte+1) != 'E' || *(byte+2) != 'L' || *(byte+3) != 'F')
    {
        printf("Not an ELF file.\n");
        return(1);
    }
    return(0);
    
   // printf("%02x\n", *byte);

}


int main(int argc, char **argv)
{
    void *memorymap;
    size_t filesize;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (-1);
    }

    memorymap = init_file_mapping(argv[1], &filesize);
    if (memorymap == MAP_FAILED)
        return (-1);

    if (identify_elf(memorymap) == 1)
        return(1);



    // Unmap before finishing
    munmap(memorymap, filesize);
    return (0);
}
