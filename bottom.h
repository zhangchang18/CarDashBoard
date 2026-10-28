#ifndef BOTTOM_H
#define BOTTOM_H

#include <QWidget>

namespace Ui {
class Bottom;
}

class Bottom : public QWidget
{
    Q_OBJECT

public:
    explicit Bottom(QWidget *parent = nullptr);
    ~Bottom();
signals:
    void changeToHome();
    void changeToSetting();
    void changeToAir();
private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_setting_clicked();


    void on_pushButton_air_clicked();



    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

private:
    Ui::Bottom *ui;
};

#endif // BOTTOM_H
