/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:06 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/14 08:03:33 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

char	*ft_lowercase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	print_padding(t_vars *elts, int valid, int ok)
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

int		print(long var, t_vars *elts, char type)
{
	if (type == 'd' || type == 'i')
	{
		if ((int)var == INT_MIN)
			elts->s = ft_strdup("2147483648");
		else
			elts->s = (int)var < 0 ? ft_itoa_base(-(int)var, 10) :
				ft_itoa_base((int)var, 10);
	}
	if (type == 'u')
		elts->s = ft_itoa_base((unsigned int)var, 10);
	if (type == 'x' || type == 'X' || type == 'p')
	{
		elts->s = ft_itoa_base(type == 'p' ? (unsigned long)var :
			(unsigned int)var, 16);
		if (type == 'x' || type == 'p')
			elts->s = ft_lowercase(elts->s);
		if (type == 'p')
			elts->prefix = 1;
	}
	elts->res = print_num(var, elts, elts->s, (type == 'd' || type == 'i') ?
		1 : 0);
	free(elts->s);
	return (elts->res);
}
