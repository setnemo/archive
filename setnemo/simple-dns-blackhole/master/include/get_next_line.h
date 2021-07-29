
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# define BUFF_SIZE 1
# define ERR(e) if (!e) return (-1);
# define NOMEM(no) if (!no) return (NULL);
# define BRK(ch) if (ch) break ;

typedef struct		s_gnl
{
	int				fd;
	int				br;
	char			*str;
	char			*tmp;
	char			*after;
	struct s_gnl	*next;
}					t_gnl;

//читает по fd, молочит строку в указатель line
//возвращает 1 если есть еще строки
//0 если вернул последнюю строку
//-1 если ошибка
//поддерживате мультидескриптор (несколько fd)

int					get_next_line(const int fd, char **line);

#endif
