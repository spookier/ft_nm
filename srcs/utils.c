#include "utils.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>     // write

void swap(t_symbol *a, t_symbol *b)
{
    t_symbol tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int nm_strcmp(const char *s1, const char *s2)
{
        int i;
        int j;
        int c1;
        int c2;
        
        i = 0;
    j = 0;
    while (1)
    {
        // Skip non-alphanumeric characters
        while (s1[i] && !ft_isalnum(s1[i]))
            i++;
        while (s2[j] && !ft_isalnum(s2[j]))
            j++;

        // Check if either reached end
        if (!s1[i] && !s2[j])
            break ;             // Both done -> Tie-breaker needed
        if (!s1[i])
            return (-1);       // s1 ended first -> s1 is smaller
        if (!s2[j])
            return (1);        // s2 ended first -> s2 is smaller

        // Compare case-insensitive
        c1 = ft_tolower(s1[i]);
        c2 = ft_tolower(s2[j]);

        if (c1 != c2)
            return (c1 - c2);

        i++;
        j++;
    }
    // If we reach here, the "clean" versions are identical
        return (ft_strcmp((char *)s1, (char *)s2));
}

void print_symbol(t_symbol *saved_symbols, int symbol_count, int is_64bit)
{
    int i;
    int j;
    int min_idx;
    int pad;

    // Sort in alphabetic order, selection sort
    i = 0;
    while (i < symbol_count)
    {
        min_idx = i;
        j = i + 1;
        while (j < symbol_count)
        {
            if (nm_strcmp(saved_symbols[min_idx].name, saved_symbols[j].name) > 0)
                min_idx = j;
            j++;
        }
        if (min_idx != i)
            swap(&saved_symbols[i], &saved_symbols[min_idx]);
        i++;
    }

    // Print everything
	if (is_64bit == 1)
		pad = 16;
	else
		pad = 8;

	i = 0;
    while (i < symbol_count)
    {
        if (saved_symbols[i].value != 0)
            ft_put_hex_padded(saved_symbols[i].value, pad);
        else
            ft_put_spaces(pad);
			
        write(1, " ", 1);
        write(1, &saved_symbols[i].type, 1);
        write(1, " ", 1);
        ft_printf("%s\n", saved_symbols[i].name);
        i++;
    }
}