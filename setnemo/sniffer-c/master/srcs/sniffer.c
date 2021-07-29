
#include <sniffer.h>

void		sniffer(void)
{
	char				*dev;
	char				errbuf[PCAP_ERRBUF_SIZE];
	char				logsfile[100];
	pcap_t				*handle;
	struct pcap_pkthdr	hdr;
	t_tosave			alldata;

	dev = check_iface(); //check selected iface in cli
	if (!dev)
		dev = pcap_lookupdev(errbuf); //or default iface
	if (dev == NULL)
	{
		printf("[!] [DAEMON] Error! Couldn't find default device: %s\n", errbuf);
		exit(2);
	}
	printf("[*] [DAEMON] Selected device: %s\n", dev);
	// create file with device's name 
	memcpy(&logsfile[0], LOG_ALLDATA, strlen(LOG_ALLDATA));
	memcpy(&logsfile[strlen(LOG_ALLDATA)], dev, strlen(dev));
	logsfile[strlen(LOG_ALLDATA) + strlen(dev)] = 0; // null-terminated
	alldata.logsfile = strdup(logsfile);
	// open live pcap
	handle = pcap_open_live(dev, SNAP_LEN, 1, 10000, errbuf);
	if (handle == NULL)
	{
		printf("[!] [DAEMON] Error! Couldn't open device %s : %s\n", dev, errbuf);
		exit(1);
	}
	alldata.dev = dev;
	while (1)
	{
		alldata.snif_data = pcap_next(handle, &hdr);
		if (alldata.snif_data != NULL)
			process_packet(&hdr, &alldata);
		else
			alldata.snif_data = NULL;
	}
}
