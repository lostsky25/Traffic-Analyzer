#include "packetlistveiw.h"

PacketListVeiw::PacketListVeiw(QWidget *parent) : QWidget(parent)
{
    horizontalLayout = new QHBoxLayout(this);

    //Main font for tableWidth
    fontHelvetica = QFont("Helvetica", 8, QFont::Thin);

    //Table (1, 6)
    tableWidget = new QTableWidget(20, 6, this);

    //Set width
    tableWidget->setMinimumWidth(1000);

    //Set font of table (horizontal headers)
//    headerView = tableWidget->horizontalHeader();
    tableWidget->horizontalHeader()->setFont(fontHelvetica);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Hide left ids
    tableWidget->verticalHeader()->hide();

    //Set fixed size for cells
    tableWidget->verticalHeader()->setDefaultSectionSize(5);

    //Set font of table (headers)
    tableWidget->setFont(fontHelvetica);

    //Add main headers (titles)
    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("No.")));
    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Time")));
    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Source")));
    tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Destination")));
    tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Legth")));
    tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("Info")));

    horizontalLayout->addWidget(tableWidget);

    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,0,0);
    horizontalLayout->setMargin(0);

    setLayout(horizontalLayout);
}

void PacketListVeiw::listUpdate(){
    sniffPackets = new SniffPackets(tableWidget);
    sniffPackets->start();
}
