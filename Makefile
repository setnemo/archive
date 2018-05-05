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

NAME = asm
CC = gcc 
WWW = -Wall -Wextra -Werror 

SRC_NAME = 	main.c\
			read_input.c\
			header_comment.c\
			header_name.c\
			labels.c\
			split_lines.c\
			check_instructions.c\
			check_instructions2.c\
			op.c\
			cleaning_tree1.c\
			cleaning_tree2.c\
			to_file_func1.c\
			to_file_func2.c\
			to_file_func3.c\
			to_file_func4.c\
			to_file_func5.c

OBJ_NAME = $(SRC_NAME:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
INC = -I$(INC_DIR)

INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = srcs/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) -j4 --silent
	@echo "######### LIB CREATED #########"
	@$(CC) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #######"
	@$(CC) $(WWW) -o $@ -c  $< $(INC)

delcor:
	@find . -type f -name "*.cor" -delete
	@echo "####### REMOVE .COR FILES #######"

clean:
	@make -C $(LIB_DIR) clean --silent
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "###### REMOVE OBJECT FILES ######"

fclean: clean delcor
	@make -C $(LIB_DIR) fclean --silent
	@rm -f $(NAME)
	@echo "###### REMOVE BINARY FILES ######"

re: fclean all

.PHONY: clean fclean all re
