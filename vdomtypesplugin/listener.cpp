#include "listener.h"
#include "protocol.h"
#include <QString>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

Listener::Listener() : QObject()
{
    connect(&server, SIGNAL(newConnection()), this, SLOT(onConnect()));
    if (server.listen(QHostAddress::LocalHost))
        qDebug("Server created (%d)", server.serverPort());
    else
        qDebug("Failed to create server");
    WriteSocketEnvVar(QString::number(server.serverPort()));
}

void Listener::onConnect()
{
    qDebug("Server: connected");
    QTcpSocket *client = server.nextPendingConnection();
    if (client) {
        clients.append(client);
        connect(client, SIGNAL(readyRead()), this, SLOT(onData()));
        connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
        connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    }
}

void Listener::onDisconnect()
{
    qDebug("Server: disconnected");
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    clients.removeAll(client);
    client->close();
    client->deleteLater();
}

void Listener::onData()
{
    //qDebug("Server: data");
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    while (CanReadMessage(client)) {
        QString wysiwyg;
        ReadMessage(client, wysiwyg);
        //qDebug("Server: emit");
        emit receivedWysiwyg(wysiwyg);
        //qDebug("Server: emit done");
    }
    //qDebug("Server: data end");
}

void Listener::onError(QAbstractSocket::SocketError e)
{
    qDebug("Server: error (%d)", (int)e);
}
