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

int nbr_length(long nb,unsigned int base)
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

char	*ft_itoa_base(long value, int base)
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

int shitty_code_for_multiple_flags(char *str, t_vars *elts, char *sign)
{
	int lon = ft_strlen(str);
	int longueur = 0;
	int x;

	x = elts->prec;
	longueur = elts->len > elts->prec ? elts->len : elts->prec;
	longueur = longueur > lon ? longueur : lon;
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
	if ((lon == longueur || x == longueur) && sign)
		longueur++;
	return (longueur);
}

int to_fix_precision(char *str, size_t *len, t_vars *elts, char *sign)
{
	elts->len = elts->prec;
	elts->padd = '0';
	*len = ft_strlen(str);
	return (!sign ? 0 : 1);
}

int print_decimal(long var, t_vars *elts, char *str, int ok)
{
	size_t len;
	int to_check;
	char *sign = 0;

	if (ok && (int)var < 0)
		sign = "-";
	to_check = elts->len;
	if (elts->prec != -1)
		to_check = elts->prec;
	if (elts->prec != -1 && elts->len != 0) //i hate this ...
		return (shitty_code_for_multiple_flags(str, elts, sign));
	len = !sign ? ft_strlen(str) : ft_strlen(str) + 1;
	if (elts->prec != -1 && elts->len == 0) //fixing the precision thing with zeros
		to_check += to_fix_precision(str, &len, elts, sign);
	elts->len -= len;
	if (sign && ft_strlen(str) == len)
		len++;
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

int print(long var, t_vars *elts, char type)
{
	char *str;

	if (type == 'd' || type == 'i')
	{
		str = (int)var < 0 ? ft_itoa_base(-(int)var, 10) : ft_itoa_base((int)var, 10);
		return (print_decimal(var, elts, str, 1));
	}
	if (type == 'u')
		return (print_decimal(var, elts, ft_itoa_base((unsigned int)var, 10), 0));
	if (type == 'x')
		return (print_decimal(var, elts, ft_lowercase(ft_itoa_base((unsigned int)var, 16)), 0));
	if (type == 'X')
		return (print_decimal(var, elts, ft_itoa_base((unsigned int)var, 16), 0));
	if (type == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (print_decimal(var, elts, ft_lowercase(ft_itoa_base((long)var, 16)), 0) + 2);
	}
	return (0);
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
		else if (fmt[i] == 'd' || fmt[i] == 'i' || fmt[i] == 'u' || fmt[i] == 'x' || fmt[i] == 'X' || fmt[i] == 'p')
		{
			var.chars += print(va_arg(arg_ptr, long), &var, fmt[i]);
			i++;
		}
		else if (fmt[i] == 's')
		{
			var.chars += print_string(va_arg(arg_ptr, char *), &var);
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
		int x = ft_printf("|%05.8x|\n",a);
		int y = printf("|%05.8x|\n",a);
		printf("%d\n%d\n", x, y);
		printf("\n==================\n");
	}
	return (0);
}
//cspdiuxX%
//%011.5d
//%-10.5d
//pointer still has some freaking stupid shit ... with flags