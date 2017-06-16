#include "protocol.h"

quint32 PeekMessageSize(QAbstractSocket *s)
{
    quint32 l = 0;
    s->peek((char*)&l, sizeof(l));
    return l;
}

bool CanReadMessage(QAbstractSocket *s)
{
    quint64 n = s->bytesAvailable();
    if (n >= sizeof(quint32)) {
        quint32 len = PeekMessageSize(s);
        if (n >= len + sizeof(len))
            return true;
    }
    return false;
}

void ReadMessage(QAbstractSocket *s, QString &wysiwyg)
{
    quint32 len = PeekMessageSize(s);
    QByteArray data = s->read(len + sizeof(len));
    wysiwyg = data.mid(sizeof(len));
}

void WriteMessage(QAbstractSocket *s, const QString &wysiwyg)
{
    QByteArray data;
    quint32 msgSize = wysiwyg.size();
    data.reserve(sizeof(quint32) + msgSize);

    QByteArray w = wysiwyg.toLatin1();

    data.append((const char*)&msgSize, sizeof(msgSize));
    data.append(w.constData(), w.size());

    s->write(data);
}

void WriteSocketEnvVar(const QString &value)
{
    qputenv(LOCAL_SOCKET_ENV_VAR, value.toLatin1());
}

QString ReadSocketEnvVar()
{
    return QString(qgetenv(LOCAL_SOCKET_ENV_VAR));
}
