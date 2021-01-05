#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "corecommunicator.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr, CoreCommunicator *coreCommunicator_ = nullptr);
    ~ConnectDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ConnectDialog *ui;
    CoreCommunicator *coreCommunicator;
};

#endif // CONNECTDIALOG_H
