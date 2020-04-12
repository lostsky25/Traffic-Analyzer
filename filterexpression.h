#ifndef FILTEREXPRESSION_H
#define FILTEREXPRESSION_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCompleter>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QEvent>
#include <QRegularExpression>
#include <QDebug>

class FilterExpression : public QWidget
{
    Q_OBJECT
public:
    explicit FilterExpression(QWidget *parent = nullptr);
    QPushButton *applyFilter;
    QLineEdit *filterExp;

public slots:
    void applyFilterEvent();
    void changeBackground(const QString &);
    bool checkFilterExpression(const QString &);

signals:
    void selectedFilter(const QString&);

private:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *mainHorizontalLayout;
    QWidget *filterWidget;
    QCompleter *completer;
    QStringList wordList;
    QListWidget *listWidget;

};

#endif // FILTEREXPRESSION_H
