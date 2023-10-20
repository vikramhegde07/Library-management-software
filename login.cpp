#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    this->setWindowState(Qt::WindowNoState);
    delete ui;
}

void Login::on_exitBtn_clicked()
{
    this->setWindowState(Qt::WindowNoState);
    this->close();
}


void Login::on_loginBtn_clicked()
{
    QString userName = ui->userName->text();
    QString passwd = ui->Passwd->text();

    if(userName.toStdString() == "admin" && passwd.toStdString() == "admin123"){
        this->setWindowState(Qt::WindowActive);
        this->close();
    }
    else{
        QMessageBox::critical(this,"Error","Username or Password is incorrect");
    }
}
