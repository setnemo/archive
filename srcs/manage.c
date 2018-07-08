
#include <sniffer.h>

void 		manage(int argc, char **argv)
{
	int		flag;			// if 0 - only daemon run, if 1 - need cli start
	int		pid = 0;
	int		check = 1;		// if 0 - daemon running,  if 1 - daemon not running

	if (getuid() != 0) // check root
	{
		printf("[!] Error: this program must be run as root! Quitting\n");
		exit(1);
	}
	else if (argc != 2 || (argc == 2 && strcmp(argv[1], "-h") == 0))
	{
		printf("Usage: ./sniffer -d       // run daemon\n");
		printf("       ./sniffer -dc      // run daemon with cli\n");
		printf("       ./sniffer -cl      // run only cli\n");
		printf("       ./sniffer -h       // show this message\n");
		exit(1);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		flag = 0;
	}
	else if (strcmp(argv[1], "-dc") == 0)
	{
		if (!check_daemon(&pid))
		{
			printf("[*] Warning! The daemon is already running.\n");
			check = 1;
		}
		else
			start_daemon(&argv[0][0], &pid);
		flag = 1;
		check = 0;
	}
	else if (strcmp(argv[1], "-cl") == 0)
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
		exit(1);
	}
	if (flag) // start daemon with cli, flag -cli
	{
		cli_handler(&argv[0][0], check, &pid);
	}
	else
	{
		if (!check_daemon(&pid))
		{
			printf("[*] Warning! The daemon is already running.\n");
			exit(1);
		}
		start_daemon(&argv[0][0], &pid); // start daemon, flag -d
	}
}
