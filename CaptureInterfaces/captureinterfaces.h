#ifndef CAPTUREINTERFACES_H
#define CAPTUREINTERFACES_H

#include <QWidget>
#include <QTabWidget>
#include <QDialog>
#include <QDebug>
#include <QHBoxLayout>

#include "input.h"
#include "options.h"
#include "output.h"

class CaptureInterfaces : public QDialog
{
    Q_OBJECT
public:
    explicit CaptureInterfaces(QWidget *parent = nullptr);
    ~CaptureInterfaces();

signals:

private:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
};

#endif // CAPTUREINTERFACES_H
