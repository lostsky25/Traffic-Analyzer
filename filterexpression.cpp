#include "filterexpression.h"

FilterExpression::FilterExpression(QWidget *parent) : QWidget(parent)
{
    horizontalLayout = new QVBoxLayout();
    filterExp = new QLineEdit();

    QObject::connect(filterExp, SIGNAL(textChanged(const QString &)), this, SLOT(changeBackground(const QString &)));

    filterExp->setPlaceholderText("Apply filter");

    horizontalLayout->addWidget(filterExp);

    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,100,0);
    horizontalLayout->setMargin(0);

    setLayout(horizontalLayout);
}

void FilterExpression::changeBackground(const QString &text){
    if(checkFilterExpression(text)){
        filterExp->setStyleSheet("QLineEdit { background: rgb(175, 255, 175); }");
    }else if(text.isEmpty()){
        filterExp->setStyleSheet("QLineEdit { background: none; }");
    }else{
        filterExp->setStyleSheet("QLineEdit { background: rgb(255, 175, 175); }");
    }
}

bool FilterExpression::checkFilterExpression(const QString &text){
    QRegularExpression re("(?i)(tcp|udp|or|and)(\W|$)");
    QRegularExpressionMatch match = re.match(text);
    qDebug() << match.hasMatch();
    return match.hasMatch();
}
