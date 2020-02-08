# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 15:30:39 by amoussai          #+#    #+#              #
#    Updated: 2019/12/07 08:35:16 by amoussai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a
SRCS =	ft_itoa_base.c  ft_print.c  ft_print_num.c  ft_print_string.c  ft_printf.c ft_verification.c

OBJ =	$(SRCS:.c=.o)

FLAGS=-Wall -Werror -Wextra
CC=gcc
INCLUDE=libftprintf.h

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	mv ./libft/libft.a .
	mv libft.a libftprintf.a
	ar rcs $(NAME) $(OBJ)

bonus: re

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $< 

clean:
	$(MAKE) -C ./libft clean
	rm -f *.o
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -f $(NAME)
re: fclean all
