
#include <sniffer.h>
#define STDIN_LEN 80

static void		term_handler_cli(int signum)
{
	if (signum == 15 || signum == 9)
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
	sa.sa_handler = term_handler_cli;
	sigaction(SIGTERM, &sa, 0);
	sigaction(SIGKILL, &sa, 0);
}

static void		usage_cli(void)
{
	printf("========================= CLI Usage =========================\n");
	printf("start             packets are being sniffed from now on from default iface(eth0).\n");
	printf("stop              packets are not sniffed.\n");
	printf("show [ip]         print number of packets received from ip address.\n");
	printf("select [iface]    select interface for sniffing eth0, wlan0, ethN, wlanN...\n");
	printf("stat [iface]      show all collected statistics for particular interface, if iface omitted - for all interfaces.\n");
	printf("packets           show all received packets.\n");
	printf("iface             show all available interfaces.\n");
	printf("exit              stop daemon and exit.\n");
	printf("exitcli           stop cli and exit (don't stop daemon).\n");
	printf("--help            show usage information.\n");
	printf("========================= end usage =========================\n");
}


void			cli_handler(char *name_pid, int check, int *pid)
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
		if (strncmp(str, "start\n", 6) == 0)
		{
			if (check_daemon(pid)) //check pid file (run daemon)
			{
				check = 1;
			}
			else
				check = 0;
			if (check)
			{
				printf("[*] Starting daemon...\n");
				start_daemon(name_pid, pid);

			}
			else
				printf("[!] Error! The daemon is already running.\n");
		}
		else if (strncmp(str, "stop\n", 5) == 0)
		{
			if (check_daemon(pid)) //check pid file (run daemon)
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
		else if (strncmp(str, "packets", 7) == 0)
			usage_cli();
		else if (strncmp(str, "show", 4) == 0)
			show_ip(str);
		else if (strncmp(str, "select", 6) == 0)
			select_iface(str);
		else if (strncmp(str, "stat", 4) == 0)
			stat_iface(str);
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
