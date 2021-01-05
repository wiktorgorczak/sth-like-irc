#include "corecommunicator.h"

CoreCommunicator::CoreCommunicator(QObject *parent) : QObject(parent), username(""), password("")
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &CoreCommunicator::connected);
    connect(socket, &QTcpSocket::disconnected, this, &CoreCommunicator::disconnected);
    connect(socket, &QTcpSocket::bytesWritten, this, &CoreCommunicator::bytesWritten);
    connect(socket, &QTcpSocket::readyRead, this, &CoreCommunicator::readyRead);
}

void CoreCommunicator::connected()
{
    qDebug() << "Successfully connected to the server.";
}

void CoreCommunicator::disconnected()
{
    qDebug() << "Disconnected from the server.";
}

void CoreCommunicator::bytesWritten(qint64 bytes)
{
    qDebug() << QString::number(bytes) + " bytes written...";
}

void CoreCommunicator::readyRead()
{
    qDebug() << "incoming message...";

    QString rawMessage = socket->readAll();
    qDebug() << "raw message: " << rawMessage;

    if(rawMessage == "[srv]:authorized;") {
        emit loginSuccessful();
    } else if(rawMessage == "[srv]:unauthorized;") {
        emit loginFailed();
        socket->disconnect();
    } else if(rawMessage == "[srv]:parsing_error;") {
        emit parsingError();
    } else if(rawMessage == "[srv]:internal_error;") {
        emit internalServerError();
    } else if(rawMessage == "[srv]:ok;") {
        emit okResponse();
    } else if(rawMessage.startsWith("[srv]:ok;all_rooms")) {
        QStringList rooms = rawMessage.split(";");

        if(rooms.length() < 3)
            emit internalServerError();
        else {
            rooms.removeFirst();
            rooms.removeFirst();

            emit allRooms(rooms);
        }

    } else if(rawMessage.startsWith("[srv]:ok;user_rooms")) {
        QStringList rooms = rawMessage.split(";");

        if(rooms.length() < 3) {
            emit internalServerError();
        } else {
            rooms.removeFirst();
            rooms.removeFirst();

            emit roomsForUser(rooms);
        }


    } else if(rawMessage.startsWith("[srv]:ok;online_users")) {
        QStringList users = rawMessage.split(";");

        if(users.length() < 4)
            emit internalServerError();
        else {
            users.removeFirst();
            users.removeFirst();
            QString room = users.at(0);
            users.removeFirst();

            emit onlineUsers(room, users);
        }

    } else {
        QStringList tokens = rawMessage.split(";");
        if(tokens.length() < 4)
            emit parsingError();

        QString username = tokens.at(0);
        QString room = tokens.at(1);
        QString timeStr = tokens.at(2);
        QString content = tokens.at(3);

        emit newMessage(username, room, timeStr, content);
    }
}

void CoreCommunicator::connectToServer(QString hostname, qint16 port, QString login, QString password)
{
    socket->connectToHost(hostname, port);

    if(!socket->waitForConnected(1000))
    {
        emit connectionError(socket->errorString());
    } else {
        QString message = login + ";" + password + ";general;login;login";

        socket->write(message.toUtf8());
    }

    this->username = login;
    this->password = password;
}

void CoreCommunicator::sendMessage(QString room, QString content)
{
    QString message = username + ";" + password + ";" + room + ";standard;" + content;
    sendContent(message);
}

void CoreCommunicator::joinRoom(QString room)
{
    QString message = username + ";" + password + ";" + room + ";join_room;join_room";
    sendContent(message);
}

void CoreCommunicator::leaveRoom(QString room)
{
    QString message = username + ";" + password + ";" + room + ";leave_room;leave_room";
    sendContent(message);
}

void CoreCommunicator::fetchAllRooms()
{
    QString message = username + ";" + password + ";general;get_rooms;get_rooms";
    sendContent(message);
}


void CoreCommunicator::fetchRoomsForUser()
{
    QString message = username + ";" + password + ";general;get_rooms_for_user;get_rooms_for_user";
    sendContent(message);
}

void CoreCommunicator::fetchOnlineUsers(QString room)
{
    QString message = username + ";" + password + ";" + room + ";get_online_users;get_online_users";
    sendContent(message);
}

void CoreCommunicator::disconnectFromServer()
{
    QString message = username + ";" + password + ";" + "general" + ";logoff;logoff";
    sendContent(message);
    socket->disconnect();
}

void CoreCommunicator::sendContent(QString message)
{
    if(!socket->isOpen()) {
        emit socketNotOpen();
    } else {
        socket->write(message.toUtf8());
    }
}
