CLIENT=client

SERVER=server

FLAGS=-Wall -Wextra -Werror -I include

CLIENT_LINKER_FLAGS=-lreadline

SERVER_LINKER_FLAGS=-lpthread

CC=gcc

VPATH=src

all: $(CLIENT) $(SERVER)

CLIENT_SRC_FILES = main.c					\
				   send_text_command.c		\

CLIENT_SRC=$(addprefix client/, $(CLIENT_SRC_FILES))

CLIENT_BINS=$(addprefix bin/, $(CLIENT_SRC:.c=.o))

SERVER_SRC_FILES = command_handler.c		\
				   connection_receiver.c	\
				   commands/test.c			\

SERVER_SRC=$(addprefix server/, $(SERVER_SRC_FILES))

SERVER_BINS=$(addprefix bin/, $(SERVER_SRC:.c=.o))

bin/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(FLAGS) -c -o $@ $<

$(CLIENT): $(CLIENT_BINS)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_LINKER_FLAGS) $(CLIENT_BINS)

$(SERVER): $(SERVER_BINS)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_LINKER_FLAGS) $(SERVER_BINS)

clean:
	/bin/rm -f $(CLIENT_BINS) $(SERVER_BINS)

fclean: clean
	/bin/rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
