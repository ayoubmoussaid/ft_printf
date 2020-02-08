/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:34:54 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/07 08:38:33 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	initilize_vars(t_vars *var, int x)
{
	if (x)
		var->chars = 0;
	var->lalign = 0;
	var->padd = ' ';
	var->len = 0;
	var->prec = -1;
	var->prefix = 0;
}

int		ft_printf(const char *fmt, ...)
{
	va_list	arg_ptr;
	int		i;
	t_vars	var;

	i = 0;
	initilize_vars(&var, 1);
	va_start(arg_ptr, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
		{
			var.chars += print_char(fmt[i++]);
			continue ;
		}
		i++;
		search_flags1(fmt, &var, &i);
		search_flags2(fmt, &var, &i, &arg_ptr);
		verify_speciefier(fmt, &var, &i, &arg_ptr);
	}
	va_end(arg_ptr);
	return (var.chars);
}
