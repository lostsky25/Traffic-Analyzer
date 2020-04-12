#ifndef SELECTEDDEVICE_H
#define SELECTEDDEVICE_H

#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QLabel>

//#include "loadchart.h"

class SelectedDevice : public QWidget
{
    Q_OBJECT
public:
    SelectedDevice(QWidget *parent = nullptr);
    QTableWidget *getTable();

public slots:
    void addDevice(const QStringList&);

private:
    QTableWidget *table;
    QVBoxLayout *verticalLayout;

protected:
    int row, column;
};

#endif // SELECTEDDEVICE_H
