#include "client.h"

Client::Client(QObject *parent, QString ip, int port, double value) : QObject(parent),
    m_ip(ip),
    m_port(port),
    m_value(value)
{
    TcpClient *tcpClient1 = new TcpClient(NULL, ip, port, value);
    TcpClient *tcpClient2 = new TcpClient(NULL, ip, port, value+1);
    TcpClient *tcpClient3 = new TcpClient(NULL, ip, port, value+2);
    QThread *thread1 = new QThread;
    QThread *thread2 = new QThread;
    QThread *thread3 = new QThread;

    tcpClient1->moveToThread(thread1);
    connect(tcpClient1, SIGNAL(finished()), tcpClient1, SLOT(deleteLater()));
    connect(thread1, SIGNAL(started()), tcpClient1, SLOT(Init()));
    connect(tcpClient1, SIGNAL(finished()), thread1, SLOT(quit()));

    tcpClient2->moveToThread(thread2);
    connect(tcpClient2, SIGNAL(finished()), tcpClient2, SLOT(deleteLater()));
    connect(thread2, SIGNAL(started()), tcpClient2, SLOT(Init()));
    connect(tcpClient2, SIGNAL(finished()), thread2, SLOT(quit()));

    tcpClient3->moveToThread(thread3);
    connect(tcpClient3, SIGNAL(finished()), tcpClient3, SLOT(deleteLater()));
    connect(thread3, SIGNAL(started()), tcpClient3, SLOT(Init()));
    connect(tcpClient3, SIGNAL(finished()), thread3, SLOT(quit()));


    thread1->start();
    thread2->start();
    thread3->start();
}

Client::~Client()
{

}

