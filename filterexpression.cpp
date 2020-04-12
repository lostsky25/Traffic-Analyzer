#include "filterexpression.h"

FilterExpression::FilterExpression(QWidget *parent) : QWidget(parent)
{
    mainHorizontalLayout = new QHBoxLayout();
    horizontalLayout = new QHBoxLayout();
    listWidget = new QListWidget();
    filterWidget = new QWidget();
    filterExp = new QLineEdit();

    wordList << "tcp" << "udp" << "or";

    applyFilter = new QPushButton();
    applyFilter->setStyleSheet("QPushButton { "
                               "background-color: white; "
                               "margin-right: 20px;"
                               "border-image: url(C:/Users/User/Desktop/filter_enter.png); }"
                               "QPushButton:hover{"
                               "background-color: white; "
                               "margin-right: 20px;"
                               "border-image: url(C:/Users/User/Desktop/filter_enter_hover.png); }"
                               "}");

    QObject::connect(filterExp, SIGNAL(textChanged(const QString &)), this, SLOT(changeBackground(const QString &)));
    QObject::connect(applyFilter, &QPushButton::clicked, this, &FilterExpression::applyFilterEvent);

    filterExp->setFrame(false);

    completer = new QCompleter(wordList, this);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    filterExp->setCompleter(completer);


    applyFilter->setAutoFillBackground(true);

    filterExp->setPlaceholderText("Apply filter (default: tcp or udp)");

    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,100,0);
    horizontalLayout->setMargin(0);

    horizontalLayout->addWidget(filterExp);
    horizontalLayout->addWidget(applyFilter);

    filterWidget->setLayout(horizontalLayout);

    filterWidget->setStyleSheet("* { "
                          "border: 1px solid rgb(105, 105, 105); "
                          "border-radius: 2px;"
                          "background-color: white; "
                          "}");

    filterWidget->setContentsMargins(0, 0, 0, 0);

    mainHorizontalLayout->setSpacing(0);
    mainHorizontalLayout->setMargin(0);
    mainHorizontalLayout->setContentsMargins(3, 4, 24, 4);

    mainHorizontalLayout->addWidget(filterWidget);

    setLayout(mainHorizontalLayout);
}

void FilterExpression::applyFilterEvent(){
    emit selectedFilter(filterExp->text());
}

void FilterExpression::changeBackground(const QString &text){
    if(checkFilterExpression(text)){
        filterExp->setStyleSheet("QLineEdit { background: rgb(175, 255, 175); }");
        wordList.append(text);
    }else if(text.isEmpty()){
        filterExp->setStyleSheet("QLineEdit { background: none; }");
    }else{
        filterExp->setStyleSheet("QLineEdit { background: rgb(255, 175, 175); }");
    }
}

bool FilterExpression::checkFilterExpression(const QString &text){
    QRegularExpression re("(?i)(tcp|udp|or|and)(\W|$)");
    QRegularExpressionMatch match = re.match(text);

    return match.hasMatch();
}
