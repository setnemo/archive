#ifndef SDB_H
# define SDB_H
# include "../libft/include/libft.h"

typedef	struct		s_db
{
	char			*forwarder;
	char			*listen;
	char			*sock;
	int				port;
	char			**blacklist;
}					t_db;

typedef struct		s_buff{
	char 			*buffer;
	int				length;
}					t_buff;

#endif
