CLIENT=client

SERVER=server

CC=gcc

FLAGS=-Wall -Wextra -Werror -I include -g

CLIENT_LINKER_FLAGS=

SERVER_LINKER_FLAGS=-lpthread -lcurl

SAM_LIB=external/sam/libsam.a

SAM_LFLAGS = `sdl-config --libs`

CJSON_LIB=external/cJSON/libcjson.a

CONFIG_FILE=include/server/config.h

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
				   commands/screen_lock.c	\
				   commands/run_program.c	\
				   commands/screen_shot.c	\
				   commands/weather.c		\
				   commands/backlight.c		\
				   commands/play_music.c	\
				   commands/history.c		\

SERVER_SRC=$(addprefix server/, $(SERVER_SRC_FILES))

SERVER_BINS=$(addprefix bin/, $(SERVER_SRC:.c=.o))

bin/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(FLAGS) -c -o $@ $<

$(SAM_LIB):
	make -C $(shell dirname $@)

$(CJSON_LIB):
	make -C $(shell dirname $@)

$(CONFIG_FILE): $(shell dirname $(CONFIG_FILE))/.env
	cd $(shell dirname $@); /bin/bash ./$(shell basename $@).gen.sh

$(CLIENT): $(CLIENT_BINS) $(SAM_LIB)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_LINKER_FLAGS) $(CLIENT_BINS) $(SAM_LIB)\
		$(SAM_LFLAGS)

$(SERVER): $(CONFIG_FILE) $(SERVER_BINS) $(CJSON_LIB)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_LINKER_FLAGS) $(SERVER_BINS) $(CJSON_LIB)

clean:
	/bin/rm -f $(CLIENT_BINS) $(SERVER_BINS)
	make -C $(shell dirname $(SAM_LIB)) clean
	make -C $(shell dirname $(CJSON_LIB)) clean

fclean: clean
	/bin/rm -f $(CLIENT) $(SERVER) $(CONFIG_FILE)
	make -C $(shell dirname $(SAM_LIB)) fclean

re: fclean all

web_client:
	@echo Starting web server
	nohup php -S 0.0.0.0:8888 -t bonus &

run: $(SERVER) $(CLIENT) web_client
	@echo Starting JOPA server
	./$(SERVER)

.PHONY: all clean fclean re web_client run
