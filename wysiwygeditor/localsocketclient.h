#ifndef LOCALSOCKETCLIENT_H
#define LOCALSOCKETCLIENT_H

#include <QObject>
#include <QTimer>
#include <QtNetwork/QTcpSocket>

class LocalSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit LocalSocketClient(QObject *parent = 0);

    void send(const QString &wysiwyg);

private:
    void connectToServer();
    bool tryReadServerPort();

private slots:
    void onConnect();
    void onDisconnect();
    void onSocketError(QAbstractSocket::SocketError);
    void onData();
    void onTimeout();

Q_SIGNALS:
    void connected();

private:
    QTcpSocket localSocket;
    QTimer timer;
    quint16 serverPort;
};

#endif // LOCALSOCKETCLIENT_H
