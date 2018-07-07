#ifndef SNIFFER_H
# define SNIFFER_H
# include <stdio.h>
# include <pcap.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/file.h>
# include <sys/types.h>
# include <sys/stat.h>
// # include <sys/prctl.h>
# include <execinfo.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>

# define PID_DAEMON "/var/log/.pid_daemon"
# define LOG_IFACE "/var/log/.interfaces.start"
# define LOG_ALLDATA "/var/log/all_data.log."
# define LOG_COUNT_IP "/var/log/ip.log"
# define LOG_COUNT_IFACES "/var/log/iface.log"
# define SNAP_LEN 1518


typedef struct	s_tosave
{
	int					size;
	FILE				*logfile;	
	FILE				*ipfile;
	FILE				*ifacefile;
	char				*dev;
	char				*logsfile;
	struct pcap_pkthdr	*header;
	const u_char		*snif_data;
}				t_tosave;

void 		manage(int argc, char **argv);

void		cli_handler(char *name_pid, int flag, int check, int *pid);
void		start_daemon(char *name_pid, int *pid);

void		sniffer(void);

void		ft_strclr(char *s);
int			check_daemon(int *pid);
char		*check_iface(void);


void process_packet(struct pcap_pkthdr *header, t_tosave *alldata);

#endif
