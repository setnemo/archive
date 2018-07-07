
#include <sniffer.h>
#define STDIN_LEN 80

static void		term_handler(int signum)
{
	remove(LOG_IFACE);
	exit(0);
}

static void		signal_handler_cli()
{	
	struct sigaction sa;
	sigset_t newset;
	sigemptyset(&newset);
	sigaddset(&newset, SIGHUP);
	sigaddset(&newset, SIGKILL);
	sigaddset(&newset, SIGQUIT);
	sigaddset(&newset, SIGINT);
	sigaddset(&newset, SIGUSR1); 
	sigprocmask(SIG_BLOCK, &newset, 0);
	sa.sa_handler = term_handler;
	sigaction(SIGTERM, &sa, 0);
	sigaction(SIGKILL, &sa, 0);
}

	
static void		select_save(char *str, int *pid, char *name_pid, int *check)
{
	FILE *f;

	f = fopen(LOG_IFACE, "w+");
	fprintf(f, "%s", str);
	fclose(f);
	printf("[*] New interface saved, need restart daemon...\n");

}

static void		select_iface(char *str, int *pid, char *name_pid, int *check)
{
	char		errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t	*devlist;
	pcap_if_t	*d;

	while (*str && *str != ' ' && *str != '\n')
		str++;
	if (*str && *str != '\n' && *(str + 1) != '\n')
	{
		str++;
		if (pcap_findalldevs(&devlist, errbuf) == -1)
		{
			fprintf(stderr, "[!] [SNIFFER] Couldn't find devices: %s\n", errbuf);
		}
		for (d = devlist; d; d = d->next)
		{
			if (strncmp(str, d->name, strlen(str) - 1) == 0)
			{
				select_save(str, pid, name_pid, check);
				return ;
			}
		}
		fprintf(stderr, "[!] [SNIFFER] Device not found!\n");
	}
	fprintf(stderr, "[!] [SNIFFER] Incorrect input! Please use 'iface' command\n");
}

static void		show_ifaces(void)
{
	char		errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t	*devlist;
	pcap_if_t	*d;

	if (pcap_findalldevs(&devlist, errbuf) == -1)
	{
		fprintf(stderr, "[!] [SNIFFER] Couldn't find devices: %s\n", errbuf);
	}
	for (d = devlist; d; d = d->next)
	{
		printf("[*] Interface: %s\n", d->name);
	}
}

static void		usage_cli(void)
{
	printf("========================= CLI Usage =========================\n");
	printf("start             packets are being sniffed from now on from default iface(eth0).\n");
	printf("stop              packets are not sniffed.\n");
	printf("show [ip] [count] ip count (print number of packets received from ip address.\n");
	printf("select [iface]    select interface for sniffing eth0, wlan0, ethN, wlanN...\n");
	printf("stat [iface]      show all collected statistics for particular interface, if iface omitted - for all interfaces.\n");
	printf("iface             show all available interfaces.\n");
	printf("exit              stop daemon and exit.\n");
	printf("exitcli           stop cli and exit (don't stop daemon).\n");
	printf("--help            show usage information.\n");
	printf("========================= end usage =========================\n");
}


void			cli_handler(char *name_pid, int flag, int check, int *pid)
{
	char	*str;
	char	*process_name = "./sniffer -cl\0";
	size_t	len = STDIN_LEN;

	signal_handler_cli();
	printf("[*] Set cli name process to \"./sniffer -cl\"\n");
	prctl(PR_SET_NAME, process_name, NULL, NULL, NULL);
	ft_strclr(name_pid);
	memcpy(name_pid, process_name, strlen(process_name) + 1);
	printf("[*] CLI for Daemon started!\n");
	usage_cli();
	while (42)
	{
		str = malloc(len);
		getline(&str, &len, stdin);
		// sscanf("%s", str);
		if (strncmp(str, "start\n", 6) == 0)
		{
			if (check_daemon(pid))
			{
				check = 1;
			}
			else
				check = 0;
			if (check)
			{
				printf("[*] Starting daemon...\n");
				start_daemon(name_pid, pid);
				// sleep(1);
				// check = 0;
			}
			else
				printf("[!] Error! The daemon is already running.\n");
		}
		else if (strncmp(str, "stop\n", 5) == 0)
		{
			if (check_daemon(pid))
			{
				check = 1;
			}
			else
				check = 0;
			if (!check && *pid != 0)
			{
				printf("[*] Daemon stopping...\n");
				kill(*pid, SIGTERM);
				check = 1;
				*pid = 0;
			}
			else
				printf("[!] Error! The daemon is not running yet.\n");
		}
		else if (strncmp(str, "show", 4) == 0)
			printf("...\n");
		else if (strncmp(str, "select", 6) == 0)
			select_iface(str, pid, name_pid, &check);
		else if (strncmp(str, "stat", 4) == 0)
			printf("...\n");
		else if (strncmp(str, "iface", 5) == 0)
			show_ifaces();
		else if (strncmp(str, "--help", 6) == 0)
			usage_cli();
		else if (strncmp(str, "exitcli", 7) == 0)
		{
			remove(LOG_IFACE);
			free(str);
			exit(0);
		}
		else if (strncmp(str, "exit", 4) == 0)
		{
			remove(LOG_IFACE);
			*pid != 0 ? kill(*pid, SIGTERM): 0 ;
			free(str);
			exit(0);
		}
		else
			printf("[!] Incorrect command! Please read usage (--help)\n");
		free(str);
	}
}
