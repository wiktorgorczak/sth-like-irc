#ifndef CORECOMMUNICATOR_H
#define CORECOMMUNICATOR_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QDebug>

class CoreCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit CoreCommunicator(QObject *parent = nullptr);
    void initConnection();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void connectToServer(QString hostname, qint16 port, QString login, QString password);
    void sendMessage(QString room, QString content);
    void joinRoom(QString room);
    void leaveRoom(QString room);
    void fetchAllRooms();
    void fetchRoomsForUser();
    void disconnectFromServer();
    void fetchOnlineUsers(QString room);

signals:
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

private:
    QTcpSocket *socket;
    void sendContent(QString message);
    QString username;
    QString password;
};

#endif // CORECOMMUNICATOR_H
