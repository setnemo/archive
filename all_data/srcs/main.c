
#include <sniffer.h>

int 		main(int argc, char **argv)
{
	if (getuid() != 0) // check root
	{
		printf("[!] Error: this program must be run as root! Quitting\n");
		exit(1);
	}
	manage(argc, argv);
	return (0);
}
