
#include <sniffer.h>

static void		term_handler(int signum)
{
	remove(PID_DAEMON);
	exit(0);
}

static void		signal_handler_daemon()
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
	char *process_name = "./sniffer -d\0";
	*pid = fork();
	if (*pid == -1) // fork fail
	{
		printf("[!] Error! Start Daemon Error: %s\n", strerror(errno));
		exit(-42);
	}
	else if (!*pid)
	{
		signal_handler_daemon();
		write_pid_to_file();
		// daemon settings
		printf("[*] Set daemon name process to \"./sniffer -d\"\n");
		ft_strclr(name_pid);
		// prctl(PR_SET_NAME, process_name, NULL, NULL, NULL);
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
