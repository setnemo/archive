NAME := asm

SRC := main.c read_input.c header_comment.c header_name.c labels.c split_lines.c \
 check_instructions.c check_instructions2.c

LIBHEAD := libft/includes

OBJ := $(SRC:.c=.o)

CFLAGS := -Wall -Wextra -Werror -I$(LIBHEAD)

LIBFT := libft/libftprintf.a

all: create_lib $(NAME)

create_lib: 
	@make -C libft -j8

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LIBFT) 
	@echo "\033[1;32mHere is ASM :P"

%.o: %.c
	@$(CC) -c -I$(LIBHEAD) -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all