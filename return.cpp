#include "return.h"
#include "ui_return.h"

Return::Return(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Return)
{
    ui->setupUi(this);
    display();
    ui->returnDate->setDate(QDate::currentDate());
    ui->returnDate->setDisabled(true);
    searchBtn = false;
}

Return::~Return()
{
    delete ui;
}

void Return::on_exitBtn_clicked()
{
    Return::~Return();
}

void Return::display()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString bookSearch = ui->bookSearch->text();

    if(!searchBtn)
        query.prepare("SELECT ledger.borrowId as 'Borrow ID', ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as 'Book Title', ledger.regNo as 'Register No',student.name as 'Student Name', ledger.issueDate as 'Issue Date',ledger.dueDate as 'Due Date',ledger.returnDate as 'Return Date' from ledger join student on student.regNo = ledger.regNo join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum where returnDate = '' order by issueDate DESC");
    else
        query.prepare("SELECT ledger.borrowId as 'Borrow ID', ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as 'Book Title', ledger.regNo as 'Register No',student.name as 'Student Name', ledger.issueDate as 'Issue Date',ledger.dueDate as 'Due Date',ledger.returnDate as 'Return Date' from ledger join student on student.regNo = ledger.regNo join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum where borrowId = '" + bookSearch + "'");

    if(query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    }
    else
        qDebug() << query.lastError();
}


void Return::on_refresh_clicked()
{
    searchBtn = false;
    display();
}


void Return::on_searchBtn_clicked()
{
    searchBtn = true;
    display();
}


void Return::on_confirmBtn_clicked()
{
    QString bookSearch = ui->bookSearch->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    query.prepare("select * from ledger where borrowId = '" + bookSearch + "' and returnDate = ''");
    if(query.exec())
    {
        model->setQuery(query);
        if(model->rowCount() == 1)
        {
            QMessageBox::information(this,"Success","Book Return Successfully");
            query.prepare(" UPDATE ledger set returnDate = '"+ ui->returnDate->text() +"' where borrowId = '"+ bookSearch +"'");
            query.exec();
            display();
        }
        else
        {
            QMessageBox::warning(this,"Failed","Error while returning : \nBook is not registered or already returned");
        }
    }
}


void Return::on_tableView_doubleClicked(const QModelIndex &index)
{
    detailWindow = new Details(this);
    detailWindow->show();
    detailWindow->AcceptData(index.siblingAtColumn(0).data().toString(), 2);
}

