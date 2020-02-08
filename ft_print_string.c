/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:54:16 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/13 17:43:45 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		print_string(char *str, t_vars *elts)
{
	int len;
	int to_check;

	if (elts->prec == -1)
		elts->prec = INT_MAX;
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
	return (len > to_check ? len : to_check);
}

int		print_character(char str, t_vars *elts)
{
	int len;
	int to_check;

	if (elts->prec == -1)
		elts->prec = INT_MAX;
	len = 1;
	to_check = elts->len;
	len = len < elts->prec ? len : elts->prec;
	elts->len -= len;
	print_padding(elts, 0, 0);
	ft_putchar_fd(str, 1);
	print_padding(elts, 1, 0);
	return (len > to_check ? len : to_check);
}
