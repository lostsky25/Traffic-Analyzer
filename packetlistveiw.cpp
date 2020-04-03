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

    //Set font of table (horizontal headers)
//    headerView = tableWidget->horizontalHeader();
    tableWidget->horizontalHeader()->setFont(fontHelvetica);
//    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Hide left ids
    tableWidget->verticalHeader()->hide();

    //Set fixed size for cells
//    tableWidget->horizontalHeader()->setDefaultSectionSize(20);
//    tableWidget->verticalHeader()->setDefaultSectionSize(20);

    //Set font of table (headers)
    tableWidget->setFont(fontHelvetica);

    //Add main headers (titles)
//    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("No.")));
//    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Time")));
//    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Source")));
//    tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Destination")));
//    tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Legth")));
//    tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("Info")));

    tableWidget->setColumnCount(7);
    tableWidget->setHorizontalHeaderLabels(QStringList() << tr("No.") << tr("Time") << tr("Source") << tr("Destination") << tr("Protocol") << tr("Legth") << tr("Info"));
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
    QObject::connect(filterExpression->filterExp, SIGNAL(textChanged(const QString&)), this, SLOT(getFilterExp(const QString&)));
    QObject::connect(this, &PacketListVeiw::sendFilter, sniffPackets, &SniffPackets::setFilter);
    QObject::connect(this, &PacketListVeiw::sniffStart, payloadLog, &Payload::clearPlane);
    QObject::connect(this, &PacketListVeiw::sniffStop, payloadLog, &Payload::clearPlane);
    QObject::connect(this, &PacketListVeiw::sniffRefresh, payloadLog, &Payload::clearPlane);

    verticalLayout->addWidget(filterExpression);
    verticalLayout->addWidget(tableWidget);
    verticalLayout->addWidget(payloadLog);

    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0,0,0,0);
    verticalLayout->setMargin(0);

//    horizontalLayout->addWidget(tableWidget);
//    horizontalLayout->addWidget(payloadLog);
    horizontalLayout->addLayout(verticalLayout);

    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,0,0);
    horizontalLayout->setMargin(0);

    setLayout(horizontalLayout);
}

void PacketListVeiw::getFilterExp(const QString &filterExpBuf){
    this->filterExpBuf = filterExpBuf;
}

void PacketListVeiw::listUpdate(){
    logging->messageHandler(QtInfoMsg, QString("Update list (start)"));
    sniffPackets->start();
    emit sniffStart();
    emit sendFilter(this->filterExpBuf);
}

void PacketListVeiw::refreshList(){
    logging->messageHandler(QtInfoMsg, QString("Refresh"));
    sniffPackets->refreshSniff();
    emit sniffRefresh();
}

void PacketListVeiw::stopUpdate(){
    logging->messageHandler(QtInfoMsg, QString("Stop"));
    sniffPackets->stopSniff();
    emit sniffStop();
//    sniffPackets->terminate(); //???

//    delete sniffPackets;
}
