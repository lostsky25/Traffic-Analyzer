#include "payload.h"


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
        try {
            plain->append(allPacketsPayloads.at(row));
        } catch (...) {
//            qDebug() << "table CRASH";
        }

    }
}

void Payload::clearPlane()
{
    plain->clear();
    plain->update();
}
