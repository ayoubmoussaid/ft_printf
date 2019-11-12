/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 10:40:42 by amoussai          #+#    #+#             */
/*   Updated: 2019/11/09 13:23:01 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	params_nbr(const char *format)
{
	int counter;
	char	*ptr;

	counter = 0;
	ptr = (char*)format;
	while ((ptr = ft_strchr(ptr, '%')) != NULL)
	{
		if (*ptr != *(ptr + 1))
			counter++;
	}
	return (counter);
}

void testit(const char *str)
{
	printf("%s",params_nbr(str);
}

/*int	ft_printf(const char *format, ...)
{
	va_list arg_ptr;
	va_list args_copy;
	int params;

	va_start(arg_ptr, format);
	va_copy(args_copy, arg_ptr);
	params = params_nbr;
}*/
