#include "loadchart.h"

LoadChart::LoadChart(QWidget *parent) : QWidget(parent)
{

}

void LoadChart::setPoints(QList<QLine> &series)
{
    this->series.append(series);

    repaint();
}

void LoadChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    foreach(QLine one, series){
        painter.drawLine(one);
        update();
    }
}
