
#ifndef SUPPORT_FUNC_H
# define SUPPORT_FUNC_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include "dns.h"

// выводим ошибку ерно и завершаем выполнение программы
void		error(char *err);

//сравниваем запрос со своим черным списком
int			check_blacklist(char *buffer, t_db *db);

//заменяем точки на количество байт после точки, чтобы во время проверка сравнивать через memcmp
void		replace_dot(t_db *db);

//занулить строку
void		ft_strclr(char *s);

//сконкатенировать и замолочить строку, вернуть указатель на нее
char		*ft_strjoin(char const *s1, char const *s2);

//замолочить новую строку по длины size + нуль-терминатор и вернуть указатель на нее 
char		*ft_strnew(size_t size);

//замолочить новую строку из строки с индекса start длиной len + '\0' и вернуть указатель
char		*ft_strsub(char const *s, unsigned int start, size_t len);

//принимает строку, делит ее на массив строк по делиметру char c и возвращает указатель на массив строк
char		**ft_strsplit(char const *s, char c);

#endif
