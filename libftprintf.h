/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 10:41:10 by amoussai          #+#    #+#             */
/*   Updated: 2019/12/14 07:56:36 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct	s_vars
{
	int		chars;
	int		lalign;
	char	padd;
	int		len;
	int		tmp;
	int		prec;
	int		prefix;
	long	str_len;
	char	tab[2];
	char	*s;
	int		res;
}				t_vars;

int				ft_printf(const char *fmt, ...);
int				print_string(char *str, t_vars *elts);
int				nbr_length(long nb, unsigned int base);
char			*ft_itoa_base(long value, int base);
char			*ft_lowercase(char *str);
void			print_padding(t_vars *elts, int valid, int ok);
int				handle_multiple_flags(char *str, t_vars *elts, char *sign,
	int pre);
int				print_num(long var, t_vars *elts, char *str, int ok);
int				print_string(char *str, t_vars *elts);
int				print(long var, t_vars *elts, char type);
int				print_char(char c);
void			search_flags1(const char *fmt, t_vars *var, int *i);
void			search_flags2(const char *fmt, t_vars *var, int *i,
	va_list *arg_ptr);
void			verify_speciefier(const char *fmt, t_vars *var, int *i,
	va_list *arg_ptr);
void			initilize_vars(t_vars *var, int x);
int				print_character(char str, t_vars *elts);
#endif
