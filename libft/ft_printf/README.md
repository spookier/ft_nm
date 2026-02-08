
# ft_printf

ft_printf is a project that involves recoding the standard printf function in C programming language

The function takes a format string as its first argument, followed by optional arguments that will be inserted into the format string at the corresponding format specifiers.


The ft_printf function must support the following format specifiers:

- %c: character
- %s: string
- %p: pointer
- %d: signed integer
- %i: signed integer
- %u: unsigned integer
- %x: hexadecimal integer (lowercase)
- %X: hexadecimal integer (uppercase)
- %%: percentage sign


## Installation

To use ft_printf, simply clone the repository and compile it with your project:

```bash
git clone https://github.com/spookier/ft_printf.git
cd ft_printf
make
```
This will generate a static library called libftprintf.a that you can link with your project


## Usage

Using ft_printf is very similar to using the standard printf function

The function takes a format string and a list of arguments, and formats the string according to the specified format specifiers

Here's an example:

```c
#include "ft_printf.h"

int main() {
    ft_printf("Hello, %s! The answer is %d.\n", "world", 42);
    return 0;
}
```

This will print the following output to the console:
```
Hello, world! The answer is 42.
```

The function supports a wide range of format specifiers, including %c, %s, %p, %d, %i, %u, %x, and %X
