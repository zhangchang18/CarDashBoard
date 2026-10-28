#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QTimer>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent =nullptr);
    void toastLable(QString str);
private:
    QTimer *time;

};

#endif // MYLABEL_H
