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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newMessage(QString username, QString room, QString timeStr, QString message)
{

}

void MainWindow::connectionError(QString errorMessage)
{

}

void MainWindow::loginSuccessful()
{

}

void MainWindow::loginFailed()
{

}

void MainWindow::internalServerError()
{

}

void MainWindow::parsingError()
{

}

void MainWindow::okResponse()
{

}

void MainWindow::allRooms(QStringList rooms)
{

}

void MainWindow::roomsForUser(QStringList rooms)
{

}

void MainWindow::socketNotOpen()
{

}


void MainWindow::on_actionConnect_triggered()
{
    ConnectDialog *dialog = new ConnectDialog(this, coreCommunicator);
    dialog->show();
}
