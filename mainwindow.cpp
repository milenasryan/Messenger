#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _client(new Client(this))
{
    _chatDisplay = new QTextEdit;
    _chatDisplay->setReadOnly(true);

    _messageInput = new QLineEdit;

    _sendButton = new QPushButton(tr("Send"));
    connect(_sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);

    auto* layout = new QVBoxLayout;
    layout->addWidget(_chatDisplay);
    layout->addWidget(_messageInput);
    layout->addWidget(_sendButton);

    auto* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(_client, &Client::receivedMessage, this, &MainWindow::onReceivedMessage);

    _client->connectToServer("localhost", 8080);
    _client->sendUsername("YourUsername");
}

MainWindow::~MainWindow()
{}

void MainWindow::onReceivedMessage(const QString &sender, const QString &message) {
    _chatDisplay->append(sender + ": " + message);
}

void MainWindow::onSendClicked() {
    _client->sendMessage(_messageInput->text());
    _messageInput->clear();
}
