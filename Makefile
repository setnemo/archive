CLIENT=client

SERVER=server

CC=gcc

FLAGS=-Wall -Wextra -Werror -I include -g

CLIENT_LINKER_FLAGS=`pkg-config --libs pocketsphinx sphinxbase`

SERVER_LINKER_FLAGS=-lpthread -lcurl

CLIENT_COMP_FLAGS=`pkg-config --cflags pocketsphinx sphinxbase` \
					-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
					-DDICTDIR=\"$(shell pwd)/src/client/voice_recognition/\"

SAM_LIB=external/sam/libsam.a

SAM_LFLAGS = `sdl-config --libs`

CJSON_LIB=external/cJSON/libcjson.a

SPHINX_LIB = external/sphinx/libsphinx.a

SPHINX_FLAGS = -Wall -Wextra -Werror -I include -g \
			   `pkg-config --cflags pocketsphinx sphinxbase` \
			   -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
			   -DDICTDIR=\"$(shell pwd)/src/client/voice_recognition/\"

CONFIG_FILE=include/server/config.h

VPATH=src

all: $(CLIENT) $(SERVER)

CLIENT_SRC_FILES = main.c									\
				   send_text_command.c						\
				   voice_recognition/voice_recognition.c	\

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
	$(CC) $(FLAGS) $(CLIENT_COMP_FLAGS) -c -o $@ $<

$(SAM_LIB):
	make -C $(shell dirname $@)

$(CJSON_LIB):
	make -C $(shell dirname $@)

$(SPHINX_LIB):
	make -C $(shell dirname $@)

$(shell dirname $(CONFIG_FILE))/.env: $(shell dirname $(CONFIG_FILE))/.env.example
	cp $< $@

$(CONFIG_FILE): $(shell dirname $(CONFIG_FILE))/.env
	cd $(shell dirname $@); /bin/bash ./$(shell basename $@).gen.sh

$(CLIENT): $(CLIENT_BINS) $(SAM_LIB) $(SPHINX_LIB)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_BINS) $(SAM_LIB) $(SPHINX_LIB)\
		$(SAM_LFLAGS) $(SPHINX_FLAGS) $(CLIENT_LINKER_FLAGS)

$(SERVER): $(CONFIG_FILE) $(SERVER_BINS) $(CJSON_LIB)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_BINS) $(CJSON_LIB) $(SERVER_LINKER_FLAGS)

clean:
	/bin/rm -f $(CLIENT_BINS) $(SERVER_BINS)
	make -C $(shell dirname $(SAM_LIB)) clean
	make -C $(shell dirname $(CJSON_LIB)) clean
	make -C $(shell dirname $(SPHINX_LIB)) clean

fclean: clean
	/bin/rm -f $(CLIENT) $(SERVER) $(CONFIG_FILE)
	make -C $(shell dirname $(SAM_LIB)) fclean
	make -C $(shell dirname $(SPHINX_LIB)) fclean

re: fclean all

web_client:
	@echo Starting web server
	nohup php -S 0.0.0.0:8888 -t bonus &

run: $(SERVER) $(CLIENT) web_client
	@echo Starting JOPA server
	./$(SERVER)

.PHONY: all clean fclean re web_client run
