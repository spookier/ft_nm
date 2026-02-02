#include "../incs/handle64.h"

void handle64(void *memorymap)
{
    // Cast the raw pointer to an ELF header pointer
    Elf64_Ehdr *header;
    Elf64_Shdr *sectionheader;

    header = (Elf64_Ehdr *)memorymap; 
    
    // Mapping is 1:1 to an Elf64_Ehdr struct
    // e.g: header->e_shoff
    

    // We now need the Section Header
    // So we do: "Go to that address and treat this location as the start of a Elf64_Shdr struct"
    

    // We cast memorymap to 1 byte and add the offset from header->e_shoff to get the start of the Elf64_Shdr struct 
    sectionheader = (Elf64_Shdr *)((unsigned char *)memorymap + header->e_shoff);

    // We now need to find the Symbol Table
    
    // because there are many Section Headers (for .text, .data, .rodata ...etc) we need to iterate until we find the correct one
    // the correct one has its sectionheader->sh_type == SHT_SYMTAB
    // we can get the number of Section Headers from header->e_shnum
   
    for(int i = 0; i < header->e_shnum; ++i)
    {
        if (sectionheader[i].sh_type == SHT_SYMTAB)
            printf("Found at %d\n", i);
    }
    
    // Writing sectionheader[i] = the same as *(sectionheader + i))
    // Since Elf64_Shdr size is ~64 bytes
    // Adding 1 (or incrementing i) automatically moves the pointer forward by 64 bytes
    // ---> sectionheader[0] starts at offset 0
    // ---> sectionheader[1] starts at offset 64
    // ---> sectionheader[2] starts at offset 128

    // Can be verified with "readelf -S"


        

     
}
