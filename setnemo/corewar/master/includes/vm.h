/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:37:08 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:37:12 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# define MALL(x) if (!(x)) mall_error()

# include "structures.h"
# include "encurse.h"

# define UCHAR unsigned char
# define UINT unsigned int
# define NUM_OF_FUNCS 16
# define NUMOF_INP_FUNCS 5

# define COMMAND 1
# define CODING_BYTE 1
# define TREG 1
# define TDIR 2
# define TIND 3

void	init_globals(void);
void	print_winner(void);
void	print_field(void);
void	you_gonna_die_bitch(void);
void	run_cycle_step(void);
void	parse_commands(void);
void	ctd_check(void);
void	finish_prog(void);

/*
** INPUT READING
*/

void	parse_input(int ac, char **av);
void	parse_player(char *name, t_champ *player);
void	numerate_remaining_players(void);
void	validate_numeration(void);
void	set_players(void);
char	*get_arg(t_inpdata *data);
int		inp_dumpflag(t_inpdata *data);
int		inp_vflag(t_inpdata *data);
int		inp_lflag(t_inpdata *data);
int		inp_sflag(t_inpdata *data);
int		inp_player(t_inpdata *data);

/*
** PROCESSES
*/

void	proc_invalid(void *data);
void	proc_live(void *data);
void	proc_load(void *data);
void	proc_store(void *data);
void	proc_add(void *data);
void	proc_sub(void *data);
void	proc_and(void *data);
void	proc_or(void *data);
void	proc_xor(void *data);
void	proc_zjump(void *data);
void	proc_ldi(void *data);
void	proc_sti(void *data);
void	proc_fork(void *data);
void	proc_load_long(void *data);
void	proc_ldi_long(void *data);
void	proc_fork_long(void *data);
void	proc_aff(void *data);

/*
** PROC TOOLS
*/

void	parse_command(t_process *p);
void	new_process(int pc, int playernum);
void	copy_process(int pc, t_process *proc);
void	gen_processes(void);
void	free_proc(t_process *proc);
void	print_move(t_process *proc, int toskip);
t_codes	get_cod_b(int *toskip, t_process **proc, void *data);

/*
** FIELD TOOLS
*/

UCHAR	get_field_val(int pos);
void	set_field_val(int pos, unsigned char val, int playernum);
int		set_pos(int pos);
t_codes	coding_byte(int pos);
int		count_total_skip(t_codes c_b, _Bool has_coding, int numofargs, int td);
int		get_int(int pos, int len);
void	set_int(int pos, int len, UINT val, int playernum);
_Bool	parse_arg(int code, t_process *proc, int *arg, int *toskip);
void	print_participants(void);
void	print_winner(void);

/*
** ERRORS
*/

void	mall_error(void);
void	print_usage(void);
void	invalid_flag(char *str);
void	not_a_champion(char *str);
void	invalid_palyer_index(char *str);
void	invalid_champion(char *str);
void	invalid_champ_length(char *str);
void	file_error(char *filename);

#endif
