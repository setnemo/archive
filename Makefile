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
LINUX = linux
FLAG = -Wall -Wextra -Werror 
FLAGS_M = -lmlx -framework OpenGL -framework AppKit
FLAGS_L = -lmlx -lXext -lX11

SRC_NAME = main.c
OBJ_NAME = $(SRC_NAME:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
OBJ_L = $(addprefix $(OBJ_DIR_L), $(OBJ_NAME_L))
INC = -I$(INC_DIR)

INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = srcs/
OBJ_DIR = obj/
SRC_DIR_L = $(SRC_DIR)
OBJ_DIR_L = $(OBJ_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@echo "######### LIB CREATED #########"
	@gcc -o $(NAME)  $(OBJ) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #######"
	@gcc $(FLAG) $(FLAGS_M) -o $@ -c  $< $(INC)

linux: $(LINUX)

$(LINUX): $(OBJ_L)
	@make -C $(LIB_DIR) --silent
	@echo "######### LIB CREATED #########"
	@gcc -o $(NAME)  $(OBJ_L) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR_L)%.o: $(SRC_DIR_L)%.c
	@mkdir -p $(OBJ_DIR_L)
	@echo "##### LINKING" [ $@ ] " #######"
	@gcc $(FLAG) $(FLAGS_L) -o $@ -c  $< $(INC)

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
