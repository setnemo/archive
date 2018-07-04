#include <stdio.h>
#include <pcap.h>
#include <sniffer.h>

int main(void)
{
	char *dev, errbuf[PCAP_ERRBUF_SIZE];

	dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "[!] Couldn't find default device: %s\n", errbuf);
		return(2);
	}
	printf("Device: %s\n", dev);
	pcap_if_t *devlist;
	pcap_if_t *d;

	if(pcap_findalldevs(&devlist,errbuf) == -1)
	{
		fprintf(stderr, "[!] Couldn't find devices: %s\n", errbuf);
	}
	for (d=devlist; d; d=d->next)
	{
		printf("Device: %s ====|||%s\n", d->name, d->description);
	}
	return(0);
}