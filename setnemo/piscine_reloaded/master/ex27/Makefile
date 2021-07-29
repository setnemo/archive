#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 09:59:38 by apakhomo          #+#    #+#              #
#    Updated: 2017/10/25 09:59:40 by apakhomo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_display_file
PATH = ft_display_file.c

all: $(NAME)

$(NAME):
	gcc -c $(PATH)
	gcc -o $(NAME) $(PATH)

clean:
	rm -f ft_display_file.o

fclean: clean
	rm -f $(NAME)

re: fclean all
