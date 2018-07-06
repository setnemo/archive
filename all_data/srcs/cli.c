
#include <sniffer.h>

static void		usage_cli(void)
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


void			cli_handler(int flag, int check, int *pid)
{
	char	str[80];
     
	printf("[*] CLI for Daemon started!\n");
	usage_cli();
	while (42)
	{
		scanf("%s", str);
		if (strcmp(str, "start") == 0)
		{
			if (check)
			{
				printf("[*]!\n");
				start_daemon(pid);
				check = 0;
				sleep(1);
			}
			else
				printf("[!] Error! The daemon is already running.\n");
		}
		else if (strcmp(str, "stop") == 0)
		{
			if (!check && *pid != 0)
			{
				kill(*pid, SIGTERM);
				check = 1;
				*pid = 0;
				remove(PID_DAEMON);
			}
			else
				printf("[!] Error! The daemon is not running yet.\n");
		}
		else if (strncmp(str, "show", 4) == 0)
			printf("...\n");
		else if (strncmp(str, "select", 6) == 0)
			printf("...\n");
		else if (strncmp(str, "stat", 4) == 0)
			printf("...\n");
		else if (strcmp(str, "--help") == 0)
			usage_cli();
		else if (strcmp(str, "--exit") == 0)
		{
			*pid != 0 ? kill(*pid, SIGTERM): 0 ;
			remove(PID_DAEMON);
			exit(0);
		}
		else if (strcmp(str, "--exitcli") == 0)
			exit(0);
		else
			printf("[!] Incorrect command! Please read usage (--help)\n");
	}
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