#include "bottom.h"
#include "ui_bottom.h"
#include"carcongig.h"
Bottom::Bottom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bottom)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    connect(ui->pushButton_back,&QPushButton::clicked,this,&Bottom::changeToHome);
    int temp=CarCongig::getCar().getTemp();
    ui->label_botwarm->setText(QString("%1℃").arg(temp));
    connect(&CarCongig::getCar(), &CarCongig::sendNewTemp, this, [this](int t){
            ui->label_botwarm->setNum(t);
            ui->label_botwarm->setText(QString("%1℃").arg(t));
        });
}

Bottom::~Bottom()
{
    delete ui;
}

void Bottom::on_pushButton_home_clicked()
{
    emit changeToHome();
}

void Bottom::on_pushButton_setting_clicked()
{
    emit changeToSetting();
}


void Bottom::on_pushButton_air_clicked()
{
    emit changeToAir();
}



void Bottom::on_pushButton_left_clicked()
{
    int temp=CarCongig::getCar().getTemp();
    CarCongig::getCar().setTemp(temp-1);
}

void Bottom::on_pushButton_right_clicked()
{
    int temp=CarCongig::getCar().getTemp();
    CarCongig::getCar().setTemp(temp+1);
}
