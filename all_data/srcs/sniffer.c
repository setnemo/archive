
#include <sniffer.h>


void		sniffer(void)
{
	char *dev, errbuf[PCAP_ERRBUF_SIZE], str;

	dev = check_iface();
	if (!dev)
		dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "[!] [SNIFFER] Error! Couldn't find default device: %s\n", errbuf);
		exit(2);
	}
	printf("[!] [SNIFFER] Selected device: %s\n", dev);
	while (42)
	{
		sleep(10);
		printf("sniffer Daemon work...\n");
	}
}
