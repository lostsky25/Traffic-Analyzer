#ifndef FILTEREXPRESSION_H
#define FILTEREXPRESSION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRegularExpression>
#include <QDebug>

class FilterExpression : public QWidget
{
    Q_OBJECT
public:
    explicit FilterExpression(QWidget *parent = nullptr);
    QVBoxLayout *horizontalLayout;
    QLineEdit *filterExp;

public slots:
    void changeBackground(const QString &);
    bool checkFilterExpression(const QString &);

signals:

};

#endif // FILTEREXPRESSION_H
