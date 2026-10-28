#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
    setStyleSheet(R"(
                QLabel{
                    color: white;
                    font-size: 16px;
                    background-color: rgba(51,51,51,0.7);
                    border-radius: 8px;
                    padding: 10px 20px;
                }
            )");
    hide();
    time=new QTimer(this);
    time->setSingleShot(true);
    connect(time,&QTimer::timeout,this,&QLabel::hide);
}

void MyLabel::toastLable(QString str)
{
    setText(str);
    this->adjustSize();
    raise();
    show();
    move(400,350);
    time->start(1000);
}
