#include "updatechart.h"

UpdateChart::UpdateChart()
{
    sniffPackets = new SniffPackets();
}

void UpdateChart::run()
{
    sniffPackets->initialyzePcap();
    static int i = 0;

    while(1){
        point.setLine(1, 1, i++, sniffPackets->getLoadOfNet());
        series.append(point);
        emit newPoint(series);
    }
}
