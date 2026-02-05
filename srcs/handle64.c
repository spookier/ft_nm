#include "../incs/handle64.h"

void handle64(void *memorymap)
{
    // Cast the raw pointer to an ELF header pointer
    Elf64_Ehdr *header;
    Elf64_Shdr *sectionheader;
    Elf64_Sym *symboltable;
    

    int i;
    int symbol_count;
    char *sym_stringtable;

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
    
    i = 0;
    while(i < header->e_shnum)
    {
        if (sectionheader[i].sh_type == SHT_SYMTAB)
        {
            break ;         // We instantly break to save in i where we found SHT_SYMTAB
        }
        i++;
    }

    // Writing sectionheader[i] = the same as *(sectionheader + i))
    // Since Elf64_Shdr size is ~64 bytes
    // Adding 1 (or incrementing i) automatically moves the pointer forward by 64 bytes
    // ---> sectionheader[0] starts at offset 0
    // ---> sectionheader[1] starts at offset 64
    // ---> sectionheader[2] starts at offset 128
    
    // Can be verified with "readelf -S"

    // We now need ->sh_offset to find where the Symbol Table starts
    
    symboltable = (Elf64_Sym *)((unsigned char *)memorymap + sectionheader[i].sh_offset); 
    
    // Now we know where the Symbol Table starts (where the first symbol starts)
    // This is also an array(list of symbols), so to print them we need a limit
    // ->sh_size = TOTAL size of this section in bytes
    // ->sh_entsize = the size of a SINGLE individual symbol
   

    // We check for divison by 0 incase a value is 0
    if (sectionheader[i].sh_size == 0 || sectionheader[i].sh_entsize == 0)
    {
        printf("Division by 0 error. Exiting.");
        return;
    }
    else
    {
        symbol_count = sectionheader[i].sh_size / sectionheader[i].sh_entsize;
        printf("Number of symbols %d\n", symbol_count);
    }

    // Now that we have the count, we can print the name of each symbol with ->st_name
    // But there's a catch !
    // ->st_name is just an offset/index in a completely different section called the String Table
    // We must first find where String Table starts in memory and add this offset

    // sectionheader[i].sh_link = The index of the String Table section header
    
    int stringtable_index = sectionheader[i].sh_link;

    // Now we know the String Table for our current Symbol Table section starts at sectionheader[stringtable_index]
     
    sym_stringtable = (char *)((unsigned char *)memorymap + sectionheader[stringtable_index].sh_offset);
    
    // Iterate through all symbols and print them

    // Print symbol's hexa address + symbol's name
    char        *symbol_name;
    Elf64_Addr  hexa_addr; 
    int j = 0;

    while(j < symbol_count)
    {
        symbol_name = sym_stringtable + symboltable[j].st_name;
        hexa_addr = symboltable[j].st_value;

        // Ensure the symbol has a name before doing anything
        if (symbol_name[0] != '\0')
        {
            if (hexa_addr != 0) 
            {
                // Print address + name
                printf("%016lx %s\n", hexa_addr, symbol_name);
            } 
            else 
            {
                // Print 16 spaces (padding) + name
                // %16s with "" prints 16 spaces
                printf("%16s %s\n", "", symbol_name);
            }
        }
        j++;
     }

    (void)symboltable;
}
