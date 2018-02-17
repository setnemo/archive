
#ifndef DNS_H
# define DNS_H
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <pwd.h>
# include <signal.h>
# include <sys/wait.h>
# include <time.h>
# include <errno.h>
# include <grp.h>

typedef	struct		s_db
{
	char			*config;
	char			*forwarder;
	char			*listen;
	char			*sock;
	int				port;
	char			**blacklist;
}					t_db;

typedef struct		s_buff{
	unsigned char	*buffer;
	int				length;
}					t_buff;


void		start_dns(t_db *db);

#endif
