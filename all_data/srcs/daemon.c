
#include <sniffer.h>

static void	write_pid_to_file(void)
{
	FILE *f;
	int pid = getpid();

	f = fopen(PID_DAEMON, "w+");
	fprintf(f, "%u\n", pid);
	fclose(f);
}

void			start_daemon(char *name_pid, int *pid)
{
	printf("[*] Change daemon name process to \"./sniffer -d\"\n");
	char *process_name = "./sniffer -d\0";
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
		ft_strclr(name_pid);
		prctl(PR_SET_NAME, process_name, NULL, NULL, NULL);
		memcpy(name_pid, process_name, strlen(process_name) + 1);

		umask(0);
		setsid();
		chdir("/");
		close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		close(STDERR_FILENO);
		sniffer();
	}
}
