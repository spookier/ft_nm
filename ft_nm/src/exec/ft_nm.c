#include "../../include/ft_nm64.h"

int main(int argc, char **argv)
{
	if (start_parsing(argc, argv) == -1)
		return(-1);
	printf("[OK] end of program\n");
}