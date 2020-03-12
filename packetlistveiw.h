#ifndef PACKETLISTVEIW_H
#define PACKETLISTVEIW_H

#include <QWidget>
#include <QTableView>

class PacketListVeiw : public QWidget
{
    Q_OBJECT
public:
    explicit PacketListVeiw(QWidget *parent = nullptr);

private:
    QTableView *tableView;
signals:

};

#endif // PACKETLISTVEIW_H
