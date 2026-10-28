#include "udpmanager.h"
#include"carcongig.h"
UdpManager::UdpManager()
{
    socket=new QUdpSocket();
}

UdpManager::UdpManager(const UdpManager &)
{

}

UdpManager &UdpManager::sendJson()
{
    static UdpManager Json;
    return Json;
}

void UdpManager::setServerInfo(QString ip, quint16 port)
{
    this->serverIP=ip;
    this->serverPort=port;
}

void UdpManager::sendUdpJsonData()
{
    QJsonObject obj = CarCongig::getCar().buildJsonObject();
    QJsonDocument doc(obj);
    QByteArray arr= doc.toJson(QJsonDocument::Compact);
    socket->writeDatagram(arr,QHostAddress(serverIP),serverPort);
    qDebug()<<"udp发给服务器端的json字符串："<<arr;
}
