#include "tcpclient.h"
#include "QCoreApplication"

TcpClient::TcpClient(QObject *parent, QString ip, int port, double value) : QObject(parent),
    m_ip(ip),
    m_port(port),
    m_value(value)
{
}

TcpClient::~TcpClient()
{
    delete m_timer;
    m_timer = NULL;
    delete m_tcpSocket;
    m_tcpSocket = NULL;
    qDebug() << "TcpClient::~TcpClient";
}

void TcpClient::Init()
{
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->connectToHost( m_ip, m_port);
    connect(m_tcpSocket, SIGNAL(connected()), SLOT(Connected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), SLOT(ReadyRead()));
}

void TcpClient::Start()
{
    qDebug() << "TcpClient::start" << m_value;
    QByteArray pack;
    pack.append(START_PREFIX);
    pack.append(START_PREFIX);
    pack.append(START_PREFIX);
    pack.append(START_PREFIX);
    int len = 8;
    pack.append(QByteArray(reinterpret_cast<const char*>(&len), sizeof(len)));
    pack.append(QByteArray(reinterpret_cast<const char*>(&m_value), sizeof(m_value)));

    m_tcpSocket->write(pack);
    m_timer->stop();
}

void TcpClient::ReadyRead()
{
    m_buffer += m_tcpSocket->readAll();

    if((m_buffer.at(0) == START_PREFIX) &&
       (m_buffer.at(1) == START_PREFIX) &&
       (m_buffer.at(2) == START_PREFIX) &&
       (m_buffer.at(3) == START_PREFIX))
    {
        QByteArray lenArr = m_buffer.mid(4,4);
        const quint32 *inLen = reinterpret_cast<const quint32*>(lenArr.data());

        if(m_buffer.length() == *inLen + 8)
        {
            m_buffer.remove(0,8);
            //QDataStream stream(m_buffer);
            //stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
            //stream.setVersion(QDataStream::Qt_5_4);
            //stream >> m_vector;
            //qDebug() << m_vector;

            QString time = QTime::currentTime().toString();
            time.remove(':');
            time += "_" + QString::number(m_value) + "_";
            QString fileName = "C:\\TcpClient_" + time + ".txt";
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly))// | QIODevice::Text))
            {
                qDebug() << "File not open";
                return;
            }

            file.write(m_buffer.data(),m_buffer.length());
            file.close();
            qDebug() << "File saved";
            m_buffer.clear();
            this->deleteLater();
            emit finished();
        }
    }
}

void TcpClient::Connected()
{
    qDebug() << "Connected";

    m_timer = new QTimer();
    m_timer->setInterval(3000);
    connect(m_timer,SIGNAL(timeout()), this, SLOT(Start()));
    m_timer->start();
}

int TcpClient::randomInt(int low, int high, int seed)
{
    qsrand(seed);
    return (qrand() % ((high + 1) - low) + low);
}

