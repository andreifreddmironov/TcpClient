#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTimer>
#include <qdebug.h>
#include <QtNetwork>

#define START_PREFIX 0x0A

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent, QString ip, int port, double value);
    ~TcpClient();

private:
    QTimer *m_timer;
    QTcpSocket *m_tcpSocket;
    QByteArray m_buffer;    
    QVector<double> m_vector;

    QString m_ip;
    int m_port;
    double m_value;

    int randomInt(int low, int high, int seed);

signals:
    void finished();

public slots:
    void Init();
    void Start();
    void ReadyRead();
    void Connected();
};

#endif // TCPCLIENT_H
