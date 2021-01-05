#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QPushButton>

class KeyEnterReceiver : public QObject
{
    Q_OBJECT
private:
    QPushButton *button;
protected:
    bool eventFilter(QObject *obj, QEvent* event);
public:
    explicit KeyEnterReceiver(QObject *parent = nullptr, QPushButton *button = nullptr);

signals:

};

#endif // KEYENTERRECEIVER_H
