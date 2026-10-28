#ifndef UDPMANAGER_H
#define UDPMANAGER_H
#include<QUdpSocket>
#include<QString>
#include<QJsonDocument>
class UdpManager
{
private:
    UdpManager();
    UdpManager(const UdpManager &);
    QUdpSocket *socket;
    QString serverIP;
    quint16 serverPort;
public:
    static UdpManager &sendJson();
    void setServerInfo(QString ip,quint16 port);
    void sendUdpJsonData();
};

#endif // UDPMANAGER_H
