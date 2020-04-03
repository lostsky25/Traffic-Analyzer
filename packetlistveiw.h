#ifndef PACKETLISTVEIW_H
#define PACKETLISTVEIW_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

#include "filterexpression.h"
#include "sniffpackets.h"
#include "payload.h"
#include "logging.h"

class PacketListVeiw : public QWidget
{
    Q_OBJECT
public:
    explicit PacketListVeiw(QWidget *parent = nullptr);

public slots:
    void listUpdate();
    void refreshList();
    void stopUpdate();
    void getFilterExp(const QString&);

signals:
    void sendFilter(const QString&);
    void sniffStart();
    void sniffStop();
    void sniffRefresh();

private:
    FilterExpression *filterExpression;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    SniffPackets *sniffPackets;
    QTableWidget *tableWidget;
    QString filterExpBuf;
    Payload *payloadLog;
    QFont fontHelvetica;
    Logging *logging;
};

#endif // PACKETLISTVEIW_H
