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

NAME = fdf
CC = gcc
FLAG = -Wall -Wextra -Werror 
FLAGS = -lmlx -framework OpenGL -framework AppKit

SRC_NAME = main.c
SRC_NAME_L = $(SRC_NAME)
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ_NAME_L = $(OBJ_NAME)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
OBJ_L = $(addprefix $(OBJ_DIR_L), $(OBJ_NAME_L))
INC = -I$(INC_DIR)

INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = srcs/
OBJ_DIR = obj/
SRC_DIR_L = $(SRC_DIR)
OBJ_DIR_L = $(OBJ_DIR)

ifneq ($(TARGETOS), Linux)
	FLAGS = -lm -lmlx -lXext -lX11 -L lib/ -I lib/
	FLAG = 
	CC = g++
endif

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@echo "######### LIB CREATED #########"
	$(CC) -o $(NAME) $(OBJ) $(FLAGS) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #######"
	$(CC) $(FLAG) -o $@ -c  $< $(INC)

linux: $(NAME)

swap:
	@cp -R ./lib ./lib1
	@rm -rf ./lib
	@cp -R ./lib2 ./lib
	@rm -rf ./lib2
	@cp -R ./lib1 ./lib2
	@rm -rf ./lib1
	@echo "#### SWAP LIB MLX FINISHED #####"

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
