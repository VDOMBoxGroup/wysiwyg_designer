#include "localsocketclient.h"
#include "protocol.h"
#include <QtNetwork/QHostAddress>

LocalSocketClient::LocalSocketClient(QObject *parent) : QObject(parent), serverPort(0)
{
    connect(&localSocket, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(&localSocket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(&localSocket, SIGNAL(readyRead()), this, SLOT(onData()));
    connect(&localSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer.setInterval(500);
    timer.setSingleShot(true);
    timer.start();
}

void LocalSocketClient::send(const QString &wysiwyg)
{
    WriteMessage(&localSocket, wysiwyg);
}

bool LocalSocketClient::tryReadServerPort()
{
    QString s = ReadSocketEnvVar();
    serverPort = s.toInt();
    //qDebug("Client: server port (%d)", serverPort);
    return (serverPort != 0);
}

void LocalSocketClient::connectToServer()
{
    qDebug("Client: connect");
    localSocket.connectToHost(QHostAddress::LocalHost, serverPort, QIODevice::ReadWrite);
}

void LocalSocketClient::onConnect()
{
    qDebug("Client: connected");
    emit connected();
}

void LocalSocketClient::onDisconnect()
{
    qDebug("Client: disconnected");
    connectToServer();
}

void LocalSocketClient::onData()
{
    //qDebug("Client: data");
}

void LocalSocketClient::onSocketError(QAbstractSocket::SocketError e)
{
    qDebug("Client: error (%d)", (int)e);
}

void LocalSocketClient::onTimeout()
{
    if (!tryReadServerPort()) {
        qDebug("Client: timeout");
        timer.start();
    } else {
        connectToServer();
    }
}
