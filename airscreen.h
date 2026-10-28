#ifndef AIRSCREEN_H
#define AIRSCREEN_H

#include <QWidget>
#include"mylabel.h"
namespace Ui {
class AirScreen;
}

class AirScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AirScreen(QWidget *parent = nullptr);
    ~AirScreen();

private slots:


    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();
    void showTemp(int temp);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
    void onAutoChanged(bool on);
    void onFanChanged(bool on);
    void onAcChanged(bool on);
    void onInnerChanged(bool on);
    void onVentChanged(bool on);
    void onDefrostChanged(bool on);


    void on_pushButton_xia_clicked();

    void on_pushButton_zhong_clicked();

    void on_pushButton_shang_clicked();

private:
    bool m_upOn = false;    // 扇形，上面那条风
        bool m_midOn = false;   // 中间吹身体
        bool m_downOn = false;  // 下面吹脚
private:
    Ui::AirScreen *ui;
    MyLabel *label;
};

#endif // AIRSCREEN_H
