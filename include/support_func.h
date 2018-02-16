
#ifndef SUPPORT_FUNC_H
# define SUPPORT_FUNC_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

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

#endif
