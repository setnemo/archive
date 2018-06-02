/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:28:41 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 15:28:41 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>
# include "ft_printf_structs.h"
# include "libft_structures.h"

# define MAX_STR 32
# define START_SIZE 2048
# define FLOAT_STR_MAX_SIZE 5300
# define FLOAT_A_STR_MAX_SIZE 20000
# define FRAC_DEFAULT_SIZE 201

# define NUMBERS_S "0123456789abcdef"
# define NUMBERS_B "0123456789ABCDEF"

/*
** LENGTH CONVERTIONS
*/

void		convert_di(va_list *ap, intmax_t *num, t_params *p);
void		convert_ouxbx(va_list *ap, uintmax_t *num, t_params *p);

/*
** TOOLS
*/

intmax_t	printf_atoi(char *str, int *p);
void		rev_str(char *from, char *until);
size_t		count_bits(wchar_t k);
int			check_bits(size_t *b, wchar_t c, t_params *p);
size_t		get_next_length(char *str, t_length *ll);
void		float_flags(t_params *p);
long double	get_float_num(va_list *ap, t_params *p, _Bool is_cap);
void		set_float(t_float *f, long double num);

/*
** PRINTERS
*/

void		print_symbol(t_params *p, char c);
void		print_str(t_params *p, char *str, _Bool ignore_prec);
int			printf_putwchar(wchar_t c, t_params *p);
void		print_number(uintmax_t n, size_t base, t_params *p,
						void (*preffunc)(t_params*));

/*
** PARAM INITIALISATION
*/

t_params	*init_params(void);
void		read_params(t_params *p, char *fmt, size_t *pos, va_list *ap);
void		del_params(t_params **p);
void		zero_params(t_params *p);

/*
** READING PARAMETERS
*/

size_t		get_n(char *str, int *p);
void		get_flags(char *str, int *p, t_flags *f);
int			get_width(char *str, int *p, va_list *ap, _Bool *b);
int			get_precision(char *str, int *p, va_list *ap, _Bool *b);
t_length	get_length(char *str, int *i);

/*
** PREFIXES
*/

void		print_sign_pref(t_params *p);
void		print_oct_pref(t_params *p);
void		print_hex_pref(t_params *p);
void		print_bin_pref(t_params *p);

/*
** FLOAT TOOLS
*/

t_float		*init_t_float(size_t size);
void		zero_t_float(t_float *f);
t_str		*init_t_str(size_t size);
void		set_float(t_float *f, long double num);
void		round_float(t_float *f, t_params *p, _Bool expo);
void		round_float_g(t_float *f, t_params *p, _Bool expo);
void		print_e_exp(t_params *p, int expon, char c);
void		float_to_binary(t_float *f, long double num,
							_Bool is_cap, _Bool is_long);

/*
** REALLOCS
*/

void		realloc_toprint(t_print_str *tp);
void		realloc_t_float(t_float *f);
void		realloc_t_str(t_str *tstr);

/*
** TYPE FUNCTIONS
*/

void		type_percent(va_list *ap, t_params *p);
void		type_c(va_list *ap, t_params *p);
void		type_bc(va_list *ap, t_params *p);
void		type_s(va_list *ap, t_params *p);
void		type_bs(va_list *ap, t_params *p);
void		type_di(va_list *ap, t_params *p);
void		type_bd(va_list *ap, t_params *p);
void		type_u(va_list *ap, t_params *p);
void		type_bu(va_list *ap, t_params *p);
void		type_o(va_list *ap, t_params *p);
void		type_bo(va_list *ap, t_params *p);
void		type_x(va_list *ap, t_params *p);
void		type_bx(va_list *ap, t_params *p);
void		type_p(va_list *ap, t_params *p);
void		type_f(va_list *ap, t_params *p);
void		type_bf(va_list *ap, t_params *p);
void		type_a(va_list *ap, t_params *p);
void		type_ba(va_list *ap, t_params *p);
void		type_g(va_list *ap, t_params *p);
void		type_bg(va_list *ap, t_params *p);
void		type_e(va_list *ap, t_params *p);
void		type_be(va_list *ap, t_params *p);
void		type_n(va_list *ap, t_params *p);
void		type_b(va_list *ap, t_params *p);
void		type_bb(va_list *ap, t_params *p);
void		type_none(char c, t_params *p);

void		type_fbf(va_list *ap, t_params *p, _Bool is_cap);
void		type_ebe(va_list *ap, t_params *p, char c, _Bool is_cap);
void		type_gbg(va_list *ap, t_params *p, char c, _Bool is_cap);
void		type_aba(va_list *ap, t_params *p, char *c, _Bool is_cap);

#endif
