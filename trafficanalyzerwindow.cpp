#include "trafficanalyzerwindow.h"
#include "ui_trafficanalyzerwindow.h"
#include <winsock2.h>
#include <pcap.h>

TrafficAnalyzerWindow::TrafficAnalyzerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrafficAnalyzerWindow)
{
    ui->setupUi(this);

    QHBoxLayout *hBox = new QHBoxLayout(this);

    PacketListVeiw *list = new PacketListVeiw(this);

    hBox->addWidget(list);

    centralWidget()->setLayout(hBox);

    char *dev, errbuf[PCAP_ERRBUF_SIZE];

    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        qDebug() << "Couldn't find default device: " << errbuf;
    }
    qDebug() << "Device: " << dev;

    qDebug() << "C++ Style Info Message";
}

TrafficAnalyzerWindow::~TrafficAnalyzerWindow()
{
    delete ui;
}

