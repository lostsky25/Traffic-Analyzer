#ifndef PACKETLISTVEIW_H
#define PACKETLISTVEIW_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QTimer>

#include "filterexpression.h"
#include "SelectedDevice/selecteddevice.h"
#include "sniffpackets.h"
#include "payload.h"
#include "logging.h"



class PacketListVeiw : public QWidget
{
    Q_OBJECT
public:
    explicit PacketListVeiw(QWidget *parent = nullptr);

public slots:
//    void listUpdate(QTableWidgetItem *);
    QStringList getDeviceNames();
    void refreshList();
    void stopUpdate();
    void startSniff(QTableWidgetItem *);
    void setFilterExp(const QString&);

signals:
    void sendFilter(const QString&);
    void lastDeviceName(QTableWidgetItem *);
    void sniffStarted();
    void sniffStoped();
    void sniffRefresh();

private:
    FilterExpression *filterExpression;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    SniffPackets *sniffPackets;
    QTableWidget *tableWidget;
    QString filterExpBuf;
    QTimer *timer;
    Payload *payloadLog;
    QFont fontHelvetica;
    Logging *logging;
};

#endif // PACKETLISTVEIW_H
