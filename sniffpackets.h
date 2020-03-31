#ifndef SNIFFPACKETS_H
#define SNIFFPACKETS_H

#include <QThread>
#include <QTableWidget>
#include <QDebug>

extern "C"{
    #include <pcap.h>
    #include <ether.h>
}

#define ETH_SIZE 32

class SniffPackets : public QThread
{
public:
    SniffPackets(QTableWidget *tableWidget);
    ~SniffPackets();

private:
    char* dev;
    pcap_t *handle;
    pcap_if_t *all_devs;
    int count = 0, selected_index = 0;

    struct bpf_program fp;          //Compiled filter
    bpf_u_int32 mask;               //The netmask of our sniffing device
    bpf_u_int32 net;                //The Ip of our sniffing device

    struct pcap_pkthdr header;      //The header that pcap gives us
    const unsigned char *packet;    //The actual packet

    char errbuf[PCAP_ERRBUF_SIZE];
    void init();
    static void sniff(unsigned char *useless,const struct pcap_pkthdr* pkthdr,const unsigned char* packet);
    void run() override;

protected:

};

#endif // SNIFFPACKETS_H
