#include "../../incs/ft_printf.h"

// Prints a hex number zero-padded to 'width' characters
// e.g. ft_put_hex_padded(0x4ba0, 16) -> "00000000000004ba0"
// Works by filling a buffer from right to left,
// extracting one hex digit at a time
void	ft_put_hex_padded(uint64_t val, int width)
{
	char	buf[17];
	char	*hex;
	int		pos;

	hex = "0123456789abcdef";
	pos = width - 1;
	while (pos >= 0)
	{
		// val & 0xf isolates the last 4 bits (one hex digit, 0-15)
		// then we use it as an index into the hex string
		buf[pos] = hex[val & 0xf];
		// shift right by 4 bits to move to the next hex digit
		val = val >> 4;
		pos--;
	}
	write(1, buf, width);
}

void	ft_put_spaces(int n)
{
	while (n-- > 0)
		write(1, " ", 1);
}
