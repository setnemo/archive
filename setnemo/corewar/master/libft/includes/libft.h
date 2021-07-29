/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:52:17 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/24 17:52:19 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "libft_structures.h"
# include "get_next_line.h"
# include "libftprintf.h"
# include <stdint.h>
# include <string.h>

# define LIB_GN(x) x - '0'
# define LIB_GC(x) x + '0'

# define NUM_FROM_CHAR(x) x >= '0' && x <= '9' ? x - '0' : x - 'a' + 10
# define CHAR_FROM_NUM(x) x <= 9 ? x + '0' : x - 10 + 'a'

/*
** READ FUNCS
*/

t_read_arr	*read_lines(int fd);
void		free_read_lines(t_read_arr *arr);
void		free_word_arr(char **words);

/*
** CALC FUNCS
*/

long		ft_abs(long x);
int			ft_atoi(const char *str);
int			ptr_atoi(char **str);
int			ptr_atoi2(char *str, size_t *ptr);
int			get_sign(int x);
int			ft_count_digits_uns(uintmax_t value, int base);
int			ft_count_digits(intmax_t value, int base);
double		ft_dsqrt(int nb, double delta);
size_t		ft_factorial(size_t num);
long		ft_isprime(long nb);
char		*ft_itoa_base_uns(uintmax_t value, int base);
char		*ft_itoa_base(intmax_t value, int base);
char		*ft_itoa(int n);
void		ft_sort_num_tab(int *mass, int size);
void		ft_sort_word_tab(char **mass);
long		ft_sqrt(long nb);
void		ft_swap(int *a, int *b);
char		*long_mul(char *ss1, char *ss2);
char		*long_mul_base(char *ss1, char *ss2, size_t base);

/*
** CHAR FUNCS
*/

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_iswhitespace(char c);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		hex_from_dec(char *buf, _Bool is_cap);

/*
** LIST FUNCS
*/

char		*ft_list_to_string(t_list *t, size_t *len);
char		*ft_list_to_string_x64(t_list *t, size_t *len);
void		ft_lstadd(t_list **alst, t_list *new);
t_list		*ft_lstcontains(t_list *t, void *data, size_t size);
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstpushback(t_list **alst, t_list *new);

/*
** MEM FUNCS
*/

void		ft_bzero(void *b, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_memdel(void **ap);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_strdel(char **as);
char		*ft_strnew(size_t size);

/*
** PRINT FUNCS
*/

void		ft_log(char l, char *str, void (*f)(char *));
void		ft_print_num_tab(int **tab, int size);
void		ft_print_word_tab(char **tab);
int			ft_printf(const char *fmt, ...);
int			ft_printf_fd(int fd, const char *fmt, ...);
size_t		ft_putchar_fd(char c, int fd);
size_t		ft_putchar(char c);
size_t		ft_putendl_fd(char *str, int fd);
size_t		ft_putendl(char *str);
size_t		ft_putnbr_fd(intmax_t n, int fd);
size_t		ft_putnbr(intmax_t n);
size_t		ft_putnbr_uns_fd(uintmax_t n, int fd);
size_t		ft_putnbr_uns(uintmax_t n);
size_t		ft_putnbrendl(intmax_t n);
size_t		ft_putstr_fd(char *str, int fd);
size_t		ft_putstr(char *str);

/*
** STR FUNCS
*/

char		*ft_rmdupsymb(char	*str);
char		**ft_split_whitespaces(char *str);
char		*ft_strcat(char *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
void		ft_strclr(char *s);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, char const *src);
char		*ft_strdup(const char *str);
char		*ft_strdupab(const char *str, int a, int b);
int			ft_strequ(char const *s1, char const *s2);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *s1, char const *s2, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strncat(char *s1, char const *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strncpy(char *dest, char const *src, size_t len);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strnstr(const char *big, const char *small, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strrev(char *str);
char		**ft_strsplit(char const *s, char c);
char		*ft_strstr(const char *big, const char *small);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s);
char		*ft_strupper(char *str);
_Bool		is_integer(char *str);
_Bool		is_number(char *str);

/*
** LONG MUL TOOLS
*/

t_str		*insert_num_base(t_str *s, char num);
t_str		*long_sum_base(t_str *s1, t_str *s2, size_t base);
void		str_to_num(t_str *s);

#endif
