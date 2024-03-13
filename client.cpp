#include "client.h"


Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QString &host, quint16 port) {
    socket->connectToHost(host, port);
}

void Client::sendUsername(const QString &username) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(username.toUtf8());
    }
}

void Client::sendMessage(const QString &message) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(message.toUtf8());
    }
}

void Client::onReadyRead() {
    QByteArray data = socket->readAll();
    QString sender;
    QString message(data);
    emit receivedMessage(sender, message);
}
