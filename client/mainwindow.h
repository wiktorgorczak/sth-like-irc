#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "corecommunicator.h"
#include "connectdialog.h"
#include "keyenterreceiver.h"
#include <QStringListModel>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sendMessage();

private:
    Ui::MainWindow *ui;
    CoreCommunicator *coreCommunicator;
    QString currentRoom;
    QMap<QString, QString> contextMap;
    QStringList onlineUserList;

public slots:
    void newMessage(QString username, QString room, QString timeStr, QString message);
    void connectionError(QString errorMessage);
    void loginSuccessful();
    void loginFailed();
    void internalServerError();
    void parsingError();
    void okResponse();
    void socketNotOpen();
    void allRooms(QStringList rooms);
    void roomsForUser(QStringList rooms);
    void onlineUsers(QString room, QStringList users);

private slots:
    void on_actionConnect_triggered();
    void on_sendPushButton_clicked();
    void on_roomListView_activated(const QModelIndex &index);
    void on_roomListView_clicked(const QModelIndex &index);
    void on_actionQuit_triggered();
};
#endif // MAINWINDOW_H
