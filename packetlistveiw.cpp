#include "packetlistveiw.h"

PacketListVeiw::PacketListVeiw(QWidget *parent) : QWidget(parent)
{
    tableView = new QTableView(this);

    tableView->columnWidth(10);
    tableView->rowHeight(10);

}
