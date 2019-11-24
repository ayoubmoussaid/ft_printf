#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"




typedef struct	s_vars
{
	int chars;
	int lalign;
	char padd;
	int len;
	int tmp;
	int prec;
}				t_vars;

int print_string(char *str, t_vars *elts);
/*int	params_nbr(const char *format)
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
}*/

int nbr_length(long long nb,unsigned int base)
{
	int i;

	i = 0;
	while (nb / base != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa_base(long long value, int base)
{
	int size = nbr_length(value, base);
	if (base == 10 && value < 0)
	{
		value = -value;
		char *tab = (char*)malloc(size+2);
		char *tab_base = "0123456789ABCDEF";
		int i = size;
		while (i >= 1)
		{
			tab[i] = tab_base[value % base];
			value = value / base;
			i--;
		}
		tab[i] = '-';
		tab[size+1] = '\0';
		return tab;
	}
	if (value < 0)
		value = -value;
	char *tab = (char*)malloc(size+1);
	char *tab_base = "0123456789ABCDEF";
	int i = size-1;
	while (i >= 0)
	{
		tab[i] = tab_base[value % base];
		value = value / base;
		i--;
	}
	tab[size] = '\0';
	return tab;
}

void	ft_putunbr_fd(long int n, int fd)
{
	unsigned int reste;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n / 10 == 0)
		ft_putchar_fd((n % 10) + 48, fd);
	if (n / 10 > 0)
	{
		reste = n % 10;
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(reste + 48, fd);
	}
}
char *ft_lowercase(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void print_padding(t_vars *elts, int valid, int ok)
{
	if (ok)
	{
		while (elts->len--)
			ft_putchar_fd(' ', 1);
	}
	if (elts->len > 0 && elts->lalign == valid)
	{
		while (elts->len--)
			ft_putchar_fd(elts->padd, 1);
	}
	if (elts->len > 0 && elts->lalign == valid)
	{
		while (elts->len--)
			ft_putchar_fd(' ', 1);
	}
}

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/

int print_char(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

/* int print_decimal(long var, t_vars *elts)
{
	int len;
	int to_check;
	char *str;

	str = ft_itoa_base((int)var, 10);
	len = ft_strlen(str);
	if (elts->prec != -1)
	{
		elts->padd = '0';
		elts->lalign = 0;
		elts->len = elts->prec;
	}
	else
		elts->prec = INT32_MAX;
	if (str == NULL)
		str = "";
	len = len < elts->prec ? len : elts->prec;
	to_check = elts->len;
	to_check += (int)var < 0 ? 1 : 0;
	elts->len -= ((int)var < 0 ? len - 1 : len);
	if ((int)var < 0 && elts->lalign == 1)
		ft_putchar_fd(*str++, 1);
	print_padding(elts, 0);
	while (*str)
		ft_putchar_fd(*str++, 1);
	print_padding(elts, 1);
	return (len > to_check ? len : to_check);
	 print_string(ft_itoa_base(var, 10), elts);
	return (var > 0 ? nbr_length(var, 10) : nbr_length(var, 10) + 1); 
} */

int shitty_code_for_multiple_flags(char *str, t_vars *elts, char *sign)
{
	int i = 0, j = 0, k = 0;
	int lon = ft_strlen(str);
	int longueur = 0;

	longueur = elts->len > lon ? elts->len : lon;
	elts->len -= elts->prec < lon ? lon : elts->prec;
	elts->len -= (sign ? 1 : 0);
	elts->prec -= lon;
	while (elts->len-- > 0 && elts->lalign == 0)
		ft_putchar_fd(' ', 1);
	if(sign)
	 	ft_putchar_fd(*sign, 1);
	while (elts->prec-- > 0)
		ft_putchar_fd('0', 1);
	while (*str)
		ft_putchar_fd(*str++, 1);
	while (elts->len-- >= 0 && elts->lalign == 1)
		ft_putchar_fd(' ', 1);
	if (lon == longueur && sign)
		longueur++;
	return (longueur);
}

int print_decimal(long var, t_vars *elts)
{
	int len;
	int to_check;
	char *str;
	char *sign = 0;

	if ((int)var < 0)
	{
		var = -var;
		sign = "-";
	}
	to_check = elts->len;
	if (elts->prec != -1)
		to_check = elts->prec;
	str = ft_itoa_base(var, 10);
	if (elts->prec != -1 && elts->len != 0) //i hate this ...
		return (shitty_code_for_multiple_flags(str, elts, sign));
	len = !sign ? ft_strlen(str) : ft_strlen(str) + 1;
	if (elts->prec != -1 && elts->len == 0) //fixing the precision thing with zeros
	{
		elts->len = elts->prec;
		elts->padd = '0';
		len = ft_strlen(str);
		to_check += (!sign ? 0 : 1);
	}
	elts->len -= len;
	//printf("\n%d -- %d\n", elts->len, len);
	/* if (sign)
		elts->len--; */
	//if (prefix) elts->len -= 2;
	if (elts->padd == ' ')
		print_padding(elts, 0, 0);
	if (sign)
		ft_putchar_fd(*sign, 1);
	if (elts->padd == '0')
		print_padding(elts, 0, 0);
	while (*str)
		ft_putchar_fd(*str++, 1);
	print_padding(elts, 1, 0);
	return (len > to_check ? len : to_check);
}

int print_pointer(long long var)
{
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(ft_lowercase(ft_itoa_base(var, 16)), 1);
	return (nbr_length(var, 16) + 2);
}

int print_string(char *str, t_vars *elts)
{
	int len;
	int to_check;

	if (elts->prec == -1)
		elts->prec = INT32_MAX;
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	to_check = elts->len;
	len = len < elts->prec ? len : elts->prec;
	elts->len -= len;
	print_padding(elts, 0, 0);
	while (*str && elts->prec--)
		ft_putchar_fd(*str++, 1);
	print_padding(elts, 1, 0);
	return ( len > to_check ? len : to_check );
}

int print_unsigned(long var, t_vars *elts)
{
	int len;
	int to_check;
	char *str;
	char *sign = 0;

	to_check = elts->len;
	if (elts->prec != -1)
		to_check = elts->prec;
	str = ft_itoa_base((unsigned int)var, 10);
	if (elts->prec != -1 && elts->len != 0) //i hate this ...
		return (shitty_code_for_multiple_flags(str, elts, sign));
	len = !sign ? ft_strlen(str) : ft_strlen(str) + 1;
	if (elts->prec != -1 && elts->len == 0) //fixing the precision thing with zeros
	{
		elts->len = elts->prec;
		elts->padd = '0';
		len = ft_strlen(str);
		to_check += (!sign ? 0 : 1);
	}
	elts->len -= len;
	if (elts->padd == ' ')
		print_padding(elts, 0, 0);
	if (sign)
		ft_putchar_fd(*sign, 1);
	if (elts->padd == '0')
		print_padding(elts, 0, 0);
	while (*str)
		ft_putchar_fd(*str++, 1);
	print_padding(elts, 1, 0);
	return (len > to_check ? len : to_check);
}

int print_smallhex(unsigned int var)
{
	ft_putstr_fd(ft_lowercase(ft_itoa_base(var, 16)), 1);
	return (nbr_length(var, 16));
}

int print_bighexa(unsigned int var)
{
	ft_putstr_fd(ft_itoa_base(var, 16), 1);
	return (nbr_length(var, 16));
}

int ft_printf(const char *fmt, ...)
{
	va_list arg_ptr;
	int i;
	t_vars var;

	i = 0;
	var.chars  = 0;
	var.lalign = 0;
	var.padd = ' ';
	var.len = 0;
	var.prec = -1;
	va_start(arg_ptr, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
		{
			ft_putchar_fd(fmt[i++], 1);
			var.chars++;
			continue ;
		}
		i++;
		while (1)
		{
			if (fmt[i] == '-')
				var.lalign = 1;
			else
				break ;
			i++;
		}
		if (fmt[i] == '0' && var.lalign != 1) //left align the sentence (to verify more)
		{
			var.padd = '0';
			i++;
		}
		else if(fmt[i] == '0' && var.lalign == 1)
		{
			i++;
			while (1)
			{
				if (fmt[i] == '-' || fmt[i] == '0')
					i++;
				else
					break ;
			}
		}
		if (ft_isdigit(fmt[i]))
			while (ft_isdigit(fmt[i]))
				var.len = var.len * 10 + fmt[i++] - '0';
		else if (fmt[i] == '*')
		{
			var.len = va_arg(arg_ptr, int);
			i++;
			if (var.len < 0)
			{
				var.len = -var.len;
				//var.lalign = !var.lalign;
			}
		}
		if (fmt[i] == '.') //precision calculation
		{
			i++;
			if (ft_isdigit(fmt[i])) 
			{
				var.prec = 0;
				while(ft_isdigit(fmt[i])) {
					var.prec = 10 * var.prec + fmt[i] - '0';
					i++;
				}
			}
			else if (fmt[i] == '*') {
				var.prec = va_arg(arg_ptr, int);
				if (var.prec < 0)
					var.prec = -1;
				i++;
			}
		}

		//absolute verification of the specifier.
		if (fmt[i] == 'c')
		{
			var.chars += print_char(va_arg(arg_ptr, int));
			i++;
		}
		else if (fmt[i] == 'd' || fmt[i] == 'i')
		{
			var.chars += print_decimal(va_arg(arg_ptr, int), &var);
			i++;
		}
		else if (fmt[i] == 'p')
		{
			var.chars += print_pointer(va_arg(arg_ptr, long long));
			i++;
		}
		else if (fmt[i] == 's')
		{
			var.chars += print_string(va_arg(arg_ptr, char *), &var);
			i++;
		}
		else if (fmt[i] == 'u')
		{
			var.chars += print_unsigned(va_arg(arg_ptr, unsigned int));
			i++;
		}
		else if (fmt[i] == 'x')
		{
			var.chars += print_smallhex(va_arg(arg_ptr, unsigned int));
			i++;
		}
		else if (fmt[i] == 'X')
		{
			var.chars += print_bighexa(va_arg(arg_ptr, unsigned int));
			i++;
		}
		else if (fmt[i] == '%')
		{
			ft_putchar_fd('%', 1);
			i++;
			var.chars++;
		}
	}
	va_end(arg_ptr);
	return (var.chars);
}

int main()
{
	int a = 5;
	char str[20];
	while(1)
	{
		scanf("%d", &a);
		int x = ft_printf("|%.0d|\n", a);
		int y = printf("|%.0d|\n", a);
		printf("%d\n%d\n", x, y);
		printf("\n==================\n");
	}
	return (0);
}
//cspdiuxX%
//%011.5d
//%-10.5d