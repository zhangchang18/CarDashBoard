#include "homescreen.h"
#include "ui_homescreen.h"
#include<QDateTime>
#include<qmediametadata.h>
#include<QMediaPlayer>
#include"udpmanager.h"
HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    label=new MyLabel(this);
    setAttribute(Qt::WA_StyledBackground);
    connect(ui->pushButton_car,&QPushButton::clicked,this,&HomeScreen::changeToIcon);
    time=new QTimer(this);
    connect(time,&QTimer::timeout,this,&HomeScreen::changeTimeLabel);
    time->start(1);
    player=new QMediaPlayer(this);
    paths.push_back("D:/QQ/music/music/A1 TRIP _ 大籽 _ Lil E - 放空.mp3");
    paths.push_back("D:/QQ/music/music/Eric周兴哲 - 永不失联的爱.mp3");
    paths.push_back("D:/QQ/music/music/金志文 - 自娱自乐.mp3");
//    player->setMedia(QUrl::fromLocalFile("D:/QQ/music/music/Eric周兴哲 - 永不失联的爱.mp3"));
    player->setMedia(QUrl::fromLocalFile(paths.at(1)));
    connect(player, &QMediaPlayer::mediaStatusChanged,this,&HomeScreen::mediaStatusChanged);
    if(CarCongig::getCar().getDoorLock()){
        ui->pushButton_clock->setIcon(QIcon(":/background/main/suo.png"));
    }
    if(CarCongig::getCar().getBoxLock()){
        ui->pushButton_door->setIcon(QIcon(":/background/main/box_lock.png"));
    }
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::setBackgroundImg(QString path)
{
     QString qss = QString("#home{border-image: url(%1);}").arg(path);
     this->setStyleSheet(qss);
}

void HomeScreen::changeTimeLabel()
{
    QDateTime datetime= QDateTime::currentDateTime();
    QString t= datetime.toString("HH:mm:ss");
    QString y=datetime.toString("MM/dd ddd");
    ui->label_time->setText(t+'\n'+y);
}

void HomeScreen::on_pushButton_start_clicked()
{
    if(player->state()==QMediaPlayer::PlayingState){
        player->pause();
        ui->pushButton_start->setIcon(QIcon(":/background/main/play.png"));
    }else if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState){
        player->play();
        ui->pushButton_start->setIcon(QIcon(":/background/main/pause.png"));
    }
    getMusicMessage();
}

void HomeScreen::on_pushButton_pre_clicked()
{
    if (currentIndex <= 0)
        currentIndex = paths.size() - 1;
    else
        currentIndex--;

    // player 加载资源
    player->setMedia(QUrl::fromLocalFile(paths.at(currentIndex)));
    player->play();
    ui->pushButton_start->setIcon(QIcon(":/background/main/pause.png"));
    // 刷新歌曲信息显示
    getMusicMessage();
}

void HomeScreen::on_pushButton_next_clicked()
{
    if (paths.isEmpty())
        return;

    // 更改播放的索引位置  注意：最后一首时，切换到第一首
    if (currentIndex >= paths.size() - 1)
        currentIndex = 0;
    else
        currentIndex++;

    // player 加载资源
    player->setMedia(QUrl::fromLocalFile(paths.at(currentIndex)));
    player->play();
    ui->pushButton_start->setIcon(QIcon(":/background/main/pause.png"));
    // 刷新歌曲信息显示（如果已连 metaDataChanged，这句可省略）
    getMusicMessage();
}

void HomeScreen::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::LoadedMedia||status==QMediaPlayer::BufferedMedia){
        getMusicMessage();
    }
}

void HomeScreen::getMusicMessage()
{
    QVariant title = player->metaData(QMediaMetaData::Title);//标题

    ui->label_name->setText(title.toString());
    // 先试封面，再试缩略图
    QVariant v = player->metaData(QMediaMetaData::CoverArtImage);//封面
    if (!v.isValid())
    {
        v = player->metaData(QMediaMetaData::ThumbnailImage);//缩略图
    }
    if (v.canConvert<QImage>())
    {
        QImage img = v.value<QImage>();
        if (!img.isNull())
        {
            ui->label_image ->setPixmap(QPixmap::fromImage(img).scaled(
            ui->label_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}


void HomeScreen::on_pushButton_clock_clicked()
{
    bool currentLock = CarCongig::getCar().getDoorLock();

       bool newLock = (currentLock == 1) ? 0 : 1;

        CarCongig::getCar().setDoorlock(newLock);
        if(newLock)
        {
            ui->pushButton_clock->setIcon(QIcon(":/background/main/suo.png"));
            label->toastLable("四门已关锁");
        }
        else
        {
            ui->pushButton_clock->setIcon(QIcon(":/background/main/unlock.png"));
            label->toastLable("四门已解锁");
        }
        UdpManager::sendJson().sendUdpJsonData();
}

void HomeScreen::on_pushButton_door_clicked()
{
    bool currentLock = CarCongig::getCar().getBoxLock();

       bool newLock = (currentLock == 1) ? 0 : 1;

        CarCongig::getCar().setBoxlock(newLock);
        if(newLock)
        {
            ui->pushButton_door->setIcon(QIcon(":/background/main/box_lock.png"));
            label->toastLable("后备箱已关闭");
        }
        else
        {
            ui->pushButton_door->setIcon(QIcon(":/background/main/box_open.png"));
            label->toastLable("后备箱已打开");
        }
}

void HomeScreen::on_pushButton_daohang_clicked()
{
    emit changeToMap();
}
