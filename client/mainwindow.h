#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "corecommunicator.h"
#include "connectdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CoreCommunicator *coreCommunicator;
    QString currentRoom;

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

private slots:
    void on_actionConnect_triggered();
};
#endif // MAINWINDOW_H
