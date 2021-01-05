#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent, CoreCommunicator *coreCommunicator_) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),
    coreCommunicator(coreCommunicator_)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_buttonBox_clicked(QAbstractButton *button)
{

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString hostname = ui->hostnameLineEdit->text();
    QString portStr = ui->portLineEdit->text();

    qint16 port = portStr.toInt();

    coreCommunicator->connectToServer(hostname, port, username, password);
}
