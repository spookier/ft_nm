#include "handle64.h"
#include "handle32.h"
#include "init.h"
#include "ft_printf.h"
#include <sys/mman.h>  // mmap, munmap


int identify_elf(void *memorymap)
{
    // 1 byte increment
    unsigned char *byte = (unsigned char *)memorymap;
    
    // Check if its an ELF file 
    if (*byte != 0x7F || *(byte + 1) != 'E' || *(byte + 2) != 'L' || *(byte + 3) != 'F')
    {
        ft_printf("Not an ELF file.\n");
        return (1);
    }
    
    // Check if 64bit OR 32bit
    if (*(byte + 4) == 1)
    {
		if (handle32(memorymap) == -1)
		{
			ft_printf("Handle32 fail. \n");
			return(-1);
		}
    }
    else if (*(byte + 4) == 2)
    {
    	if (handle64(memorymap) == -1)
		{
			ft_printf("Handle64 fail. \n");
			return(-1);
		}
    }
    else
    {
        ft_printf("Invalid ELF file. \n");
        return(1);
    }

    return (0);
}


int main(int argc, char **argv)
{
    void *memorymap;
    size_t filesize;

    if (argc != 2)
    {
        ft_printf("Usage: %s <filename>\n", argv[0]);
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
