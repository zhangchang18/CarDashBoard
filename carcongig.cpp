#include "carcongig.h"
CarCongig CarCongig::temp;
CarCongig::CarCongig()
{
    setting = new QSettings("config.ini",QSettings::IniFormat);

    if(!setting->contains("/car_status/door_lock"))
    {
        setting->setValue("/car_status/door_lock",0);
    }
    if(!setting->contains("/car_status/box_lock"))
    {
        setting->setValue("/car_status/box_lock",0);
    }
    if(!setting->contains("/car_air/temp"))
    {
        setting->setValue("/car_air/temp",23);
    }
    if (!setting->contains("/car_air/ac"))
            setting->setValue("/car_air/ac", 0);
    if (!setting->contains("/car_air/fan"))
            setting->setValue("/car_air/fan", 0);
    if (!setting->contains("/car_air/inner"))
            setting->setValue("/car_air/inner", 0);
    if (!setting->contains("/car_air/vent"))
            setting->setValue("/car_air/vent", 0);
    if (!setting->contains("/car_air/defrost"))
            setting->setValue("/car_air/defrost", 0);
    if (!setting->contains("/car_air/auto"))
                setting->setValue("/car_air/auto", 0);
    if (!setting->contains("/car_air/level"))
                setting->setValue("/car_air/level", 3);
}

CarCongig::CarCongig(const CarCongig &other)
{

}

CarCongig &CarCongig::getCar()
{
        return temp;
}

void CarCongig::setDoorlock(bool lock)
{
    setting->setValue("/car_status/door_lock",lock?1:0);
}

bool CarCongig::getDoorLock()const
{
    return setting->value("/car_status/door_lock").toBool();
}

void CarCongig::setBoxlock(bool lock)
{
    setting->setValue("/car_status/box_lock",lock?1:0);
}

bool CarCongig::getBoxLock() const
{
    return setting->value("/car_status/box_lock").toBool();
}

int CarCongig::getTemp() const
{
    return setting->value("/car_air/temp").toInt();
}
void CarCongig::setLevel(int l)
{
    setting->setValue("/car_air/level",l);
}

int CarCongig::getLevel() const
{
    return setting->value("/car_air/level").toInt();
}
void CarCongig::setTemp(int temp)
{
    if(temp<16)temp=16;
    if(temp>30)temp=30;
    setting->setValue("/car_air/temp",temp);
    emit sendNewTemp(temp);
}
void CarCongig::setAc(bool on) {
    if (on == getAc()) return;
    setting->setValue("/car_air/ac", on ? 1 : 0);
    setting->sync();
    emit sendAcChanged(on);
}
void CarCongig::setFan(bool on) {
    if (on == getFan()) return;
    setting->setValue("/car_air/fan", on ? 1 : 0);
    setting->sync();
    emit sendFanChanged(on);
}
void CarCongig::setInner(bool on) {
    if (on == getInner()) return;
    setting->setValue("/car_air/inner", on ? 1 : 0);
    setting->sync();
    emit sendInnerChanged(on);
}
void CarCongig::setVent(bool on) {
    if (on == getVent()) return;
    setting->setValue("/car_air/vent", on ? 1 : 0);
    setting->sync();
    emit sendVentChanged(on);
}
void CarCongig::setDefrost(bool on) {
    if (on == getDefrost()) return;
    setting->setValue("/car_air/defrost", on ? 1 : 0);
    setting->sync();
    emit sendDefrostChanged(on);
}
void CarCongig::setAuto(bool on) {
    if (on == getAuto()) return;
    setting->setValue("/car_air/auto", on ? 1 : 0);
    setting->sync();
    emit sendAutoChanged(on);
}

QJsonObject CarCongig::buildJsonObject()
{
    QJsonObject obj;
    obj["car_doorlock"]=getDoorLock();
    obj["car_boxlock"]=getBoxLock();
    obj["temp"]=getTemp();
    obj["ac"]=getAc();
    obj["fan"]=getFan();
    obj["inner"]=getInner();
    obj["vent"]=getVent();
    obj["defrost"]=getDefrost();
    obj["auto"]=getAuto();
    obj["level"]=getLevel();
    return obj;
}
bool CarCongig::getAc() const
{
    return setting->value("/car_air/ac").toBool();
}

bool CarCongig::getFan() const
{
    return setting->value("/car_air/fan").toBool();
}

bool CarCongig::getInner() const
{
    return setting->value("/car_air/inner").toBool();
}

bool CarCongig::getVent() const
{
    return setting->value("/car_air/vent").toBool();
}

bool CarCongig::getDefrost() const
{
    return setting->value("/car_air/defrost").toBool();
}

bool CarCongig::getAuto() const
{
    return setting->value("/car_air/auto").toBool();
}

