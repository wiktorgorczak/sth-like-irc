#include "keyenterreceiver.h"

bool KeyEnterReceiver::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::KeyPress) {
           QKeyEvent* key = static_cast<QKeyEvent*>(event);
           if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                button->click();
           } else {
               return QObject::eventFilter(obj, event);
           }
           return true;
       } else {
           return QObject::eventFilter(obj, event);
       }
       return false;
}

KeyEnterReceiver::KeyEnterReceiver(QObject *parent, QPushButton *button_) : QObject(parent), button(button_)
{

}
