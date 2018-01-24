#ifndef SDB_H
# define SDB_H
# include "../libft/libft.h"

typedef struct		s_sdb
{
	char			*addr;
	struct s_sdb	*next;
}					t_sdb;

#endif
