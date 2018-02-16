#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 20:34:52 by apakhomo          #+#    #+#              #
#    Updated: 2017/11/07 20:34:54 by apakhomo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
NAME = sdb
FLAGS = -Wall -Wextra -Werror -std=c99

SRC_NAME =	main.c\
			read_config.c\
			dns.c\
			support_func.c\
			get_next_line.c

OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
INC = -I$(INC_DIR)

INC_DIR = include/
SRC_DIR = srcs/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ)
	@echo "##### COMPILING FINISHED #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #####"
	@gcc $(FLAGS) -o $@ -c  $< $(INC)

clean:
	@rm -f $(OBJ)
	@echo "##### REMOVE OBJECT FILES #####"

fclean: clean
	@rm -f $(NAME)
	@echo "##### REMOVE BINARY FILES #####"

re: fclean all

.PHONY: clean fclean all re