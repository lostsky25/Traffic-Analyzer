#ifndef PACKETLISTVEIW_H
#define PACKETLISTVEIW_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

#include "sniffpackets.h"

class PacketListVeiw : public QWidget
{
    Q_OBJECT
public:
    explicit PacketListVeiw(QWidget *parent = nullptr);

public slots:
    void listUpdate();

private:
    SniffPackets *sniffPackets;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QFont fontHelvetica;
};

#endif // PACKETLISTVEIW_H
