#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

int	params_nbr(const char *format)
{
	int counter;
	char	*ptr;

	counter = 0;
	ptr = (char*)format;
	while ((ptr = ft_strchr(ptr, '%')) != NULL)
	{
		if (*(ptr + 1) == 'd' || *(ptr + 1) == 'c' || *(ptr + 1) == 'p' || *(ptr + 1) == 's'
		|| *(ptr + 1) == 'i' || *(ptr + 1) == 'u' || *(ptr + 1) == 'x' || *(ptr + 1) == 'X')
			counter++;
		ptr++;
	}
	return (counter);
}

void i_print(char *ptr, va_list args, int chars)
{
	if (*(ptr + 1) == 'd')
		ft_printint()
	return (0);
}

int main()
{
	printf("%d\n",params_nbr("%s%d%a%%%c%X"));
	return (0);
}
//cspdiuxX%