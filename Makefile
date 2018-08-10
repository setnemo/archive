CLIENT=client

SERVER=server

CC=gcc

FLAGS=-Wall -Wextra -Werror -I include -g

CLIENT_LINKER_FLAGS=-lreadline

SERVER_LINKER_FLAGS=-lpthread

SAM_LIB=external/SAM/samlib

SAM_LFLAGS = `sdl-config --libs`

VPATH=src

all: $(CLIENT) $(SERVER)

CLIENT_SRC_FILES = main.c					\
				   send_text_command.c		\

CLIENT_SRC=$(addprefix client/, $(CLIENT_SRC_FILES))

CLIENT_BINS=$(addprefix bin/, $(CLIENT_SRC:.c=.o))

SERVER_SRC_FILES = command_handler.c		\
				   connection_receiver.c	\
				   commands/test.c			\
				   commands/sound.c			\

SERVER_SRC=$(addprefix server/, $(SERVER_SRC_FILES))

SERVER_BINS=$(addprefix bin/, $(SERVER_SRC:.c=.o))

bin/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(FLAGS) -c -o $@ $<

$(SAM_LIB):
	make -C $(shell dirname $@)

$(CLIENT): $(CLIENT_BINS) $(SAM_LIB)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_LINKER_FLAGS) $(CLIENT_BINS) $(SAM_LIB)\
		$(SAM_LFLAGS)

$(SERVER): $(SERVER_BINS)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_LINKER_FLAGS) $(SERVER_BINS)

clean:
	/bin/rm -f $(CLIENT_BINS) $(SERVER_BINS)
	make -C $(shell dirname $(SAM_LIB)) clean

fclean: clean
	/bin/rm -f $(CLIENT) $(SERVER)
	make -C $(shell dirname $(SAM_LIB)) fclean

re: fclean all

.PHONY: all clean fclean re
