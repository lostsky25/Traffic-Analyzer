#include "selecteddevice.h"

SelectedDevice::SelectedDevice(QWidget *parent) : QWidget(parent)
{
    row = column = 0;
//    model = new QStandardItemModel(this);
    table = new QTableWidget(this);
    verticalLayout = new QVBoxLayout(this);

    //Turn off edit mode
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setFrameStyle(QFrame::NoFrame);
    table->setGridStyle(Qt::NoPen);

    table->horizontalHeader()->setStretchLastSection(true);

    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->setColumnCount(2);
    table->setColumnWidth(0, 300);
    table->setColumnWidth(1, 300);

    table->setMinimumSize(QSize(500,500));

    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);


    verticalLayout->addWidget(table);
    setLayout(verticalLayout);
}

QTableWidget* SelectedDevice::getTable()
{
    return table;
}

void SelectedDevice::addDevice(const QStringList &names)
{
    QString description;
    foreach(QString name, names){
        table->insertRow(row);
        QStringList currentName = name.split(" ");
        table->setItem(row, 0, new QTableWidgetItem(currentName[0]));
        currentName.pop_front();

        foreach(QString part, currentName){
            description.append(part + " ");
            qDebug() << part;
        }
        column = 0;
        table->setItem(row, 1, new QTableWidgetItem(description));
        row++;
        description.clear();
    }
}

