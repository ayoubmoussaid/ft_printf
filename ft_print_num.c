/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:43:06 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/14 07:55:40 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		handle_multiple_flags(char *str, t_vars *elts, char *sign, int pre)
{
	int	lon;
	int	x;

	elts->str_len = ft_strlen(str);
	x = elts->prec;
	lon = elts->len > elts->prec ? elts->len : elts->prec;
	lon = lon > elts->str_len ? lon : elts->str_len;
	elts->len -= elts->prec < elts->str_len ? elts->str_len : elts->prec;
	elts->len -= (sign ? 1 : 0) + pre;
	elts->prec -= elts->str_len;
	while (elts->lalign == 0 && elts->len-- >= 0)
		ft_putchar_fd(' ', 1);
	if (elts->prefix == 1)
		ft_putstr_fd("0x", 1);
	if (sign)
		ft_putchar_fd(*sign, 1);
	while (elts->prec-- > 0)
		ft_putchar_fd('0', 1);
	while (*str)
		ft_putchar_fd(*str++, 1);
	while (elts->lalign == 1 && elts->len-- >= 0)
		ft_putchar_fd(' ', 1);
	lon += (elts->str_len == lon || x == lon) && sign ? 1 : 0;
	lon += (elts->prefix ? 2 : 0);
	return (lon);
}

int		to_fix_precision(char *str, t_vars *elts, char *sign)
{
	elts->len = elts->prec + (elts->prefix ? 2 : 0);
	elts->padd = '0';
	elts->str_len = ft_strlen(str) + (elts->prefix ? 2 : 0);
	return (!sign ? 0 : 1);
}

size_t	ret_value(size_t str_len, int prefix, char *sign)
{
	size_t var;

	var = !sign ? str_len : str_len + 1;
	var += prefix ? 2 : 0;
	return (var);
}

void	do_print_dec(t_vars *elts, char *str, char *sign)
{
	if (sign && ft_strlen(str) == (size_t)elts->str_len)
		elts->str_len++;
	if (elts->padd == ' ')
		print_padding(elts, 0, 0);
	if (elts->prefix == 1)
		ft_putstr_fd("0x", 1);
	if (sign)
		ft_putchar_fd(*sign, 1);
	if (elts->padd == '0')
		print_padding(elts, 0, 0);
	while (*str)
		ft_putchar_fd(*str++, 1);
	print_padding(elts, 1, 0);
}

int		print_num(long var, t_vars *elts, char *str, int ok)
{
	int		to_check;
	char	*sign;

	sign = 0;
	if (var == 0 && elts->prec == 0)
		str = "";
	if (ok && (int)var < 0)
		sign = "-";
	to_check = elts->len;
	if (elts->prec != -1)
		to_check = elts->prec + (elts->prefix ? 2 : 0);
	if (elts->prec != -1 && elts->len != 0)
		return (handle_multiple_flags(str, elts, sign, elts->prefix ? 2 : 1));
	elts->str_len = ret_value(ft_strlen(str), elts->prefix, sign);
	if (elts->prec != -1 && elts->len == 0)
		to_check += to_fix_precision(str, elts, sign);
	elts->len -= elts->str_len;
	do_print_dec(elts, str, sign);
	return ((int)elts->str_len > to_check ? (int)elts->str_len : to_check);
}
