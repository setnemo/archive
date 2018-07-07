
#include <sniffer.h>

#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
// void process_ip_packet(const u_char *snif_data, int size);
// void print_ip_packet(const u_char *snif_data, int size);
// void print_tcp_packet(const u_char *snif_data, int size);
// void print_udp_packet(const u_char *snif_data, int size);
// void print_icmp_packet(const u_char *snif_data, int size);
// void print_data (const u_char *data, int size);


struct sockaddr_in source,dest;
int tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j;
 
void print_ethernet_header(const u_char *snif_data, int size, FILE *logfile)
{
	struct ethhdr *eth = (struct ethhdr *)snif_data;
	 
	fprintf(logfile, "\n");
	fprintf(logfile, "Ethernet Header\n");
	fprintf(logfile, "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5] );
	fprintf(logfile, "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5] );
	fprintf(logfile, "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}
 
void print_ip_header(const u_char * snif_data, int size, FILE *logfile)
{
	print_ethernet_header(snif_data, size, logfile);
   
	unsigned short iphdrlen;
		 
	struct iphdr *iph = (struct iphdr *)(snif_data  + sizeof(struct ethhdr));
	iphdrlen =iph->ihl*4;
	 
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->saddr;
	 
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iph->daddr;
	 
	fprintf(logfile, "\n");
	fprintf(logfile, "IP Header\n");
	fprintf(logfile, "   |-IP Version        : %d\n",(unsigned int)iph->version);
	fprintf(logfile, "   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
	fprintf(logfile, "   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
	fprintf(logfile, "   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
	fprintf(logfile, "   |-Identification    : %d\n",ntohs(iph->id));
	fprintf(logfile, "   |-TTL      : %d\n",(unsigned int)iph->ttl);
	fprintf(logfile, "   |-Protocol : %d\n",(unsigned int)iph->protocol);
	fprintf(logfile, "   |-Checksum : %d\n",ntohs(iph->check));
	fprintf(logfile, "   |-Source IP        : %s\n", inet_ntoa(source.sin_addr));
	fprintf(logfile, "   |-Destination IP   : %s\n", inet_ntoa(dest.sin_addr));
}

 
void print_data (const u_char * data, int size, FILE *logfile)
{
	int i, j;
	for (i = 0; i < size ; i++)
	{
		if (i! = 0 && i % 16 == 0)   //if one line of hex printing is complete...
		{
			fprintf(logfile, "         ");
			for (j=i-16 ; j<i ; j++)
			{
				if (data[j]>=32 && data[j]<=128)
					fprintf(logfile, "%c",(unsigned char)data[j]); //if its a number or alphabet
				 
				else fprintf(logfile, "."); //otherwise print a dot
			}
			fprintf(logfile, "\n");
		} 
		 
		if (i%16==0) fprintf(logfile, "   ");
			fprintf(logfile, " %02X",(unsigned int)data[i]);
				 
		if ( i==size-1)  //print the last spaces
		{
			for (j=0;j<15-i%16;j++) 
			{
			  fprintf(logfile, "   "); //extra spaces
			}
			 
			fprintf(logfile, "         ");
			 
			for (j=i-i%16 ; j<=i ; j++)
			{
				if (data[j]>=32 && data[j]<=128) 
				{
				  fprintf(logfile, "%c",(unsigned char)data[j]);
				}
				else
				{
				  fprintf(logfile, ".");
				}
			}
			fprintf(logfile,  "\n" );
		}
	}
}

void print_tcp_packet(const u_char * snif_data, int size, FILE *logfile)
{
	unsigned short iphdrlen;
	 
	struct iphdr *iph = (struct iphdr *)( snif_data  + sizeof(struct ethhdr));
	iphdrlen = iph->ihl*4;
	 
	struct tcphdr *tcph=(struct tcphdr*)(snif_data + iphdrlen + sizeof(struct ethhdr));
			 
	int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
	 
	fprintf(logfile, "\n\n***********************TCP Packet*************************\n");  
		 
	print_ip_header(snif_data,size, logfile);
		 
	fprintf(logfile, "\n");
	fprintf(logfile, "TCP Header\n");
	fprintf(logfile, "   |-Source Port      : %u\n",ntohs(tcph->source));
	fprintf(logfile, "   |-Destination Port : %u\n",ntohs(tcph->dest));
	fprintf(logfile, "   |-Sequence Number    : %u\n",ntohl(tcph->seq));
	fprintf(logfile, "   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
	fprintf(logfile, "   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
	fprintf(logfile, "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
	fprintf(logfile, "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
	fprintf(logfile, "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
	fprintf(logfile, "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
	fprintf(logfile, "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
	fprintf(logfile, "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
	fprintf(logfile, "   |-Window         : %d\n",ntohs(tcph->window));
	fprintf(logfile, "   |-Checksum       : %d\n",ntohs(tcph->check));
	fprintf(logfile, "   |-Urgent Pointer : %d\n",tcph->urg_ptr);
	fprintf(logfile, "\n");
	fprintf(logfile, "                        DATA Dump                         ");
	fprintf(logfile, "\n");
		 
	fprintf(logfile, "IP Header\n");
	print_data(snif_data,iphdrlen, logfile);
		 
	fprintf(logfile, "TCP Header\n");
	print_data(snif_data+iphdrlen,tcph->doff*4, logfile);
		 
	fprintf(logfile, "Data Payload\n");    
	print_data(snif_data + header_size, size - header_size, logfile);
						 
	fprintf(logfile, "\n###########################################################");
}

void print_udp_packet(const u_char *snif_data, int size, FILE *logfile)
{
	 
	unsigned short iphdrlen;
	 
	struct iphdr *iph = (struct iphdr *)(snif_data +  sizeof(struct ethhdr));
	iphdrlen = iph->ihl*4;
	 
	struct udphdr *udph = (struct udphdr*)(snif_data + iphdrlen  + sizeof(struct ethhdr));
	 
	int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
	 
	fprintf(logfile, "\n\n***********************UDP Packet*************************\n");
	 
	print_ip_header(snif_data,size, logfile);           
	 
	fprintf(logfile, "\nUDP Header\n");
	fprintf(logfile, "   |-Source Port      : %d\n", ntohs(udph->source));
	fprintf(logfile, "   |-Destination Port : %d\n", ntohs(udph->dest));
	fprintf(logfile, "   |-UDP Length       : %d\n", ntohs(udph->len));
	fprintf(logfile, "   |-UDP Checksum     : %d\n", ntohs(udph->check));
	 
	fprintf(logfile, "\n");
	fprintf(logfile, "IP Header\n");
	print_data(snif_data, iphdrlen, logfile);
		 
	fprintf(logfile, "UDP Header\n");
	print_data(snif_data+iphdrlen, sizeof udph, logfile);
		 
	fprintf(logfile, "Data Payload\n");    
	 
	//Move the pointer ahead and reduce the size of string
	print_data(snif_data + header_size, size - header_size, logfile);
	 
	fprintf(logfile, "\n###########################################################");
}
 
void print_icmp_packet(const u_char * snif_data, int size, FILE *logfile)
{
	unsigned short iphdrlen;
	 
	struct iphdr *iph = (struct iphdr *)(snif_data  + sizeof(struct ethhdr));
	iphdrlen = iph->ihl * 4;
	 
	struct icmphdr *icmph = (struct icmphdr *)(snif_data + iphdrlen  + sizeof(struct ethhdr));
	 
	int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof icmph;
	 
	fprintf(logfile, "\n\n***********************ICMP Packet*************************\n"); 
	 
	print_ip_header(snif_data, size, logfile);
			 
	fprintf(logfile, "\n");
		 
	fprintf(logfile, "ICMP Header\n");
	fprintf(logfile, "   |-Type : %d",(unsigned int)(icmph->type));
			 
	if ((unsigned int)(icmph->type) == 11)
	{
		fprintf(logfile, "  (TTL Expired)\n");
	}
	else if ((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
	{
		fprintf(logfile, "  (ICMP Echo Reply)\n");
	}
	 
	fprintf(logfile, "   |-Code : %d\n",(unsigned int)(icmph->code));
	fprintf(logfile, "   |-Checksum : %d\n",ntohs(icmph->checksum));
	fprintf(logfile, "\n");
 
	fprintf(logfile, "IP Header\n");
	print_data(snif_data,iphdrlen, logfile);
		 
	fprintf(logfile, "UDP Header\n");
	print_data(snif_data + iphdrlen, sizeof icmph, logfile);
		 
	fprintf(logfile, "Data Payload\n");    
	 
	//Move the pointer ahead and reduce the size of string
	print_data(snif_data + header_size, (size - header_size), logfile);
	 
	fprintf(logfile, "\n###########################################################");
}

 

void process_packet(struct pcap_pkthdr *header, const u_char *snif_data, FILE *logfile)
{
	int size = header->len;
	 
	//Get the IP Header part of this packet, excluding the ethernet header
	struct iphdr *iph = (struct iphdr*)(snif_data + sizeof(struct ethhdr));
	++total;
	switch (iph->protocol) //Check the Protocol and do accordingly...
	{
		case 1:  //ICMP Protocol
			++icmp;
			print_icmp_packet(snif_data, size, logfile);
			break;
		 
		case 2:  //IGMP Protocol
			++igmp;
			break;
		 
		case 6:  //TCP Protocol
			++tcp;
			print_tcp_packet(snif_data, size, logfile);
			break;
		 
		case 17: //UDP Protocol
			++udp;
			print_udp_packet(snif_data, size, logfile);
			break;
		 
		default: //Some Other Protocol like ARP etc.
			++others;
			break;
	}
	printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r", tcp, udp, icmp, igmp, others, total);
}
