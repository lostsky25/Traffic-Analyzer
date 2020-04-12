#ifndef SNIFFPACKETS_H
#define SNIFFPACKETS_H

#include <QCoreApplication>
#include <QElapsedTimer>
#include <QTableWidget>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QTime>

#include "payload.h"
#include "logging.h"

#ifdef __linux__
    #define DEFAULT_DEV "wlx8416f91538ab"
#elif _WIN32
    #define DEFAULT_DEV "/Device/NPF_{447F6203-87BD-431F-8252-765287CC331C}"
// /Device/NPF_{1E696F08-39A9-493E-B3A0-C80DF562B8E7}
// /Device/NPF_{447F6203-87BD-431F-8252-765287CC331C}
// /Device/NPF_{1F9302CB-4A9C-45AF-BAC5-11F305828DCB}
#endif

extern "C"{
    #ifdef __linux__
        #include <pcap.h>
        #include <netinet/in.h>
        #include <netinet/if_ether.h>
    #elif _WIN32
        #include <pcap.h>
        #include <ether.h>
    #else

    #endif

}

#define ETH_SIZE 32

#define SIZE_ETHERNET 14

//Timer mode
#define START_TIMER     0x00000001
#define RESTART_TIMER   0x00000002
#define GET_TIMER       0x00000003

/* Ethernet header */
struct sniff_ethernet {
    u_char ether_dhost[ETHER_ADDR_LEN];     /* destination host address */
    u_char ether_shost[ETHER_ADDR_LEN];     /* source host address */
    u_short ether_type;                     /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
    u_char ip_vhl;                          /* version << 4 | header length >> 2 */
    u_char ip_tos;                          /* type of service */
    u_short ip_len;                         /* total length */
    u_short ip_id;                          /* identification */
    u_short ip_off;                         /* fragment offset field */
    #define IP_RF 0x8000                    /* reserved fragment flag */
    #define IP_DF 0x4000                    /* dont fragment flag */
    #define IP_MF 0x2000                    /* more fragments flag */
    #define IP_OFFMASK 0x1fff               /* mask for fragmenting bits */
    u_char  ip_ttl;                         /* time to live */
    u_char  ip_p;                           /* protocol */
    u_short ip_sum;                         /* checksum */
    struct  in_addr ip_src,ip_dst;          /* source and dest address */
};

#define     IP_HL(ip)    (((ip)->ip_vhl) & 0x0f)
#define     IP_V(ip)     (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
    u_short th_sport;                       /* source port */
    u_short th_dport;                       /* destination port */
    tcp_seq th_seq;                         /* sequence number */
    tcp_seq th_ack;                         /* acknowledgement number */
    u_char  th_offx2;                       /* data offset,rsvd */
    #define TH_OFF(th)       (((th)->th_offx2 & 0xf0) >> 4)
    u_char  th_flags;
    #define TH_FIN 0x01
    #define TH_SYN 0x02
    #define TH_RST 0x04
    #define TH_PUSH 0x08
    #define TH_ACK 0x10
    #define TH_URG 0x20
    #define TH_ECE 0x40
    #define TH_CWR 0x80
    #define TH_FLAGS  (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
    u_short th_win;                         /* window */
    u_short th_sum;                         /* checksum */
    u_short th_urp;                         /* urgent pointer */
};

class SniffPackets : public QThread
{
//    Q_OBJECT
public:
    SniffPackets();
    SniffPackets(QTableWidget*, Payload*);

    static void stopSniff(/*pcap_t**/);
    static void refreshSniff();
    ~SniffPackets();

    void initialyzePcap(char *);
    void setFilter(QString);
    int getLoadOfNet();
//    void setDefaultDevice();
    void setDeviceName(char *);
    void compileFilter(pcap_t *);
    void setFilterExpresion(char *);
    void openSession(char*, int, int, int);
    QStringList getDeviceNames();
    void setNetmask(char *, bpf_u_int32 *, bpf_u_int32 *);

//signals:
//    void sendNameDevices(const QStringList &);

private:
    char* dev;                      //Interface name
    char *filterExp;                //Filter expresion
    Logging *logging;               //For logining
    pcap_if_t *all_devs, *d;            //Singly linked list of all devices
    bool timerStartState = true;    //Elasped time

    struct bpf_program fp;          //Compiled filter
    bpf_u_int32 mask;               //The netmask of our sniffing device
    bpf_u_int32 net;                //The Ip of our sniffing device

    struct pcap_pkthdr header;      //The header that pcap gives us
    const unsigned char *packet;    //The actual packet
    QStringList nameDevices;

    char errbuf[PCAP_ERRBUF_SIZE];  //Error buffer

    static void sniff(unsigned char *useless,const struct pcap_pkthdr* pkthdr,const unsigned char* packet);
    static void print_hex_ascii_line(const u_char *, int, int);
    static void print_payload(const u_char *, int);

    void run() override;

    static double timer(int8_t);


protected:

};

#endif // SNIFFPACKETS_H
