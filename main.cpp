#include <QApplication>
#include "mainwindow.h"
#include <QThread>
#include "worker.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    QThread* thread = new QThread();
    Worker* worker = new Worker("127.0.0.1", 8080, "User1");
    worker->moveToThread(thread);

    QObject::connect(thread, &QThread::started, worker, &Worker::process);
    QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
    QObject::connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

    return app.exec();
}
