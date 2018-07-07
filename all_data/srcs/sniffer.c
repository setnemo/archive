
#include <sniffer.h>

void		sniffer(void)
{
	char				*dev;
	char				errbuf[PCAP_ERRBUF_SIZE];
	char				logsfile[100];
	pcap_t				*handle;
	const u_char		*packet;
	struct pcap_pkthdr	hdr;
	t_tosave			alldata;

	dev = check_iface();
	if (!dev)
		dev = pcap_lookupdev(errbuf);
	if (dev == NULL)
	{
		printf("[!] [SNIFFER] Error! Couldn't find default device: %s\n", errbuf);
		exit(2);
	}
	printf("[*] [SNIFFER] Selected device: %s\n", dev);
	// create file with device's name at end 
	memcpy(&logsfile[0], LOG_ALLDATA, strlen(LOG_ALLDATA));
	memcpy(&logsfile[strlen(LOG_ALLDATA)], dev, strlen(dev));
	logsfile[strlen(LOG_ALLDATA) + strlen(dev)] = 0; // null-terminated
	alldata.logsfile = strdup(logsfile);
	handle = pcap_open_live(dev, SNAP_LEN, 1, 10000, errbuf);
	if (handle == NULL)
	{
		printf("[!] [SNIFFER] Error! Couldn't open device %s : %s\n", dev, errbuf);
		exit(1);
	}
	alldata.dev = dev;
	while (42)
	{
		alldata.snif_data = pcap_next(handle, &hdr);
		if (alldata.snif_data != NULL)
			process_packet(&hdr, &alldata);
		else
			alldata.snif_data = NULL;
	}
}
