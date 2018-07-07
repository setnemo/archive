
#include <sniffer.h>

void		sniffer(void)
{
	char				*dev;
	char				errbuf[PCAP_ERRBUF_SIZE];
	char				str;
	pcap_t				*handle;
	const u_char		*packet;
	FILE				*logfile;
	struct pcap_pkthdr	hdr;
	
	logfile = fopen("/var/log/log.txt","w");
	dev = check_iface();
	if (!dev)
		dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		printf("[!] [SNIFFER] Error! Couldn't find default device: %s\n", errbuf);
		exit(2);
	}
	printf("[*] [SNIFFER] Selected device: %s\n", dev);
	handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);
	if (handle == NULL)
	{
		printf("[!] [SNIFFER] Error! Couldn't open device %s : %s\n", dev, errbuf);
		exit(1);
	}
	while (42)
	{
		packet = pcap_next(handle, &hdr);
		process_packet(&hdr, packet, logfile);
	}
}
