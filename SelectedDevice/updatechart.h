#ifndef UPDATECHART_H
#define UPDATECHART_H

#include <QThread>
#include <QLine>

#include "../sniffpackets.h"

class UpdateChart : public QThread
{
    Q_OBJECT
public:
    UpdateChart();
    void foo();

signals:
    void newPoint(QList<QLine> &);

private:
    SniffPackets *sniffPackets;
    QList<QLine> series;
    QLine point;

protected:
    void run() override;
};

#endif // UPDATECHART_H
