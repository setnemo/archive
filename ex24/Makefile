#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 09:49:10 by apakhomo          #+#    #+#              #
#    Updated: 2017/10/25 09:49:12 by apakhomo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

LIB = libft.a
SRCS = srcs/
INCLUDE = includes/
PATH = $(SRCS)ft_putchar.c $(SRCS)ft_putstr.c $(SRCS)ft_strcmp.c $(SRCS)ft_strlen.c $(SRCS)ft_swap.c
OBJECT = ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o

all: $(LIB)

$(LIB):
	gcc -c -I$(INCLUDE) $(PATH)
	ar rc $(LIB) $(OBJECT)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(LIB)

re: fclean all
