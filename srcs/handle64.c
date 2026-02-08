#include "handle64.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


// TO DO: Replace every function with libft one


// We want to know: "Is this symbol in a Text section? A Data section? Or a BSS section?"
// Tese sections are ID by letters (like 'T' 'D' 'B'). We need to check the section header the symbol belongs to
// If current_symbol->st_shndx is 3, we need to look at the 3rd item in the sectionheader array


// Some letters are Uppercase ('D'), and some are lowercase ('t')
// Uppercase means the symbol is Global (visible to other files)
// Lowercase means the symbol is Local (only visible inside this file)
// ->st_info can be 3 options, STB_LOCAL,GLOBAL or WEAK
void print_symbol(t_symbol *saved_symbols, int symbol_count)
{
    
    // Sort in alphabetic order, selection sort

    int i = 0;  // iterate from start to end
    int j = 0; // iterate to find min
    int min_idx = 0;   // remember min pos

    i = 0;
    while (i < symbol_count) // for all structs
    {
        min_idx = i;
        j = i + 1;
        while (j < symbol_count)        // test remaining structs
        {
            if (nm_strcmp(saved_symbols[min_idx].name, saved_symbols[j].name) > 0)
            {
                min_idx = j;
            }  
            j++;
        }
        if (min_idx != i)
            swap(&saved_symbols[i], &saved_symbols[min_idx]);
        i++;
    }

    // Now print everything
    i = 0;
    while (i < symbol_count)
    {
        if (saved_symbols[i].value != 0)
        {
            printf("%016lx %c %s\n", saved_symbols[i].value, saved_symbols[i].type, saved_symbols[i].name);
        }
        else
        {
            printf("%16s %c %s\n", "", saved_symbols[i].type, saved_symbols[i].name);
        }
        i++;
    }
}


char get_symbol_type(Elf64_Sym *current_symbol, Elf64_Shdr *sectionheader)
{
    char symbol_type;
    Elf64_Shdr *dest_section;

    symbol_type = 'U';
    if (current_symbol->st_shndx == SHN_UNDEF) // Undefined
    {
        symbol_type = 'U';
    }
    else if (current_symbol->st_shndx == SHN_ABS)
    {
        symbol_type = 'A';
    }
    else if (current_symbol->st_shndx == SHN_COMMON)
    {
        symbol_type = 'C';
    }
    else
    {
        dest_section = &sectionheader[current_symbol->st_shndx];
        if (dest_section->sh_type == SHT_NOBITS) 
        {
            symbol_type = 'B';
        }
        else if(dest_section->sh_flags & SHF_EXECINSTR)
        {
            symbol_type = 'T';
        }
        else if(dest_section->sh_flags & SHF_WRITE)
        {
            symbol_type = 'D';
        }
        else if (dest_section->sh_flags & SHF_ALLOC)
        {
            symbol_type = 'R';
        }
    }

    // Weak symbols are special: 'W' if defined (has a section), 'w' if undefined
    if (ELF64_ST_BIND(current_symbol->st_info) == STB_WEAK)
    {
        if (symbol_type == 'U')
            symbol_type = 'w';
        else
            symbol_type = 'W';
    }
    // If it's a local symbol, it should be lowercase
    else if (ELF64_ST_BIND(current_symbol->st_info) == STB_LOCAL)
    {
        if (symbol_type != '?') // Safety check (sometimes this symbol appear for unknown types)
            symbol_type += 32;
    }
    return (symbol_type);
}


int handle64(void *memorymap)
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
        return (-1);
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
    char        symbol_type;
    int j;

    t_symbol *saved_symbols; 
    
    saved_symbols = malloc(sizeof(t_symbol) * symbol_count);
    if (!saved_symbols)
        return (-1);

    
    // list_index = all eligible symbols, skipping the ones we dont need
    int list_index = 0;
    j = 0;
    while(j < symbol_count)
    {
        // We skip STT_FILE symbols (like "main.c") because they are internal metadata 
        // and standard nm doesn't show them by default
        if (ELF64_ST_TYPE(symboltable[j].st_info) == STT_FILE)
        {
            j++;
            continue;
        }

        symbol_name = sym_stringtable + symboltable[j].st_name;
        hexa_addr = symboltable[j].st_value;

        symbol_type = get_symbol_type(&symboltable[j], sectionheader);
        
        // Ensure the symbol has a name before doing anything
        if (symbol_name[0] != '\0')
        {
            if (hexa_addr != 0) 
            {
                // Print address + name
                // printf("%016lx %c %s\n", hexa_addr, symbol_type,symbol_name);
                saved_symbols[list_index].name = symbol_name;
                saved_symbols[list_index].type = symbol_type;
                saved_symbols[list_index].value = hexa_addr;
            } 
            else 
            {
                // Print 16 spaces (padding) + name to make it look like the real nm
                // %16s with "" prints 16 spaces
                saved_symbols[list_index].name = symbol_name;
                saved_symbols[list_index].type = symbol_type;
                saved_symbols[list_index].value = 0;
                // printf("%16s %c %s\n", "", symbol_type, symbol_name);
            }
            list_index++;
        }
        j++;
     }
    print_symbol(saved_symbols, list_index);
    free(saved_symbols);
    return (0);
}
