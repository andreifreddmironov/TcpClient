#include <QCoreApplication>
#include <tcpclient.h>
#include <client.h>
#include <QSettings>
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings("TcpClient.ini", QSettings::IniFormat);

    settings.beginGroup("Settings");
    QString ip = settings.value("ServerIP", "127.0.0.1").toString();
    int port = settings.value("ServerPort", 6060).toInt();
    double value = settings.value("ServerValue", 1.2).toDouble();
    if(port == 6060)
    {
        settings.setValue("ServerPort", 6060);
    }
    if(ip == "127.0.0.1")
    {
        settings.setValue("ServerIP", "127.0.0.1");
    }
    if(value == 1.2)
    {
        settings.setValue("ServerValue", 1.2);
    }
    settings.endGroup();

    //TcpClient client(NULL, ip, port, value);
    Client client(NULL, ip, port, value);

    return a.exec();
}
