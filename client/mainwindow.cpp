#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    coreCommunicator = new CoreCommunicator(this);

    connect(coreCommunicator, &CoreCommunicator::connectionError, this, &MainWindow::connectionError);
    connect(coreCommunicator, &CoreCommunicator::newMessage, this, &MainWindow::newMessage);
    connect(coreCommunicator, &CoreCommunicator::loginSuccessful, this, &MainWindow::loginSuccessful);
    connect(coreCommunicator, &CoreCommunicator::loginFailed, this, &MainWindow::loginFailed);
    connect(coreCommunicator, &CoreCommunicator::internalServerError, this, &MainWindow::internalServerError);
    connect(coreCommunicator, &CoreCommunicator::parsingError, this, &MainWindow::parsingError);
    connect(coreCommunicator, &CoreCommunicator::okResponse, this, &MainWindow::okResponse);
    connect(coreCommunicator, &CoreCommunicator::socketNotOpen, this, &MainWindow::socketNotOpen);
    connect(coreCommunicator, &CoreCommunicator::allRooms, this, &MainWindow::allRooms);
    connect(coreCommunicator, &CoreCommunicator::roomsForUser, this, &MainWindow::roomsForUser);
    connect(coreCommunicator, &CoreCommunicator::onlineUsers, this, &MainWindow::onlineUsers);

    KeyEnterReceiver *key = new KeyEnterReceiver(parent, ui->sendPushButton);
    ui->messageTextEdit->installEventFilter(key);
}

MainWindow::~MainWindow()
{
    coreCommunicator->disconnectFromServer();
    delete ui;
}

void MainWindow::newMessage(QString username, QString room, QString timeStr, QString message)
{
    QString conversation = contextMap.value(room);
    QString messageLine = timeStr + " [" + username + "]: " + message + "\n";
    conversation += messageLine;
    contextMap.insert(room, conversation);

    if(currentRoom == room) {
        ui->conversationTextEdit->clear();
        ui->conversationTextEdit->setText(conversation);
    }
}

void MainWindow::connectionError(QString errorMessage)
{
    ui->statusbar->showMessage("Connection error: "+ errorMessage);
}

void MainWindow::loginSuccessful()
{
    ui->statusbar->showMessage("Connected!");
    coreCommunicator->fetchRoomsForUser();
}

void MainWindow::loginFailed()
{
    ui->statusbar->showMessage("Connection failed!");
}

void MainWindow::internalServerError()
{
    ui->statusbar->showMessage("Internal server error occurred.");
}

void MainWindow::parsingError()
{
    ui->statusbar->showMessage("Parsing error occurred.");
}

void MainWindow::okResponse()
{

}

void MainWindow::allRooms(QStringList rooms)
{

}

void MainWindow::roomsForUser(QStringList rooms)
{
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(rooms);

    ui->roomListView->setModel(model);

    contextMap.clear();
    for(QString room : rooms)
    {
        contextMap.insert(room, "");
    }

    if(!rooms.empty())
        currentRoom = rooms.at(0);

    coreCommunicator->fetchOnlineUsers(currentRoom);
}

void MainWindow::onlineUsers(QString room, QStringList users)
{
    if(currentRoom == room) {
        if(!ui->userListView->model()) {
            QStringListModel *model = new QStringListModel(this);
            ui->userListView->setModel(model);
        }

        QStringListModel *model = (QStringListModel*)ui->userListView->model();
        model->setStringList(users);

        qDebug() << "something";
    }
}

void MainWindow::socketNotOpen()
{

}


void MainWindow::on_actionConnect_triggered()
{
    ConnectDialog *dialog = new ConnectDialog(this, coreCommunicator);
    dialog->show();
}

void MainWindow::on_sendPushButton_clicked()
{
    sendMessage();
}

void MainWindow::sendMessage()
{
    QString message = ui->messageTextEdit->toPlainText();
    if(!message.isEmpty()) {
        coreCommunicator->sendMessage(currentRoom, message);
        ui->messageTextEdit->clear();
    }

}

void MainWindow::on_roomListView_activated(const QModelIndex &index)
{

}

void MainWindow::on_roomListView_clicked(const QModelIndex &index)
{
    const QAbstractItemModel* model = index.model();

    QVariant modelValue = model->data(index);
    QString value = modelValue.toString();

    currentRoom = value;
    ui->conversationTextEdit->setText(contextMap.value(currentRoom));

    coreCommunicator->fetchOnlineUsers(currentRoom);

}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
