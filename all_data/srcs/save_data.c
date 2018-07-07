
#include <sniffer.h>

#include <netinet/ip_icmp.h>	//Provides declarations for icmp header
#include <netinet/udp.h>		//Provides declarations for udp header
#include <netinet/tcp.h>		//Provides declarations for tcp header
#include <netinet/ip.h>			//Provides declarations for ip header
#include <arpa/inet.h>			// for inet_ntoa()
#include <net/ethernet.h>

void print_ethernet_header(t_tosave *alldata)
{
	struct ethhdr *eth = (struct ethhdr *)alldata->snif_data;
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "Ethernet Header\n");
	fprintf(alldata->logfile, "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5] );
	fprintf(alldata->logfile, "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5] );
	fprintf(alldata->logfile, "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}

void print_ip_header(t_tosave *alldata)
{
	struct sockaddr_in source,dest;
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)(alldata->snif_data + sizeof(struct ethhdr));
	print_ethernet_header(alldata);
	iphdrlen = iph->ihl * 4;
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->saddr;
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iph->daddr;
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "IP Header\n");
	fprintf(alldata->logfile, "   |-IP Version        : %d\n",(unsigned int)iph->version);
	fprintf(alldata->logfile, "   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl)) * 4);
	fprintf(alldata->logfile, "   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
	fprintf(alldata->logfile, "   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
	fprintf(alldata->logfile, "   |-Identification    : %d\n",ntohs(iph->id));
	fprintf(alldata->logfile, "   |-TTL      : %d\n",(unsigned int)iph->ttl);
	fprintf(alldata->logfile, "   |-Protocol : %d\n",(unsigned int)iph->protocol);
	fprintf(alldata->logfile, "   |-Checksum : %d\n",ntohs(iph->check));
	fprintf(alldata->logfile, "   |-Source IP        : %s\n", inet_ntoa(source.sin_addr));
	fprintf(alldata->logfile, "   |-Destination IP   : %s\n", inet_ntoa(dest.sin_addr));
	alldata->ipfile = fopen(LOG_COUNT_IP, "a+");
	if (alldata->ipfile == NULL)
	{
		printf("[!] [SNIFFER] Error! Couldn't create 'ip log' file!\n");
		exit(3);
	}
	alldata->ifacefile = fopen(LOG_COUNT_IFACES, "a+");
	if (alldata->ifacefile == NULL)
	{
		printf("[!] [SNIFFER] Error! Couldn't create 'interface count' file!\n");
		exit(3);
	}
	fprintf(alldata->ipfile, "%s\n", inet_ntoa(source.sin_addr));
	fprintf(alldata->ifacefile, "%s\n", alldata->dev);
	fclose(alldata->ipfile);
	fclose(alldata->ifacefile);

}

void print_data(const u_char * data, int size, FILE *logfile)
{
	int i, j;
	for (i = 0; i < size ; i++)
	{
		if (i != 0 && i % 16 == 0)   //if one line of hex printing is complete...
		{
			fprintf(logfile, "         ");
			for (j = i - 16; j < i; j++)
			{
				if (data[j] >= 32 && data[j] <= 128)
					fprintf(logfile, "%c",(unsigned char)data[j]); //if its a number or alphabet
				else
					fprintf(logfile, "."); //otherwise print a dot
			}
			fprintf(logfile, "\n");
		} 
		if (i % 16 == 0)
			fprintf(logfile, "   ");
		fprintf(logfile, " %02X",(unsigned int)data[i]);
		if (i == size - 1)  //print the last spaces
		{
			for (j = 0; j < 15 - i % 16; j++) 
			{
				fprintf(logfile, "   "); //extra spaces
			}
			fprintf(logfile, "         ");
			for (j = i - i % 16; j <= i; j++)
			{
				if (data[j] >= 32 && data[j] <= 128) 
					fprintf(logfile, "%c",(unsigned char)data[j]);
				else
					fprintf(logfile, ".");
			}
			fprintf(logfile,  "\n" );
		}
	}
}

void print_tcp_packet(t_tosave *alldata)
{
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)(alldata->snif_data + sizeof(struct ethhdr));
	iphdrlen = iph->ihl * 4;
	struct tcphdr *tcph=(struct tcphdr*)(alldata->snif_data + iphdrlen + sizeof(struct ethhdr));
	int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff * 4;
	fprintf(alldata->logfile, "\n\n***********************TCP Packet*************************\n");  
	print_ip_header(alldata);
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "TCP Header\n");
	fprintf(alldata->logfile, "   |-Source Port      : %u\n",ntohs(tcph->source));
	fprintf(alldata->logfile, "   |-Destination Port : %u\n",ntohs(tcph->dest));
	fprintf(alldata->logfile, "   |-Sequence Number    : %u\n",ntohl(tcph->seq));
	fprintf(alldata->logfile, "   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
	fprintf(alldata->logfile, "   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff * 4);
	fprintf(alldata->logfile, "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
	fprintf(alldata->logfile, "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
	fprintf(alldata->logfile, "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
	fprintf(alldata->logfile, "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
	fprintf(alldata->logfile, "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
	fprintf(alldata->logfile, "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
	fprintf(alldata->logfile, "   |-Window         : %d\n",ntohs(tcph->window));
	fprintf(alldata->logfile, "   |-Checksum       : %d\n",ntohs(tcph->check));
	fprintf(alldata->logfile, "   |-Urgent Pointer : %d\n",tcph->urg_ptr);
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "                        DATA Dump                         ");
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "IP Header\n");
	print_data(alldata->snif_data, iphdrlen, alldata->logfile);
	fprintf(alldata->logfile, "TCP Header\n");
	print_data(alldata->snif_data+iphdrlen,tcph->doff * 4, alldata->logfile);
	fprintf(alldata->logfile, "Data Payload\n");    
	print_data(alldata->snif_data + header_size, alldata->size - header_size, alldata->logfile);
	fprintf(alldata->logfile, "\n###########################################################");
}

void print_udp_packet(t_tosave *alldata)
{
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)(alldata->snif_data +  sizeof(struct ethhdr));
	iphdrlen = iph->ihl * 4;
	struct udphdr *udph = (struct udphdr*)(alldata->snif_data + iphdrlen + sizeof(struct ethhdr));
	int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
	fprintf(alldata->logfile, "\n\n***********************UDP Packet*************************\n");
	print_ip_header(alldata);           
	fprintf(alldata->logfile, "\nUDP Header\n");
	fprintf(alldata->logfile, "   |-Source Port      : %d\n", ntohs(udph->source));
	fprintf(alldata->logfile, "   |-Destination Port : %d\n", ntohs(udph->dest));
	fprintf(alldata->logfile, "   |-UDP Length       : %d\n", ntohs(udph->len));
	fprintf(alldata->logfile, "   |-UDP Checksum     : %d\n", ntohs(udph->check));
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "IP Header\n");
	print_data(alldata->snif_data, iphdrlen, alldata->logfile);
	fprintf(alldata->logfile, "UDP Header\n");
	print_data(alldata->snif_data+iphdrlen, sizeof udph, alldata->logfile);
	fprintf(alldata->logfile, "Data Payload\n");    
	//Move the pointer ahead and reduce the size of string
	print_data(alldata->snif_data + header_size, alldata->size - header_size, alldata->logfile);
	fprintf(alldata->logfile, "\n###########################################################");
}

void print_icmp_packet(t_tosave *alldata)
{
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)(alldata->snif_data + sizeof(struct ethhdr));
	iphdrlen = iph->ihl * 4;
	struct icmphdr *icmph = (struct icmphdr *)(alldata->snif_data + iphdrlen + sizeof(struct ethhdr));
	int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof icmph;
	fprintf(alldata->logfile, "\n\n***********************ICMP Packet*************************\n"); 
	print_ip_header(alldata);
	fprintf(alldata->logfile, "\n");
	fprintf(alldata->logfile, "ICMP Header\n");
	fprintf(alldata->logfile, "   |-Type : %d",(unsigned int)(icmph->type));
	if ((unsigned int)(icmph->type) == 11)
	{
		fprintf(alldata->logfile, "  (TTL Expired)\n");
	}
	else if ((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
	{
		fprintf(alldata->logfile, "  (ICMP Echo Reply)\n");
	}
	fprintf(alldata->logfile, "   |-Code : %d\n",(unsigned int)(icmph->code));
	fprintf(alldata->logfile, "   |-Checksum : %d\n",ntohs(icmph->checksum));
	fprintf(alldata->logfile, "\n");

	fprintf(alldata->logfile, "IP Header\n");
	print_data(alldata->snif_data, iphdrlen, alldata->logfile);
	fprintf(alldata->logfile, "UDP Header\n");
	print_data(alldata->snif_data + iphdrlen, sizeof icmph, alldata->logfile);
	fprintf(alldata->logfile, "Data Payload\n");    
	//Move the pointer ahead and reduce the size of string
	print_data(alldata->snif_data + header_size, (alldata->size - header_size), alldata->logfile);
	fprintf(alldata->logfile, "\n###########################################################");
}

void process_packet(struct pcap_pkthdr *header, t_tosave *alldata)
{
	alldata->size = header->len;
	alldata->logfile = fopen(alldata->logsfile, "a+");
	if (alldata->logfile == NULL)
	{
		printf("[!] [SNIFFER] Error! Couldn't create 'all data log' file!\n");
		exit(2);
	}
	//Get the IP Header part of this packet, excluding the ethernet header
	struct iphdr *iph = (struct iphdr*)(alldata->snif_data + sizeof(struct ethhdr));
	switch (iph->protocol) //Check the Protocol and do accordingly...
	{
		case 1:  //ICMP Protocol
			print_icmp_packet(alldata);
			break;
		case 2:  //IGMP Protocol
			break;
		case 6:  //TCP Protocol
			print_tcp_packet(alldata);
			break;
		case 17: //UDP Protocol
			print_udp_packet(alldata);
			break;
		default: //Some Other Protocol like ARP etc.
			break;
	}
	fclose(alldata->logfile);
}
