#include "packetlistveiw.h"

PacketListVeiw::PacketListVeiw(QWidget *parent) : QWidget(parent)
{
    logging = new Logging();
    horizontalLayout = new QHBoxLayout(this);
    verticalLayout = new QVBoxLayout(this);

    //Main font for tableWidth
    fontHelvetica = QFont("Helvetica", 8, QFont::Thin);

    //Table (1, 6)
    tableWidget = new QTableWidget(30, 6, this);

    //Set width
    tableWidget->setMinimumWidth(1000);

    //Turn off edit
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Set font of table (horizontal headers)
    tableWidget->horizontalHeader()->setFont(fontHelvetica);

    //Hide left ids
    tableWidget->verticalHeader()->hide();

    //Set font of table (headers)
    tableWidget->setFont(fontHelvetica);

    tableWidget->setColumnCount(7);

    //Add main headers (titles)
    tableWidget->setHorizontalHeaderLabels(QStringList()
                                           << tr("No.")
                                           << tr("Time")
                                           << tr("Source")
                                           << tr("Destination")
                                           << tr("Protocol")
                                           << tr("Legth")
                                           << tr("Info"));
    tableWidget->setColumnWidth(0, 60);
    tableWidget->setColumnWidth(1, 100);
    tableWidget->setColumnWidth(2, 145);
    tableWidget->setColumnWidth(3, 145);
    tableWidget->setColumnWidth(4, 80);
    tableWidget->setColumnWidth(5, 60);
    tableWidget->setColumnWidth(6, 1270);

    //Set scrollbar visable
    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    payloadLog = new Payload(this);
    filterExpression = new FilterExpression(this);
    sniffPackets = new SniffPackets(tableWidget, payloadLog);

    QObject::connect(tableWidget, &QTableWidget::cellClicked, payloadLog, &Payload::cellActivated);
    QObject::connect(filterExpression->filterExp, SIGNAL(textChanged(const QString&)), this, SLOT(setFilterExp(const QString&)));
    QObject::connect(filterExpression, SIGNAL(selectedFilter(const QString&)), this, SLOT(setFilterExp(const QString&)));
    QObject::connect(this, &PacketListVeiw::sendFilter, sniffPackets, &SniffPackets::setFilter);
    QObject::connect(this, &PacketListVeiw::sniffStarted, payloadLog, &Payload::clearPlane);
    QObject::connect(this, &PacketListVeiw::sniffStoped, payloadLog, &Payload::clearPlane);
    QObject::connect(this, &PacketListVeiw::sniffRefresh, payloadLog, &Payload::clearPlane);

    verticalLayout->addWidget(filterExpression);
    verticalLayout->addWidget(tableWidget);
    verticalLayout->addWidget(payloadLog);

//    filterExpression->hide();
    tableWidget->hide();
    payloadLog->hide();

    //Set margins to zero (vertical)
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0,0,0,0);
    verticalLayout->setMargin(0);

    horizontalLayout->addLayout(verticalLayout);

    //Set margins to zero (horizontal)
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,0,0);
    horizontalLayout->setMargin(0);

    setLayout(horizontalLayout);
}

QStringList PacketListVeiw::getDeviceNames(){
    return sniffPackets->getDeviceNames();
}

void PacketListVeiw::setFilterExp(const QString &filterExpBuf){
    logging->messageHandler(QtInfoMsg, QString("Set filter: %1").arg(filterExpBuf));
    qDebug() << QString("Set filter: %1").arg(filterExpBuf);
    this->filterExpBuf = filterExpBuf;
}

void PacketListVeiw::refreshList(){
    logging->messageHandler(QtInfoMsg, QString("Refresh"));
    sniffPackets->refreshSniff();
    emit sniffRefresh();
}

void PacketListVeiw::stopUpdate(){
    logging->messageHandler(QtInfoMsg, QString("Stop"));
    sniffPackets->stopSniff();
    emit sniffStoped();
}

void PacketListVeiw::startSniff(QTableWidgetItem *devName)
{
    QString name = "\\" + devName->text().toUtf8();
    QByteArray buf = name.toLocal8Bit();
    char *c_buf =  buf.data();

    emit lastDeviceName(devName);

    sniffPackets->initialyzePcap(c_buf);
    sniffPackets->start();

    if(!(tableWidget->isVisible() && payloadLog->isVisible())){
        tableWidget->setVisible(true);
        payloadLog->setVisible(true);
    }

    emit sniffStarted();

    if(this->filterExpBuf == ""){
        this->filterExpBuf = "tcp or udp";
    }

    //emit sendFilter(this->filterExpBuf);
}
