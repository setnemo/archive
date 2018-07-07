NAME = sniffer
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGLP = -lpcap 

SRC_NAME =	main.c\
			manage.c\
			daemon.c\
			cli.c\
			sniffer.c\
			utils.c\
			save_data.c\
			show_data.c

OBJ_NAME = $(SRC_NAME:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))
INC = -I$(INC_DIR)

INC_DIR = include/
SRC_DIR = srcs/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(FLAGLP) 
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### LINKING" [ $@ ] " #######"
	$(CC) -o $@ -c  $< $(INC) $(FLAGS) 

clean:
	@rm -f $(OBJ)
	@echo "##### REMOVE OBJECT FILES #####"

fclean: clean
	@rm -f $(NAME)
	@echo "##### REMOVE BINARY FILES #####"

re: fclean all

.PHONY: clean fclean all re