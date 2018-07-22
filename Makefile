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

NAME = game_2048
CC = gcc 
WWW = -Wall -Wextra -Werror 
FLAGS = -lncurses 

SRC_NAME = 	main.c\
			gets.c\
			moves.c\
			while.c\
			summ.c\
			keys.c\
			init.c\
			adds.c\
			score.c\
			game_win.c\
			game_over.c\
			greeting.c\
			pause.c

OBJ_NAME = $(SRC_NAME:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
INC = -I$(INC_DIR)
INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = srcs/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	# @make -C $(LIB_DIR) --silent
	@echo "######### LIB CREATED #########"
	$(CC) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft $(FLAGS) 
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #######"
	$(CC) $(WWW) -o $@ -c  $< $(INC)

norm:
	@norminette ./libft/include
	@norminette ./libft/src
	@norminette ./include
	@norminette ./srcs

clean:
	# @make -C $(LIB_DIR) clean --silent
	@rm -f $(OBJ)
	@echo "##### REMOVE OBJECT FILES #####"

fclean: clean
	# @make -C $(LIB_DIR) fclean --silent
	@rm -f $(NAME)
	@echo "##### REMOVE BINARY FILES #####"

re: fclean all

.PHONY: clean fclean all re