#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void onSendClicked();
    void onReceivedMessage(const QString &sender, const QString &message);

private:
    Client* _client;
    QTextEdit* _chatDisplay;
    QLineEdit* _messageInput;
    QPushButton* _sendButton;
};
#endif // MAINWINDOW_H
