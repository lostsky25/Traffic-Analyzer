#include "sniffpackets.h"

QTableWidget *table;
Payload *payloadLog;
int row, col;
//double lastTime;
pcap_t *handle;
QString buf;
QString fullPayloadStr;
char *filterExpBuf;

SniffPackets::SniffPackets(){

}

SniffPackets::SniffPackets(QTableWidget *tableWidget, Payload *payloadLog){
    ::row = 0;
    ::col = 0;
    ::table = tableWidget;
    ::payloadLog = payloadLog;
}

SniffPackets::~SniffPackets(){
    pcap_freealldevs(all_devs);
    pcap_close(handle);
//    free(::fullPayloadStr);
}

void SniffPackets::setFilter(QString buf){
    QByteArray ba = buf.toLatin1();
    ::filterExpBuf = ba.data();
}

void SniffPackets::init(){
//    timer1 = new QTimer();
//    QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(emit newPacket(fullPayloadStr)));

//    timer1->start(100);

    char *filter_exp = (char*)::filterExpBuf;
    qDebug() << "FILTER EXP: " << filter_exp << ::filterExpBuf;

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
    fullPayloadStr = (char*)malloc(50);
}

/*
 * print data in rows of 16 bytes: offset   hex   ascii
 *
 * 00000   47 45 54 20 2f 20 48 54  54 50 2f 31 2e 31 0d 0a   GET / HTTP/1.1..
 */
void SniffPackets::print_hex_ascii_line(const u_char *payload, int len, int offset)
{
//    static int count = 0;
    int i;
    int gap;
    const u_char *ch;
    /* offset */
//    fullPayloadStr.append(QString::number(offset));
//    qDebug() << fullPayloadStr;
    buf.sprintf("%05d   ", offset);
    fullPayloadStr.append(buf);

    /* hex */
    ch = payload;
    for(i = 0; i < len; i++) {
        buf.sprintf("%02x ", *ch);
        fullPayloadStr.append(buf);
        ch++;
        /* print extra space after 8th byte for visual aid */
        if (i == 7){
            buf.sprintf(" ");
            fullPayloadStr.append(buf);
        }
    }
    /* print space to handle line less than 8 bytes */
    if (len < 8){
        buf.sprintf(" ");
        fullPayloadStr.append(buf);
    }

    /* fill hex gap with spaces if not full line */
    if (len < 16) {
        gap = 16 - len;
        for (i = 0; i < gap; i++) {
            buf.sprintf("   ");
            fullPayloadStr.append(buf);
        }
    }
    buf.sprintf("   ");
    fullPayloadStr.append(buf);

    /* ascii (if printable) */
    ch = payload;
    for(i = 0; i < len; i++) {
        if (isprint(*ch)){
            buf.sprintf("%c", *ch);
            fullPayloadStr.append(buf);
        }
        else{
            buf.sprintf(".");
            fullPayloadStr.append(buf);
        }
        ch++;
    }
//    count++;
//    sprintf(fullPayloadStr + strlen(fullPayloadStr), "\n");
//    qDebug() << fullPayloadStr;
//    sniffPackets.newPacket(fullPayloadStr);

//    if(count < 200){
//        buf.sprintf("\n");
//        fullPayloadStr.append(buf);
//    }
//    else{
//        ::payloadLog->appendPayload(fullPayloadStr);
//        count = 0;
//        fullPayloadStr.clear();
//    }
    buf.sprintf("\n");
    fullPayloadStr.append(buf);

//    ::payloadLog->update();
//    free(fullPayloadStr);
//    fullPayloadStr.clear();
return;
}

void SniffPackets::print_payload(const u_char *payload, int len)
{
    int len_rem = len;
    int line_width = 16;			/* number of bytes per line */
    int line_len;
    int offset = 0;					/* zero-based offset counter */
    const u_char *ch = payload;

    if (len <= 0)
        return;

    /* data fits on one line */
    if (len <= line_width) {
        print_hex_ascii_line(ch, len, offset);
        return;
    }

    /* data spans multiple lines */
    for ( ;; ) {
        /* compute current line length */
        line_len = line_width % len_rem;
        /* print line */
        print_hex_ascii_line(ch, line_len, offset);
        /* compute total remaining */
        len_rem = len_rem - line_len;
        /* shift pointer to remaining bytes to print */
        ch = ch + line_len;
        /* add offset */
        offset = offset + line_width;
        /* check if we have line width chars or less */
        if (len_rem <= line_width) {
            /* print last line and get out */
            print_hex_ascii_line(ch, len_rem, offset);
            break;
        }
    }
return;
}

void SniffPackets::sniff(unsigned char *useless, const struct pcap_pkthdr* pkthdr, const unsigned char* packet){
    char temp_buf[ETH_SIZE];
    const struct sniff_ethernet *ethernet = (struct sniff_ethernet *)packet;    /* The ethernet header */
    const struct sniff_ip *ip;                                                  /* The IP header */
    const struct sniff_tcp *tcp;                                                /* The TCP header */
    const unsigned char *payload;                                               /* Packet payload */

    u_int size_ip;
    u_int size_tcp;

    struct ether_header *eth = (struct ether_header *)packet;

    ethernet = (struct sniff_ethernet*)(packet);
    ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
    size_ip = IP_HL(ip)*4;

    if (size_ip < 20) {
        printf("   * Invalid IP header length: %u bytes\n", size_ip);
        return;
    }

    tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
    size_tcp = TH_OFF(tcp)*4;

    if (size_tcp < 20) {
        printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
        return;
    }

    //No
    table->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
    //!No

    //Time
    sprintf(temp_buf, "%.3lf", (/*lastTime + */SniffPackets::timer(GET_TIMER)));
    table->setItem(row, 1, new QTableWidgetItem(temp_buf));
    //!Time

    //Source
    sprintf(temp_buf, "%3d.%3d.%3d.%3d", (int)eth->ether_shost[0], (int)eth->ether_shost[1], (int)eth->ether_shost[2], (int)eth->ether_shost[3]);
    table->setItem(row, 2, new QTableWidgetItem(temp_buf));
    table->insertRow(row+1);
    //!Source

    payload = (unsigned char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
//    QString str = "";


//    qDebug() << "Row: " << row << " " << payload;
    //Distination
//    sprintf(temp_buf, "%s", payload);
//    table->setItem(row, 3, new QTableWidgetItem(temp_buf));
//    table->insertRow(row+1);
    //!Distination

    //Distination
    sprintf(temp_buf, "%3d.%3d.%3d.%3d", (int)eth->ether_dhost[0], (int)eth->ether_dhost[1], (int)eth->ether_dhost[2], (int)eth->ether_dhost[3]);
    table->setItem(row, 3, new QTableWidgetItem(temp_buf));
    table->insertRow(row+1);
    //!Distination

    print_payload(payload, size_tcp);
    ::payloadLog->appendPayload(fullPayloadStr);
//    qDebug() << endl << endl << fullPayloadStr;
    fullPayloadStr.clear();

    row++;
}

void SniffPackets::refreshSniff(){
    ::row = 0;
    ::col = 0;
//    ::lastTime = 0;
    table->clearContents();
    table->setRowCount(30);
    timer(RESTART_TIMER);
}

void SniffPackets::stopSniff(/*pcap_t**/){
//    lastTime = timer(GET_TIMER);
//    timer(RESTART_TIMER);
    pcap_breakloop(handle);
}

void SniffPackets::run(){
    init();
    refreshSniff();
    if(timerStartState){
        timer(START_TIMER);
        timerStartState = false;
    }

    pcap_loop(handle, 0, sniff, NULL);
}

double SniffPackets::timer(int8_t state)
{
    static QElapsedTimer *elaspedTimer = new QElapsedTimer();

    switch (state) {
        case START_TIMER:{
            elaspedTimer->start();
            break;
        }
        case RESTART_TIMER:{
            elaspedTimer->restart();
            break;
        }
        case GET_TIMER:{
            return (double)elaspedTimer->elapsed() / 1000.000f;
            break;
        }
        default:{
            qDebug() << "Timer: value not found";
            break;
        }
    }
    return 0;
}
