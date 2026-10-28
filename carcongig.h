#ifndef CARCONGIG_H
#define CARCONGIG_H

#include <QSettings>
#include<QObject>
#include<QJsonObject>
class CarCongig:public QObject
{
    Q_OBJECT
    CarCongig();
    CarCongig(const CarCongig & other);
    static CarCongig temp;

    QSettings* setting;

signals:
    void sendNewTemp(int temp);
    void sendAcChanged(bool on);
    void sendFanChanged(bool on);
    void sendInnerChanged(bool on);
    void sendVentChanged(bool on);
    void sendDefrostChanged(bool on);
    void sendAutoChanged(bool on);
public:
    static CarCongig & getCar();

    void setDoorlock(bool lock);

    bool getDoorLock()const;

    void setBoxlock(bool lock);

    bool getBoxLock()const;

    int getTemp()const;

    void setTemp(int temp);

    bool getAc() const;
    void setAc(bool on);

    bool getFan() const;
    void setFan(bool on);

    bool getInner() const;
    void setInner(bool on);

    bool getVent() const;
    void setVent(bool on);

    bool getDefrost() const;
    void setDefrost(bool on);
    bool getAuto() const;               // 新增
    void setAuto(bool on);
    QJsonObject buildJsonObject();
    void setLevel(int l);
    int getLevel()const;

};

#endif // CARCONGIG_H
