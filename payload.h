#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

class Payload : public QWidget
{
    Q_OBJECT
public:
    explicit Payload(QWidget *parent = nullptr);
    void add();

public slots:
    void appendPayload(QString text);
    void cellActivated(int, int);
    void clearPlane();
    void clearData();

private:
    QStringList allPacketsPayloads;
    QTextEdit *plain;
    QVBoxLayout *verticalLayout;
    QString text;
};

#endif // PAYLOAD_H
