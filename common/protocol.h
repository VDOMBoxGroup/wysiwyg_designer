#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>
#include <QtNetwork/QAbstractSocket>

#define LOCAL_SOCKET_ENV_VAR "local_socket_port"

bool CanReadMessage(QAbstractSocket *s);
void ReadMessage(QAbstractSocket *s, QString &wysiwyg);
void WriteMessage(QAbstractSocket *s, const QString &wysiwyg);

void WriteSocketEnvVar(const QString &value);
QString ReadSocketEnvVar();

#endif // PROTOCOL_H
