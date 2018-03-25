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

NAME = lem-in
CC = gcc 
WWW = -Wall -Wextra -Werror 

SRC_NAME = 	main.c\
			cleaning.c\
			cleaning_next.c\
			validation.c\
			read_rooms.c\
			check_coords.c\
			find_ways.c\
			solve_ways.c\
			calculate.c\
			sort_ants.c\
			for_norm_mf.c\
			manage_flags.c\
			printresult.c\
			for_norm_mf_last.c

OBJ_NAME = $(SRC_NAME:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
INC = -I$(INC_DIR)

INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = srcs/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@echo "######### LIB CREATED #########"
	@$(CC) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #######"
	@$(CC) $(WWW) -o $@ -c  $< $(INC)

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
