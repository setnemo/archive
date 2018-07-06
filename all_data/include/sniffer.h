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
# include <execinfo.h>
# include <unistd.h>
# include <errno.h>
# include <wait.h>

void	cli_handler(int flag, int check);
void	start_daemon(int *pid);

#endif
