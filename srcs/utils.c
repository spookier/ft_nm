#include "utils.h"
#include <ctype.h>
#include <string.h>


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
        while (s1[i] && !isalnum(s1[i]))
            i++;
        while (s2[j] && !isalnum(s2[j]))
            j++;

        // Check if either reached end
        if (!s1[i] && !s2[j])
            break ;             // Both done -> Tie-breaker needed
        if (!s1[i])
            return (-1);       // s1 ended first -> s1 is smaller
        if (!s2[j])
            return (1);        // s2 ended first -> s2 is smaller

        // Compare case-insensitive
        c1 = tolower(s1[i]);
        c2 = tolower(s2[j]);

        if (c1 != c2)
            return (c1 - c2);

        i++;
        j++;
    }
    // If we reach here, the "clean" versions are identical
        return (strcmp(s1, s2));
}

