/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 09:04:20 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/27 09:04:21 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include "../libft/libft.h"
# define WTHT 0
# define HASH 1
# define ZERO 2
# define MINUS 4
# define PLUS 8
# define SPACE 16
# define APOST 32

typedef struct	s_pfs
{
	const char	*str;
	size_t		length;
}				t_pfs;

typedef enum	e_pf_mod
{
	NONE = 0, L = 1, H = 2, J = 3, Z = 4, LL = 5, HH = 6
}				t_pf_mod;

typedef struct	s_pf_argument
{
	size_t			position;
	size_t			length;
	t_pfs			str;
}				t_pf_argument;

typedef struct	s_arg
{
	t_pfs			str;
	int				add;
	int				flags;
	unsigned int	width;
	int				width_add;
	int				precision;
	t_pf_mod		mod;
	char			conver;
	int				error;
	void			*value;
}				t_arg;

typedef struct	s_pf_mngr
{
	char			conver;
	int				(*mngr)(t_arg, va_list);
}				t_pf_mngr;

int				pf_atoi(const char *s, int allow_neg, int *result, size_t *i);
char			*pf_itoa(intmax_t n, t_arg all, char sign);
char			*pf_uitoa(uintmax_t n, unsigned int base, const char *digits,
					size_t precision);

size_t			ft_strnlen(const char *s, const size_t max);

int				max(int a, int b);
int				bs(char c);

int				pf_mngr_percent(t_arg all, va_list list);
int				pf_mngr_char(t_arg all, va_list list);
int				pf_mngr_string(t_arg all, va_list list);
int				pf_mngr_hex(t_arg all, va_list list);

int				pf_write_chunk(const char *s, int free, size_t len, t_arg all);

int				pf_core(va_list arg, const char *s);
int				pf_transform(t_arg all, va_list arg, int i);

int				pf_write(const char *s, const size_t len);
int				pf_repeat(const char c, int len);

int				ft_printf(const char *format, ...);

int				mngr_add(t_arg *all, const char *s, size_t *i);
int				mngr_flags(t_arg *all, const char *s, size_t *i);
int				mngr_width(t_arg *all, const char *s, size_t *i);
int				mngr_precision(t_arg *p, const char *s, size_t *i);
int				mngr_mod(t_arg *p, const char *s, size_t *i);
int				mngr_conver(t_arg *p, const char *s, size_t *i);
t_arg			get_all(const char *s, size_t len);

int				conver(const char c);
int				modfc(const char c);
int				flag(const char c);
int				validsymb(const char c);
t_arg			arg(const char *s, const size_t len);
t_pfs			pfs(const char *s, size_t len);
t_arg			get_all(const char *s, size_t len);

int				pf_atoi(const char *s, int allow_neg, int *result, size_t *i);
char			*pf_itoa(intmax_t n, t_arg all, char sign);
char			*pf_uitoa(uintmax_t n, unsigned int base, const char *digits,
					size_t precision);
#endif
