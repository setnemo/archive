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
FLAGS = -std=c99

SRC_NAME = main.c
OBJ_NAME = $(SRC_NAME:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
INC = -I$(INC_DIR)

INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = srcs/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@echo "##### START MY LIB CREATE #####"
	@make -C $(LIB_DIR) --silent
	@echo "##### LIB CREATED #####"
	@gcc -o $(NAME)  $(OBJ) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #####"
	@gcc $(FLAGS) -o $@ -c  $< $(INC)

clean:
	@make -C $(LIB_DIR) clean --silent
	@rm -f $(OBJ)
	@echo "##### REMOVE OBJECT FILES #####"

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@rm -f $(NAME)
	@echo "##### REMOVE BINARY FILES #####"

re: fclean all

.PHONY: clean fclean all re