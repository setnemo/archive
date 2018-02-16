
#ifndef READ_CONFIG_H
# define READ_CONFIG_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

void		free_db(t_db *db);
int			read_config(t_db *db);

#endif
