#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/27 08:51:56 by apakhomo          #+#    #+#              #
#    Updated: 2018/01/27 08:51:57 by apakhomo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror -O3
LIBFT = libft
DIR_S = src
DIR_O = temp
HEADER = include
SOURCES = 	conversions.c\
			core.c\
			fordigits.c\
			ft_printf.c\
			manage.c\
			managecharandhex.c\
			managestrandperc.c\
			pf_itoa.c\
			verify.c\

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p temp
	gcc $(FLAGS) -I./$(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
