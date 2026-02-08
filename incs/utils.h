#ifndef UTILS_H
# define UTILS_H

#include <stdint.h>

typedef struct s_symbol
{
    char        *name;
    uint64_t    value;		// can hold both sizes (32 / 64)
    char        type;
} t_symbol;

void swap(t_symbol *a, t_symbol *b);
int nm_strcmp(const char *s1, const char *s2);
void print_symbol(t_symbol *saved_symbols, int symbol_count, int is_64bit);

#endif
