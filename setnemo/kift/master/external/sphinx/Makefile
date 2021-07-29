NAME = libsphinx.a

FLAGS = -Wall -Wextra -Werror -g \
		`pkg-config --cflags pocketsphinx sphinxbase` \
		-DDICTDIR=\"$(shell pwd)/../src/client/voice_recognition/\"

SRCS = recognize_from_mic.c

BINS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	ar rcu $(NAME) $(BINS)
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
