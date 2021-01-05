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
    void sendMessage(QString username, QString password, QString room, QString content);
    void joinRoom(QString username, QString password, QString room);
    void leaveRoom(QString username, QString password, QString room);
    void fetchAllRooms(QString username, QString password);
    void fetchRoomsForUser(QString username, QString password);
    void disconnectFromServer(QString username, QString password);

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

private:
    QTcpSocket *socket;
    void sendContent(QString message);
};

#endif // CORECOMMUNICATOR_H
