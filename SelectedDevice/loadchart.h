#ifndef LOADCHART_H
#define LOADCHART_H

#include <QWidget>
#include <QPainter>

class LoadChart : public QWidget
{
    Q_OBJECT
public:
    explicit LoadChart(QWidget *parent = nullptr);

public slots:
    void setPoints(QList<QLine> &);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<QLine> series;

};

#endif // LOADCHART_H
