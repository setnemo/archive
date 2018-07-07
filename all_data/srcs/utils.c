
#include <sniffer.h>

void		ft_strclr(char *s)
{
	while (*s)
		*s++ = '\0';
}

int			check_daemon(int *pid)
{
	FILE *f;
	char *line;
	size_t len;

	f = fopen(PID_DAEMON, "r");
	if (!f)
	{
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

char		*check_iface(void)
{
	FILE *f;
	char *line, *temp;
	size_t len;

	f = fopen(LOG_IFACE, "r");
	if (!f)
	{
		return (NULL);
	}
	else
	{
		getline(&line, &len, f);
		fclose(f);
	}
	temp = line;
	temp = strchr(temp, '\n');
	if (temp)
		*temp = 0;
	return (line);
}

static void		select_save(char *str)
{
	FILE *f;

	f = fopen(LOG_IFACE, "w+");
	fprintf(f, "%s", str);
	fclose(f);
	printf("[*] New interface saved, need restart daemon...\n");

}

void			select_iface(char *str)
{
	char		errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t	*devlist;
	pcap_if_t	*d;

	str = strchr(str, ' ');
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
				select_save(str);
				return ;
			}
		}
		fprintf(stderr, "[!] [SNIFFER] Device not found!\n");
	}
	fprintf(stderr, "[!] [SNIFFER] Incorrect input! Please use 'iface' command\n");
}
