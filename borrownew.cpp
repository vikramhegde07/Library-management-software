#include "borrownew.h"
#include "ui_borrownew.h"
#include <QDate>

borrowNew::borrowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::borrowNew)
{
    ui->setupUi(this);
    ui->BorrowDate->setDate(QDate::currentDate());
    ui->BorrowDate->setDisabled(true);
    ui->ReturnDate->setDate(QDate::currentDate().addDays(7));
    borrowId = "0";
}

borrowNew::~borrowNew()
{
    delete ui;
}

void borrowNew::on_Exit_clicked()
{
    this->close();
}


void borrowNew::on_bookIdSearch_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString bookid = ui->BookId->text();

    query.prepare("select bookTitle from bookRegistry where accessionNum == '" + bookid + "'");
    QString title;
    if(query.exec())
        while(query.next())
            title = query.value(0).toString();
    ui->BookTitle->setText(title);
}


void borrowNew::on_StudentIdSearch_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString student = ui->StudentId->text();

    student = student.toUpper();

    query.prepare("select name from student where regNo == '" + student + "'");
    QString name;
    if(query.exec())
        while(query.next())
            name = query.value(0).toString();
    ui->StudentName->setText(name);
}


void borrowNew::on_AddToRecord_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString bookid = ui->BookId->text();
    QString regno = ui->StudentId->text();
    QString borrowingDate = ui->BorrowDate->text();
    QString returningDate = ui->ReturnDate->text();

    regno = regno.toUpper();

   if(bookid != "" && regno != ""){
       query.prepare("select borrowId from ledger");
       if(query.exec()){
           while(query.next())
               borrowId = query.value(0).toString();
           int i = borrowId.toInt();
           i++;
           borrowId = QString::number(i);
       }
       query.prepare("Select * from student where regNo = '"+ regno +"'");
       if(query.exec())
           model->setQuery(query);
       if(model->rowCount() == 1){
           query.prepare("insert into ledger values( '" + borrowId + "','" + bookid + "','" + regno + "','" + borrowingDate + "','" + returningDate + "','')");

           if(query.exec()){
               QMessageBox::information(this,"Successfull","Successfully registered");
           }
           else{
               QMessageBox::critical(this,"Failed","Error while registering");
               qDebug() << query.lastError();
           }
       }
       else{
           QMessageBox::critical(this,"Failed","Error in student register number");
           qDebug() << query.lastError();
       }


   }
   else{
       QMessageBox::warning(this,"Warning","Please enter student and book information");
   }
}
