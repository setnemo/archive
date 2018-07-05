
#include <sniffer.h>


void		usage_cli(void)
{
	printf("========================= CLI Usage =========================\n");
	printf("start             packets are being sniffed from now on from default iface(eth0)\n");
	printf("stop              packets are not sniffed\n");
	printf("show [ip]         ip count (print number of packets received from ip address\n");
	printf("select [iface]    select interface for sniffing eth0, wlan0, ethN, wlanN...\n");
	printf("stat [iface]      show all collected statistics for particular interface, if iface omitted - for all interfaces.\n");
	printf("--exit            stop daemon and exit\n");
	printf("--exitcli         stop cli and exit (don't stop daemon)\n");
	printf("--help            show usage information\n");
	printf("========================= end usage =========================\n");
}

void		start_daemon_and_cli2(int flag)
{

		// тут будет код демона
		// printf("[SNIFFER] Fork [OK], daemon started!\n");
		// printf("[!][%d] [DAEMON] Work!\n", pid);
		while (42)
			;
		// printf("[*][%d] Second died!\n", pid);
}

void	start_daemon(int flag, int *pid)
{
	*pid = fork();
	if (*pid == -1) // fork fail
	{
		printf("[!] Error! Start Daemon Error: %s\n", strerror(errno));
		exit(-42);
	}
	else if (!*pid)
	{
		// daemon settings
		umask(0);
		setsid();
		// chdir("/");
		// close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		// close(STDERR_FILENO);

		// for cli
		printf("[!][%d] [IN IF]\n", *pid);
		start_daemon_and_cli2(flag);
	}
}

int 	main(int argc, char **argv)
{
	int		flag;
	int		pid = 0;
	int		check = 1;
	char	str[80];

	// usage and handling invalid flags
	if (argc != 2 || argc == 2 && strcmp(argv[1], "-h") == 0)
	{
		printf("Usage: ./sniffer -d       // run daemon\n");
		printf("       ./sniffer -cli     // run daemon with cli\n");
		printf("       ./sniffer -h       // show this message\n");
		return (-42);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		flag = 0;
	}
	else if (strcmp(argv[1], "-cli") == 0)
	{
		flag = 1; 
	}
	else
	{
		printf("[!] Error! Incorrect flag '%s'. Use -h to show usage\n", argv[1]);
		return (-42);
	}
	if (flag)
	{
		printf("[*] CLI for Daemon started!\n");
		usage_cli();
		while (42)
		{
			scanf("%s", str);
			if (strcmp(str, "start") == 0)
			{
				if (check)
				{
					start_daemon(flag, &pid);
					check = 0;
				}
				else
					printf("[!] Error! The daemon is already running.\n");
			}
			else if (strcmp(str, "stop") == 0)
			{
				if (!check)
				{
					kill(pid, SIGTERM);
					check = 1;
				}
				else
					printf("[!] Error! The daemon is not running yet.\n");
			}
			else if (strncmp(str, "show", 4) == 0)
				printf("WOW show\n");
			else if (strncmp(str, "select", 6) == 0)
				printf("WOW select\n");
			else if (strncmp(str, "stat", 4) == 0)
				printf("WOW\n");
			else if (strcmp(str, "--help") == 0)
				usage_cli();
			else if (strcmp(str, "--exit") == 0)
				exit(0);
			else if (strcmp(str, "--exitcli") == 0)
				exit(0);
			else
				printf("[!] Incorrect command! Please read usage (--help)\n");
		}
	}
	else
	{
		start_daemon(flag, &pid);// start daemon
	}
	// if (flag && pid)
	// {
	// 	printf("[!][%d] [CLI] Work!\n", pid);
	// 	kill(pid, SIGTERM);
	// }
	// printf("[*] First died!\n");
	return (0);
}


// int main(void)
// {
// 	char *dev, errbuf[PCAP_ERRBUF_SIZE];

// 	dev = pcap_lookupdev(errbuf);
// 	if (dev == NULL) {
// 		fprintf(stderr, "[!] Couldn't find default device: %s\n", errbuf);
// 		return(2);
// 	}
// 	printf("[!] Device: %s\n", dev);
// 	pcap_if_t *devlist;
// 	pcap_if_t *d;

// 	if(pcap_findalldevs(&devlist,errbuf) == -1)
// 	{
// 		fprintf(stderr, "[!] Couldn't find devices: %s\n", errbuf);
// 	}
// 	for (d=devlist; d; d=d->next)
// 	{
// 		printf("[*] Device: %s ====|||%s\n", d->name, d->description);
// 	}
// 	return(0);
// }