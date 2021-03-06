#include "payload.h"
#include <QMessageLogger>

Payload::Payload(QWidget *parent) : QWidget(parent)
{
    plain = new QTextEdit();
    verticalLayout = new QVBoxLayout();

    verticalLayout->addWidget(plain);

    setLayout(verticalLayout);
}

void Payload::appendPayload(QString text){
    allPacketsPayloads.append(text);
}

void Payload::cellActivated(int row, int column)
{
    if(!allPacketsPayloads.isEmpty() && (allPacketsPayloads.length() > row)){
        plain->clear();
        plain->update();
        plain->append(allPacketsPayloads.at(row));
    }
}

void Payload::clearData(){
    allPacketsPayloads.clear();
}

void Payload::clearPlane()
{
    plain->clear();
    plain->update();
}
