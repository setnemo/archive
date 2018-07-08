
#include <sniffer.h>

static void		dev_show_packets(char *name)
{
	FILE	*dev;
	char	*line;
	size_t	len;
	char	logsfile[100];

	memset(&logsfile[0], 0, 100);
	memcpy(&logsfile[0], LOG_ALLDATA, strlen(LOG_ALLDATA));
	memcpy(&logsfile[strlen(LOG_ALLDATA)], name, strlen(name));
	dev = fopen(logsfile, "rt");
	if (dev == NULL)
	{
		printf("[*] [CLI] [PACKETS] No data file '%s'\n", name);
		return ;
	}
	else
	{
		printf("[*] [CLI] [PACKETS] [%s]\n", logsfile);
		len = 1024;
		line = malloc(len);
		while (getline(&line, &len, dev) > 0)
		{
			printf("%s", line);
		}
		printf("\n\n");
		free(line);
		fclose(dev);
	}
}

static void		parse_all_dev_and_show_packets(void)
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
		dev_show_packets(d->name);
	}

}

static void		parse_dev_and_show_packets(char *str)
{
	char	*temp;

	temp = strchr(str, '\n');
	if (temp)
		*temp = 0;
	if (*str == ' ')
	{
		while (*str == ' ')
			str++;
	}
	if (*str != 0)
		dev_show_packets(str);
}

void			show_packets(char *str)
{
	char *temp;

	temp = str;
	str = strchr(str, ' ');
	if (str && strncmp(temp, "packets ", 8) == 0)
	{
		str++;
		if (strlen(str) > 1)
		{
			temp = str;
			if (*temp == '\n' || *temp == ' ')
			{
				while (*temp == '\n' || *temp == ' ')
					temp++;	
				if (strlen(temp))
					parse_dev_and_show_packets(str);
				else
					parse_all_dev_and_show_packets();
			}
			else if (*temp == 0)
				parse_all_dev_and_show_packets();
			else
				parse_dev_and_show_packets(str);
		}
		else
			parse_all_dev_and_show_packets();
	}
	else
	{
		if (temp[7] != '\n' && temp[7] != ' ' && strncmp(temp, "packets", 7) == 0) 
			printf("[!] Incorrect command! Please read usage (--help)\n");
		else
			parse_all_dev_and_show_packets();
	}
}

void			show_ip(char *str)
{
	FILE	*ip;
	char	*line;
	char	*temp;
	size_t	len;
	size_t	count;

	str = strchr(str, ' ');
	if (str)
		str++;
	if (str && *str && *str != ' ' && *(str + 1) != '\n')
	{
		ip = fopen(LOG_COUNT_IP, "rt");
		if (ip == NULL)
		{
			printf("[!] [CLI] Error! Couldn't open 'ip log' file!\n");
			return ;
		}
		else
		{
			count = 0;
			len = 1024;
			line = malloc(len);
			while (getline(&line, &len, ip) > 0)
			{
				if (strncmp(line, str, strlen(str)) == 0)
					++count;
			}
			temp = strchr(str, '\n');
			if (temp)
				*temp = 0;
			if (!count)
				printf("[!] [CLI] Zero packets from '%s' or invalid IP\n", str);
			else
				printf("[*] [CLI] Total packets from '%s': %zu\n", str, count);
			free(line);
			fclose(ip);
		}
	}
	else
		fprintf(stderr, "[!] [CLI] Incorrect input!\n");
}
static void		dev_show_stat(char *str, char *name)
{
	FILE	*dev;
	char	*line;
	size_t	len;
	size_t	count;

	dev = fopen(str, "rt");
	if (dev == NULL)
	{
		return ;
	}
	else
	{
		count = 0;
		len = 1024;
		line = malloc(len);
		while (getline(&line, &len, dev) > 0)
		{
			if (strncmp(line, name, strlen(name)) == 0)
				++count;
		}
		if (count)
			printf("[*] [CLI] Total packets from '%s': %zu\n", name, count);
		else
			printf("[!] [CLI] Zero packets from '%s' or invalid device\n", name);

		free(line);
		fclose(dev);
	}
}

static void		parse_all_dev_and_show_stat(void)
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
		dev_show_stat(LOG_COUNT_IFACES, d->name);
	}

}

static void		parse_dev_and_show_stat(char *str)
{
	char	*temp;

	temp = strchr(str, '\n');
	if (temp)
		*temp = 0;
	if (*str == ' ')
	{
		while (*str == ' ')
			str++;
	}
	if (*str != 0)
		dev_show_stat(LOG_COUNT_IFACES, str);
}

void			stat_iface(char *str)
{
	char *temp;

	temp = str;
	str = strchr(str, ' ');
	if (str && strncmp(temp, "stat ", 5) == 0)
	{
		str++;
		if (strlen(str) > 1)
		{
			temp = str;
			if (*temp == '\n' || *temp == ' ')
			{
				while (*temp == '\n' || *temp == ' ')
					temp++;	
				if (strlen(temp))
					parse_dev_and_show_stat(str);
				else
					parse_all_dev_and_show_stat();
			}
			else if (*temp == 0)
				parse_all_dev_and_show_stat();
			else
				parse_dev_and_show_stat(str);
		}
		else
			parse_all_dev_and_show_stat();
	}
	else
	{
		if (temp[4] != '\n' && temp[4] != ' ' && strncmp(temp, "stat", 4) == 0) 
			printf("[!] Incorrect command! Please read usage (--help)\n");
		else
			parse_all_dev_and_show_stat();
	}
}

void		show_ifaces(void)
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
