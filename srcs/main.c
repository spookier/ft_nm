#include "../incs/handle64.h"
#include "../incs/init.h"

int identify_elf(void *memorymap)
{
    // 1 byte increment
    unsigned char *byte = (unsigned char *)memorymap;
    
    // Check if its an ELF file 
    if (*byte != 0x7F || *(byte + 1) != 'E' || *(byte + 2) != 'L' || *(byte + 3) != 'F')
    {
        printf("Not an ELF file.\n");
        return (1);
    }
    
    // Check if 64bit OR 32bit
    if (*(byte + 4) == 1)
    {
        printf("32bit file\n");
    }
    else if (*(byte + 4) == 2)
    {
        printf("64bit file\n");
    }
    else
    {
        printf("Invalid ELF file. \n");
        return(1);
    }

    return (0);
    
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
    
    handle64(memorymap);

    // Unmap before finishing
    munmap(memorymap, filesize);
    return (0);
}
