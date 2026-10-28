#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include"carcongig.h"
#include <QWidget>
#include<QTimer>
#include<QMediaPlayer>
#include<QList>
#include<QLabel>
#include"mylabel.h"
namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

    void setBackgroundImg(QString path);
signals:
    void changeToTheme();
    void changeToIcon();
    void changeToMap();
private slots:
    void changeTimeLabel();
    void on_pushButton_start_clicked();

    void on_pushButton_pre_clicked();

    void on_pushButton_next_clicked();

    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_pushButton_clock_clicked();

    void on_pushButton_door_clicked();

    void on_pushButton_daohang_clicked();

private:
    void getMusicMessage();
private:
    Ui::HomeScreen *ui;
    QTimer *time;
    QMediaPlayer *player;
    QList<QString> paths;
    int count=0;
    int currentIndex=1;
    MyLabel *label;
};

#endif // HOMESCREEN_H
