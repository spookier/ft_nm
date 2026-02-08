#ifndef UTILS_H
# define UTILS_H

#include <stdint.h>

typedef struct s_symbol
{
    char        *name;
    uint64_t    value;
    char        type;
} t_symbol;

void swap(t_symbol *a, t_symbol *b);
int nm_strcmp(const char *s1, const char *s2);

#endif
