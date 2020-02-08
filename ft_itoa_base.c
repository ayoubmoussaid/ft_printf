/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:34:33 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/01 10:37:33 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		nbr_length(long nb, unsigned int base)
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

char	*ft_atoi_neg(long value, int base, int size, const char *tab_base)
{
	char	*tab;
	int		i;

	tab = (char*)malloc(size + 2);
	value = -value;
	i = size;
	while (i >= 1)
	{
		tab[i] = tab_base[value % base];
		value = value / base;
		i--;
	}
	tab[i] = '-';
	tab[size + 1] = '\0';
	return (tab);
}

char	*ft_itoa_base(long value, int base)
{
	char		*tab;
	int			size;
	int			i;
	const char	*tab_base = "0123456789ABCDEF";

	size = nbr_length(value, base);
	if (base == 10 && value < 0)
		return (ft_atoi_neg(value, base, size, tab_base));
	if (value < 0)
		value = -value;
	tab = (char*)malloc(size + 1);
	i = size - 1;
	while (i >= 0)
	{
		tab[i] = tab_base[value % base];
		value = value / base;
		i--;
	}
	tab[size] = '\0';
	return (tab);
}
