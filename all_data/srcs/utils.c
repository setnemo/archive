
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
	while(*temp != '\n')
		temp++;
	*temp = 0;
	return (line);
}
