#include "sniffpackets.h"

QTableWidget *table;
int row, col;

SniffPackets::SniffPackets(QTableWidget *tableWidget){
    ::row = 0;
    ::col = 0;
    ::table = tableWidget;
}

SniffPackets::~SniffPackets(){
    pcap_freealldevs(all_devs);
    pcap_close(handle);
}

void SniffPackets::init(){
    char filter_exp[] = "tcp";

    //dev = pcap_lookupdev(errbuf);
    dev = "/Device/NPF_{1F9302CB-4A9C-45AF-BAC5-11F305828DCB}";

    qDebug() << "Line: " << __LINE__ << " dev: " << dev << "Error value: " << errbuf;
    qDebug() << "Init started";
    //Default network device
    if (pcap_findalldevs(&all_devs, errbuf) == -1)
    {
        qDebug() << "Error in pcap_findalldevs: " << errbuf;
        //fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        //return EXIT_FAILURE;
    }

    if (dev == NULL)
    {
        qDebug() << "Couldn't find default device: " << errbuf;
        //fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        //return EXIT_FAILURE;
    }

    printf("Dev: %s\n", dev);

    //Find the IPv4 network number and netmask for a device
    if(pcap_lookupnet(dev, &net, &mask, errbuf) == -1){
        qDebug() << "Can't get netmask for device " << dev;
        net = 0;
        mask = 0;
    }

    //Get descriptor of session (sniffing session)
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if(handle == NULL){
        qDebug() << "Couldn't open device %s: " << dev << " " << errbuf;
        //return EXIT_FAILURE;
    }

    if(pcap_compile(handle, &fp, filter_exp, 0, net) == -1){
        qDebug() << "Couldn't parse filter: " << filter_exp;
        //return EXIT_FAILURE;
    }

    if(pcap_setfilter(handle, &fp)){
        qDebug() << "Couldn't install filter: " << filter_exp;
        //return EXIT_FAILURE;
    }
}

void SniffPackets::sniff(unsigned char *useless, const struct pcap_pkthdr* pkthdr, const unsigned char* packet){
    char temp_buf[ETH_SIZE];
    struct ether_header *eth = (struct ether_header *)packet;
    sprintf(temp_buf, "%3d.%3d.%3d.%3d",
            (int)eth->ether_dhost[0],
            (int)eth->ether_dhost[1],
            (int)eth->ether_dhost[2],
            (int)eth->ether_dhost[3]);
    table->setItem(row++, 3, new QTableWidgetItem(temp_buf));
    table->insertRow(row+1);
//    table->selectRow(row); //I should change it.

    //qDebug() << "Row: " << row << " " << temp_buf;
}

void SniffPackets::run(){
    init();
    pcap_loop(handle, 0, sniff, NULL);
    qDebug() << "Other thread started";
}
