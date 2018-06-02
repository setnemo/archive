#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/04 13:41:34 by nkolosov          #+#    #+#              #
#    Updated: 2017/09/04 14:04:44 by nkolosov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
HEADNAMES = libft libft_structures get_next_line
PRINTF_HEADERS = ./includes/ft_printf.h \
				./includes/ft_printf_funcs.h \
				./includes/ft_printf_consts.h
INCDIR = ./includes
HEADERS = $(patsubst %, $(INCDIR)/%.h, $(HEADNAMES))
READFUNCS = get_next_line \
			read_lines
READFUNCDIR = ./readfuncs
DREADFUNCS = $(patsubst %, $(READFUNCDIR)/%, $(READFUNCS))
PRINTFUNCS = ft_putchar \
			ft_putstr \
			ft_putendl \
			ft_putnbr \
			ft_putnbrendl \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_print_word_tab \
			ft_print_num_tab \
			ft_log \
			ft_putnbr_uns_fd \
			ft_putnbr_uns
PRINTFUNCDIR = ./printfuncs
DPRINTFUNCS = $(patsubst %, $(PRINTFUNCDIR)/%, $(PRINTFUNCS))
PRINTF =	ft_printf \
			ft_printf_fd \
			length_converters \
			buffer_string_forming \
			params_set \
			params_tools \
			print_prefix \
			printers \
			types_char \
			types_numeric \
			types_octhex \
			types_binary \
			types_extra \
			types_float_f \
			types_float_e \
			types_float_g \
			types_float_a \
			tools1 \
			tools_bits \
			tools_float_fe_funcs \
			tools_float_ga_funcs \
			tools_float_universal \
			tools_float_convert_to_struct \
			tools_float_struct_managing \
			tools_float_round \
			types_float_a_get_float
PRNTFDIR = $(PRINTFUNCDIR)/ft_printf
DPRNTF = $(patsubst %, $(PRNTFDIR)/%, $(PRINTF))
STRFUNCS =	ft_strlen \
			ft_strcat \
			ft_strncat \
			ft_strlcat \
			ft_strcmp \
			ft_strncmp \
			ft_strstr \
			ft_strnstr \
			ft_strchr \
			ft_strrchr \
			ft_strclr \
			ft_strdup \
			ft_strcpy \
			ft_strncpy \
			ft_striter \
			ft_striteri \
			ft_strmap \
			ft_strmapi \
			ft_strequ \
			ft_strnequ \
			ft_strsub \
			ft_strjoin \
			ft_strsplit \
			ft_strtrim \
			ft_split_whitespaces \
			ft_strdupab \
			ft_strrev \
			ft_strupper \
			ft_rmdupsymb \
			is_integer \
			is_number
STRFDIR = ./strfuncs
DSTRFUNCS = $(patsubst %, $(STRFDIR)/%, $(STRFUNCS))
LISTFUNCS = ft_find_del \
			ft_list_to_string \
			ft_lstnew \
			ft_lstcontains \
			ft_lstdelone \
			ft_lstdel \
			ft_lstadd \
			ft_lstiter \
			ft_lstmap \
			ft_lstpushback
LISTFDIR = ./listfuncs
DLISTFUNCS = $(patsubst %, $(LISTFDIR)/%, $(LISTFUNCS))
MEMFUNCS =	ft_strnew \
			ft_strdel \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memccpy \
			ft_memmove \
			ft_memchr \
			ft_memalloc \
			ft_memdel \
			ft_memcmp
MEMFDIR = ./memfuncs
DMEMFUNCS = $(patsubst %, $(MEMFDIR)/%, $(MEMFUNCS))
CALCFUNCS = ft_atoi \
			ft_itoa_base_uns \
			ft_itoa \
			ft_swap \
			ft_factorial \
			ft_sqrt \
			ft_isprime \
			ft_sort_word_tab \
			ft_sort_num_tab \
			ft_count_digits \
			ft_itoa_base \
			ft_abs \
			ft_dsqrt \
			ft_count_digits_uns \
			long_mul \
			long_mul_base \
			long_mul_base_tools \
			ft_sign
CALCFDIR = ./calcfuncs
DCALCFUNCS = $(patsubst %, $(CALCFDIR)/%, $(CALCFUNCS))
CHARFUNCS = ft_isdigit \
			ft_isalpha \
			ft_isalnum \
			ft_isascii \
			ft_isupper \
			ft_islower \
			ft_isprint \
			ft_iswhitespace \
			ft_toupper \
			ft_tolower \
			hex_from_dec
CHARFDIR = ./charfuncs
DCHARFUNCS = $(patsubst %, $(CHARFDIR)/%, $(CHARFUNCS))
FILENAMES = $(DSTRFUNCS) \
			$(DPRINTFUNCS) \
			$(DLISTFUNCS) \
			$(DMEMFUNCS) \
			$(DCALCFUNCS) \
			$(DCHARFUNCS) \
			$(DPRNTF) \
			$(DREADFUNCS)
ODIR = ./obj
CFILES = $(patsubst %, %.c, $(FILENAMES))
OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))
FLAGS = -Wall -Wextra -Werror -O3

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

all: $(NAME)

$(NAME): $(ODIR) $(OFILES) $(HEADERS)
	@echo ${CYAN}[Compiling $(NAME)]${NC}
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo ${GREEN}"[========| $(NAME) is up to date. |========]"${NC}

$(ODIR)/%.o: %.c $(HEADERS)
	gcc $(FLAGS) -o $@ -c $< -I$(INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(STRFDIR)
	@mkdir -p $(ODIR)/$(PRINTFUNCDIR)
	@mkdir -p $(ODIR)/$(LISTFDIR)
	@mkdir -p $(ODIR)/$(MEMFDIR)
	@mkdir -p $(ODIR)/$(CALCFDIR)
	@mkdir -p $(ODIR)/$(CHARFDIR)
	@mkdir -p $(ODIR)/$(PRNTFDIR)
	@mkdir -p $(ODIR)/$(READFUNCDIR)

clean:
	@echo ${RED}[Removing $(NAME) *.o files]${NC}
	@/bin/rm -rf $(ODIR)

fclean: clean
	@echo ${RED}[Removing $(NAME)]${NC}
	@/bin/rm -f $(NAME)

re: fclean all
	
norm:
	@clear
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette $(CFILES) $(HEADERS) $(PRINTF_HEADERS)

main: $(NAME)
	gcc -o e -I $(INCDIR) -L. -lftprintf main.c

gitclean: clean
	find . -name "*.DS_Store*" -delete 
	find . -name "#*#" -delete
	@/bin/rm -f e

