
# =========================    ASSEMBLER    =========================

ASM_NAME = asm
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

INC_DIR = asm_includes/
LIB_DIR = asm_libft/
SRC_DIR = asm_sources/
OBJ_DIR_ASM = asm_obj/

OBJ = $(addprefix $(OBJ_DIR_ASM), $(OBJ_NAME))
INC = -I$(INC_DIR)

# ========================= VIRTUAL MACHINE =========================

VM_NAME = corewar

HEADERS =	op \
			vm \
			structures \
			encurse

INCDIR = ./includes
VMSRCDIR = ./vm_sources
HFILES = $(patsubst %, $(INCDIR)/%.h, $(HEADERS))

VMCMDENCDIR = encurse
VMDENCNAMES = main_pic \
			  exit \
			  make_players_bar \
			  draw_map \
			  init_curse \
			  hotkey \
			  swap_cursor \
			  add_func_forb

VMCENCFILES = $(patsubst %, $(VMSRCDIR)/$(VMCMDENCDIR)/%.c, $(VMDENCNAMES))
VMOENCFILES = $(patsubst %, $(ODIR)/$(VMCMDENCDIR)/%.o, $(VMDENCNAMES))

VMCMDSRCDIR = commands
VMCMDFNAMES = 	proc_00_invalid \
				proc_01_live \
				proc_02_load \
				proc_03_store \
				proc_04_add \
				proc_05_sub \
				proc_06_and \
				proc_07_or \
				proc_08_xor \
				proc_09_zjmp \
				proc_10_ldi \
				proc_11_sti \
				proc_12_fork \
				proc_13_load_long \
				proc_14_ldi_long \
				proc_15_fork_long \
				proc_16_aff \
				proc_common

VMCCMDFILES = $(patsubst %, $(VMSRCDIR)/$(VMCMDSRCDIR)/%.c, $(VMCMDFNAMES))
VMOCMDFILES = $(patsubst %, $(ODIR)/$(VMCMDSRCDIR)/%.o, $(VMCMDFNAMES))

VMFILENAMES =	main \
				pre \
				errors \
				errors2 \
				globals \
				input_parsing \
				input_funcs \
				player_reading \
				player_parsing \
				print_tools \
				process_tools \
				cycle_tools \
				field_tools \
				commands

VMCFILES = $(patsubst %, $(VMSRCDIR)/%.c, $(VMFILENAMES)) $(VMCCMDFILES) $(VMCENCFILES)
VMOFILES = $(patsubst %, $(ODIR)/%.o, $(VMFILENAMES)) $(VMOCMDFILES) $(VMOENCFILES)


LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
FLAGS = -Wall -Wextra -Werror
LIBINCDIR = $(LIBDIR)/includes

ODIR = ./obj

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

all:
	@make -j $(ASM_NAME)
	@make -j $(VM_NAME)

$(ASM_NAME): $(OBJ)
	@make -C $(LIB_DIR) -j4 --silent
	@echo "######### LIB CREATED #########"
	@$(CC) -o $(ASM_NAME) $(OBJ) -L $(LIB_DIR) -lft
	@echo "##### COMPILING FINISHED ######"

$(OBJ_DIR_ASM)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR_ASM)
	@echo "##### LINKING" [ $@ ] " #######"
	@$(CC) $(WWW) -o $@ -c  $< $(INC)

$(OBJ_DIR_ASM):
	@mkdir -p $(OBJ_DIR_ASM)



$(VM_NAME): $(ODIR) $(HFILES) $(VMOFILES)
	@echo ${CYAN}[Compiling the $(VM_NAME) executable]${NC}
	gcc $(FLAGS) $(VMOFILES) $(LIBFT) -o $(VM_NAME) -lncurses
	@echo ${GREEN}"[========| $(VM_NAME) is up to date. |========]"${NC}

$(ODIR)/%.o: $(VMSRCDIR)/%.c $(HFILES) $(LIBFT)
	gcc $(FLAGS) -o $@ -c $< -I$(INCDIR) -I$(LIBINCDIR) 

$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(VMCMDSRCDIR)
	@mkdir -p $(ODIR)/$(VMCMDENCDIR)

$(LIBFT):
	@make -j -C $(LIBDIR)

delcor:
	@find . -type f -name "*.cor" -delete
	@echo "####### REMOVE .COR FILES #######"

clean:
	@make -C $(LIB_DIR) clean --silent
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR_ASM)
	@echo "###### REMOVE OBJECT FILES ######"
	@echo ${RED}[Removing $(VM_NAME) *.o files]${NC}
	@/bin/rm -rf $(ODIR)
	@make clean -C ./libft
	
fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@rm -f $(ASM_NAME)
	@echo "###### REMOVE BINARY FILES ######"
	@echo ${RED}[Removing executable $(VM_NAME) file]${NC}
	@/bin/rm -f $(VM_NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: clean fclean all re
