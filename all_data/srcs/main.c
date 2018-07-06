
#include <sniffer.h>

int			check_daemon(int *pid)
{
	FILE *f;
	char *line;
	size_t len;

	f = fopen(PID_DAEMON, "r+");
	if (f < 0)
	{
		fclose(f);
		return (1);
	}
	else
	{
		getline(&line, &len, f);
		*pid = atoi(line);
		fclose(f);
	}
	return (0);
}

int 		main(int argc, char **argv)
{
	int		flag;			// if 0 - only daemon run, if 1 - need cli start
	int		pid = 0;
	int		check = 1;		// if 0 - daemon running,  if 1 - daemon not running

	if (argc != 2 || argc == 2 && strcmp(argv[1], "-h") == 0)
	{
		printf("Usage: ./sniffer -d       // run daemon\n");
		printf("       ./sniffer -dcli    // run daemon with cli\n");
		printf("       ./sniffer -cli     // run only cli\n");
		printf("       ./sniffer -h       // show this message\n");
		return (-42);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		flag = 0;
	}
	else if (strcmp(argv[1], "-dcli") == 0)
	{
		start_daemon(&pid);
		flag = 1;
		check = 0;
	}
	else if (strcmp(argv[1], "-cli") == 0)
	{
		flag = 1;
		if (check_daemon(&pid))
		{
			printf("[*] Warning! The daemon is not running yet.\n");
			check = 1;
		}
		else
			check = 0;
	}
	else
	{
		printf("[!] Error! Incorrect flag '%s'. Use -h to show usage\n", argv[1]);
		return (-42);
	}
	if (flag) // start daemon with cli, flag -cli
	{
		cli_handler(flag, check, &pid);
	}
	else
	{
		start_daemon(&pid); // start daemon, flag -d
	}
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