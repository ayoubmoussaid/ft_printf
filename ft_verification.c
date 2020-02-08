/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:24:16 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/13 18:12:28 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	search_flags1(const char *fmt, t_vars *var, int *i)
{
	while (1)
	{
		if (fmt[*i] == '-')
			var->lalign = 1;
		else
			break ;
		(*i)++;
	}
	if (fmt[*i] == '0' && var->lalign != 1)
	{
		var->padd = '0';
		(*i)++;
	}
	else if (fmt[*i] == '0' && var->lalign == 1)
	{
		(*i)++;
		while (1)
		{
			if (fmt[*i] == '-' || fmt[*i] == '0')
				(*i)++;
			else
				break ;
		}
	}
}

void	search_flags2(const char *fmt, t_vars *var, int *i, va_list *arg_ptr)
{
	if (ft_isdigit(fmt[*i]))
		while (ft_isdigit(fmt[*i]))
			var->len = var->len * 10 + fmt[(*i)++] - '0';
	else if (fmt[*i] == '*')
	{
		var->len = va_arg(*arg_ptr, int);
		(*i)++;
		var->lalign = var->len < 0 ? 1 : var->lalign;
		var->len = var->len < 0 ? -var->len : var->len;
	}
	if (fmt[*i] == '.')
	{
		var->prec = 0;
		if (ft_isdigit(fmt[++(*i)]))
			while (ft_isdigit(fmt[*i]))
				var->prec = 10 * var->prec + fmt[(*i)++] - '0';
		else if (fmt[*i] == '*')
		{
			var->prec = va_arg(*arg_ptr, int);
			var->prec = var->prec < 0 ? -1 : var->prec;
			(*i)++;
		}
	}
}

void	verify_speciefier(const char *fmt, t_vars *var, int *i,
	va_list *arg_ptr)
{
	if (fmt[*i] == 'c')
	{
		if (var->prec != -1)
			var->prec = -1;
		var->chars += print_character((char)va_arg(*arg_ptr, int), var);
		(*i)++;
	}
	else if (fmt[*i] == 'd' || fmt[*i] == 'i' || fmt[*i] == 'u' ||
		fmt[*i] == 'x' || fmt[*i] == 'X' || fmt[*i] == 'p')
		var->chars += print(va_arg(*arg_ptr, long), var, fmt[(*i)++]);
	else if (fmt[*i] == 's')
	{
		var->chars += print_string(va_arg(*arg_ptr, char *), var);
		(*i)++;
	}
	else if (fmt[*i] == '%')
	{
		var->tab[0] = '%';
		var->tab[1] = '\0';
		var->prec += !var->prec ? 1 : 0;
		var->chars += print_string(var->tab, var);
		(*i)++;
	}
	initilize_vars(var, 0);
}
