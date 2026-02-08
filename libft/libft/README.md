
# libft

Libft is a library of useful functions written in C, designed to help you write your own programs more quickly and efficiently
It involves recoding several functions from the standard C library, as well as implementing new functions

It includes implementations of common functions like strlen, strcpy, memset, and atoi, as well as some more specialized functions like linked list manipulation and string formatting


The Libft project is divided into three main parts:

1. Part 1: Recode several functions from the standard C library, including functions for manipulating strings, memory, and characters
2. Part 2: Implement additional functions that are not part of the standard library, such as functions for manipulating linked lists, binary trees, and other data structures
3. Bonus: Implement additional functions that are not required for the project but demonstrate advanced programming skills, such as functions for parsing command-line arguments or working with regular expressions

## Installation

To use libft in your own projects, simply clone the repository and compile it with the Makefile provided:

```bash
git clone https://github.com/spookier/libft.git
cd libft
make
```

This will generate a static library called libft.a that you can link to your own programs.


## Usage

To use libft in your own programs, include the appropriate header files and link to the libft.a library:

```c
#include "libft.h"

int main(void)
{
    char *str = "Hello, world!";
    ft_putstr(str, 1);
    return 0;
}
```
This program uses the ft_putstr_fd function from libft to print a string to the file descriptor 1

To compile your project with libft, add -L /path/to/libft -lft to your compiler flags

## Features

- ft_memset: fill a block of memory with a specified value
- ft_bzero: set a block of memory to zero
- ft_memcpy: copy a block of memory from one location to another
- ft_memccpy: copy a block of memory from one location to another until a specified character is found
- ft_memmove: copy a block of memory from one location to another, handling overlapping regions
- ft_memchr: find the first occurrence of a character in a block of memory
- ft_memcmp: compare two blocks of memory
- ft_strlen: get the length of a string
- ft_strlcpy: copy a string, truncating if necessary
- ft_strlcat: concatenate two strings, truncating if necessary
- ft_strchr: find the first occurrence of a character in a string
- ft_strrchr: find the last occurrence of a character in a string
- ft_strncmp: compare two strings
- ft_atoi: convert a string to an integer
- ft_isalpha: check if a character is an alphabetic character
- ft_isdigit: check if a character is a digit
- ft_isalnum: check if a character is an alphanumeric character
- ft_isascii: check if a character is an ASCII character
- ft_isprint: check if a character is printable
- ft_toupper: convert a character to uppercase
- ft_tolower: convert a character to lowercase
- ft_calloc: allocate memory and initialize it to zero
- ft_strdup: duplicate a string
- ft_substr: extract a substring from a string
- ft_strjoin: concatenate two strings
- ft_strtrim: remove leading and trailing whitespace from a string
- ft_split: split a string into an array of substrings
- ft_itoa: convert an integer to a string
- ft_strmapi: apply a function to each character in a string
- ft_putchar_fd: output a character to a file descriptor
- ft_putstr_fd: output a string to a file descriptor
- ft_putendl_fd: output a string followed by a newline to a file descriptor
- ft_putnbr_fd: output an integer to a file descriptor
