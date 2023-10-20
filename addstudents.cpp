#include "addstudents.h"
#include "ui_addstudents.h"

addStudents::addStudents(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addStudents)
{
    ui->setupUi(this);
}

addStudents::~addStudents()
{
    delete ui;
}

void addStudents::on_exitBtn_clicked()
{
    addStudents::~addStudents();
}


void addStudents::on_clearBtn_clicked()
{
    ui->name->setText("");
    ui->regNo->setText("");
}


void addStudents::on_addBtn_clicked()
{
    QString name = ui->name->text();
    QString regNo = ui->regNo->text();
    QString course = ui->course->currentText();

    regNo = regNo.toUpper();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    query.prepare("insert into student values('" + regNo + "','" + name + "','" + course + "')");
    if(query.exec()){
        QMessageBox::information(this,"Success","Information added to database successfully");
    }
    else{
        QMessageBox::critical(this,"Failed", "Error while adding information");
    }

}

