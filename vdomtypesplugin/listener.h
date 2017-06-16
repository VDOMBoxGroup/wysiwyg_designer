#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QList>
#include <QtNetwork/QTcpServer>

class QTcpSocket;

class Listener: public QObject
{
    Q_OBJECT

public:
    Listener();

private slots:
    void onConnect();
    void onData();
    void onDisconnect();
    void onError(QAbstractSocket::SocketError);

Q_SIGNALS:
    void receivedWysiwyg(const QString &wysiwyg);

private:
    QTcpServer server;
    QList<QTcpSocket*> clients;
};

#endif // LISTENER_H
