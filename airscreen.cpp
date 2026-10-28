#include "airscreen.h"
#include "ui_airscreen.h"
#include"carcongig.h"
AirScreen::AirScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirScreen)
{
    ui->setupUi(this);
    label=new MyLabel(this);
    setAttribute(Qt::WA_StyledBackground);
    showTemp(CarCongig::getCar().getTemp());
    connect(&CarCongig::getCar(), &CarCongig::sendNewTemp,
                this, &AirScreen::showTemp);
    connect(&CarCongig::getCar(), &CarCongig::sendAutoChanged, this, &AirScreen::onAutoChanged);
    connect(&CarCongig::getCar(), &CarCongig::sendFanChanged,  this, &AirScreen::onFanChanged);
    connect(&CarCongig::getCar(), &CarCongig::sendAcChanged,   this, &AirScreen::onAcChanged);
    connect(&CarCongig::getCar(), &CarCongig::sendInnerChanged,this, &AirScreen::onInnerChanged);
    connect(&CarCongig::getCar(), &CarCongig::sendVentChanged, this, &AirScreen::onVentChanged);
    connect(&CarCongig::getCar(), &CarCongig::sendDefrostChanged, this, &AirScreen::onDefrostChanged);
    ui->pushButton->setCheckable(true);
    ui->pushButton_2->setCheckable(true);
    ui->pushButton_3->setCheckable(true);
    ui->pushButton_4->setCheckable(true);
    ui->pushButton_5->setCheckable(true);
    ui->pushButton_6->setCheckable(true);
    ui->pushButton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    ui->pushButton_2->setStyleSheet("QPushButton{border:none;background:transparent;}");
    ui->pushButton_3->setStyleSheet("QPushButton{border:none;background:transparent;}");
    ui->pushButton_4->setStyleSheet("QPushButton{border:none;background:transparent;}");
    ui->pushButton_5->setStyleSheet("QPushButton{border:none;background:transparent;}");
    ui->pushButton_6->setStyleSheet("QPushButton{border:none;background:transparent;}");
    int level=CarCongig::getCar().getLevel();
    ui->widget->setLevel(level);

}

AirScreen::~AirScreen()
{
    delete ui;
}



void AirScreen::on_pushButton_up_clicked()
{
    int temp=CarCongig::getCar().getTemp();
    CarCongig::getCar().setTemp(temp+1);
}

void AirScreen::on_pushButton_down_clicked()
{
    int temp=CarCongig::getCar().getTemp();
    CarCongig::getCar().setTemp(temp-1);
}

void AirScreen::showTemp(int temp)
{
    ui->label_now->setText(QString("%1℃").arg(temp));
//    ui->label_now->setNum(temp);
    if (temp >= 30)
            ui->label_up->clear();      // 到顶不显示
        else
            ui->label_up->setNum(temp + 1);

        if (temp <= 16)
            ui->label_down->clear();    // 到底不显示
        else
            ui->label_down->setNum(temp - 1);


}

void AirScreen::on_pushButton_clicked()
{
    bool on = ui->pushButton->isChecked();
        CarCongig::getCar().setAuto(on);
}

void AirScreen::on_pushButton_2_clicked()
{
    bool on = ui->pushButton_2->isChecked();
        CarCongig::getCar().setFan(on);
}

void AirScreen::on_pushButton_3_clicked()
{
    bool on = ui->pushButton_3->isChecked();
        CarCongig::getCar().setAc(on);
}

void AirScreen::on_pushButton_4_clicked()
{
    bool on = ui->pushButton_4->isChecked();
        CarCongig::getCar().setInner(on);
}

void AirScreen::on_pushButton_5_clicked()
{
    bool on = ui->pushButton_5->isChecked();
        CarCongig::getCar().setVent(on);
}

void AirScreen::on_pushButton_6_clicked()
{
    bool on = ui->pushButton_6->isChecked();
        CarCongig::getCar().setDefrost(on);
}
void AirScreen::onAutoChanged(bool on)
{
    ui->pushButton->setIcon(QIcon(on ? ":/background/air/auto_icon_select.png"
                                     : ":/background/air/auto_icon.png"));
}

void AirScreen::onFanChanged(bool on)
{
    ui->pushButton_2->setIcon(QIcon(on ? ":/background/air/wind_btn_open.png"
                                       : ":/background/air/wind_btn_lock.png"));
}

void AirScreen::onAcChanged(bool on)
{
    ui->pushButton_3->setIcon(QIcon(on ? ":/background/air/snow_icon_select.png"
                                       : ":/background/air/snow_icon.png"));
}

void AirScreen::onInnerChanged(bool on)
{
    ui->pushButton_4->setIcon(QIcon(on ? ":/background/air/loop_open.png"
                                       : ":/background/air/loop_lock.png"));
}

void AirScreen::onVentChanged(bool on)
{
    ui->pushButton_5->setIcon(QIcon(on ? ":/background/air/windding_select.png"
                                       : ":/background/air/windding.png"));
}

void AirScreen::onDefrostChanged(bool on)
{
    ui->pushButton_6->setIcon(QIcon(on ? ":/background/air/wram_seelct.png"
                                       : ":/background/air/wram.png"));
}



void AirScreen::on_pushButton_shang_clicked()
{
    m_upOn = !m_upOn;
    ui->label_up_2->setPixmap(QPixmap(m_upOn ? ":/background/air/up_open.png"
                                           : ":/background/air/up_no.png"));
}

void AirScreen::on_pushButton_zhong_clicked()
{
    m_midOn = !m_midOn;
    ui->label_mid->setPixmap(QPixmap(m_midOn ? ":/background/air/mid_open.png"
                                             : ":/background/air/mid_no.png"));
}

void AirScreen::on_pushButton_xia_clicked()
{
    m_downOn = !m_downOn;
    ui->label_bottom->setPixmap(QPixmap(m_downOn ? ":/background/air/down_open.png"
                                                 : ":/background/air/down_no.png"));
}
