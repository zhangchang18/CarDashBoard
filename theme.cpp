#include "theme.h"
#include "ui_theme.h"

Theme::Theme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Theme)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    for(int i=0;i<=9;i++){
        QString path=QString(":/background/bg/bg%1.png").arg(i);
        imgPaths.push_back(path);
    }
    for(int i=0;i<imgPaths.size();i++){
        QLabel *item=new QLabel(this);
        item->setPixmap(QPixmap(imgPaths.at(i)));
        item->setScaledContents(true);
        ui->gridLayout->addWidget(item,i/3,i%3);
        //item->setFixedSize(QSize(180,150));
        item->installEventFilter(this);
        list_labels.push_back(item);
        item->installEventFilter(this);
//        QString index=QString("%1").arg(i);
        item->setObjectName(QString::number(i));
    }

}

Theme::~Theme()
{
    delete ui;
}

void Theme::on_pushButton_changetheme_clicked()
{
    QString path=imgPaths.at(imgIndex);
    emit sendThemePath(path);
}

bool Theme::eventFilter(QObject *watch, QEvent *event){
    if(event->type()==QEvent::MouseButtonPress){
        QLabel *label=dynamic_cast<QLabel*>(watch);
        if(label==nullptr){
            return false;
        }
//        for(auto iter=list_labels.begin();iter!=list_labels.end();iter++){
//            (*iter)->setStyleSheet("border:2px solid transparent; border-radius:6px;");
//        }
        for(auto iter:list_labels){
            iter->setStyleSheet("border:2px solid transparent; border-radius:6px;");

        }
        label->setStyleSheet("border:3px solid #1E90FF; border-radius:6px;");
        QString index=label->objectName();
        imgIndex=index.toInt();
        return true;
    }
    return QWidget::eventFilter(watch,event);
}
