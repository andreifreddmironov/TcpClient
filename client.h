#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <tcpclient.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent, QString ip, int port, double value);
    ~Client();

private:
    QString m_ip;
    int m_port;
    double m_value;

signals:

public slots:
};

#endif // CLIENT_H
