#include "worker.h"

Worker::Worker(const QString& serverAddress, quint16 port, const QString& username, QObject *parent)
    : QObject(parent), serverAddress(serverAddress), port(port), username(username) {
    client = new Client(this);
}

Worker::~Worker() {
    client->disconnect();
}

void Worker::process() {
    connect(client, &Client::receivedMessage, this, [](const QString &sender, const QString &message) {
        qDebug() << sender << ": " << message;
    });

    client->connectToServer(serverAddress, port);
    QThread::sleep(1);
    client->sendUsername(username);

    emit finished();
}
