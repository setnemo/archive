
#include <sniffer.h>

static void	write_pid_to_file(void)
{
	FILE *f;
	int pid = getpid();

	f = fopen(PID_DAEMON, "w+");
	fprintf(f, "%u\n", pid);
	fclose(f);
}

static void		sniffer()
{
	// тут будет код демона
	while (42)
	{
		sleep(10);
		printf("sniffer Daemon work...\n");
	}
}

void			start_daemon(int *pid)
{
	*pid = fork();
	if (*pid == -1) // fork fail
	{
		printf("[!] Error! Start Daemon Error: %s\n", strerror(errno));
		exit(-42);
	}
	else if (!*pid)
	{
		write_pid_to_file();
		// daemon settings
		umask(0);
		setsid();
		chdir("/");
		close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		close(STDERR_FILENO);
		sniffer();
	}
}
