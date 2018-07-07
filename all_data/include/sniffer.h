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
# include <sys/prctl.h>
# include <execinfo.h>
# include <unistd.h>
# include <errno.h>
# include <wait.h>
# include <signal.h>

/*
**	defines for logs, daemon, sniffer()
*/
# define PID_DAEMON "/var/log/.pid_daemon"
# define LOG_IFACE "/var/log/.interfaces.start"
# define LOG_ALLDATA "/var/log/all_data.log."
# define LOG_COUNT_IP "/var/log/ip.log"
# define LOG_COUNT_IFACES "/var/log/iface.log"
# define SNAP_LEN 1518

/*
**	struct for saving data in logs
*/
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

/*
**	manage.c
*/
void 		manage(int argc, char **argv);

/*
**	cli.c
*/
void		cli_handler(char *name_pid, int check, int *pid);

/*
**	daemon.c
*/
void		start_daemon(char *name_pid, int *pid);

/*
**	sniffer.c
*/
void		sniffer(void);

/*
**	utils.c
*/
void		ft_strclr(char *s);
int			check_daemon(int *pid);
char		*check_iface(void);
void		select_iface(char *str);
void		show_ifaces(void);
void		show_ip(char *str);
void		stat_iface(char *str);

/*
**	save_data.c
*/
void		process_packet(struct pcap_pkthdr *header, t_tosave *alldata);

#endif
