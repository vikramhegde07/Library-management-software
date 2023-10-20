#include "history.h"
#include "ui_history.h"

history::history(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    display();
}

history::~history()
{
    delete ui;
}

void history::display()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel * model = new QSqlQueryModel(this);

    query.prepare("select ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo order by ledger.borrowId DESC");

    if(query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->columnWidth(20);
    }
    else
    {
        qDebug() << query.lastError();
    }
}

void history::on_refreshBtn_clicked()
{
    display();
}


void history::on_backBtn_clicked()
{
    history::~history();
}


void history::on_tableView_doubleClicked(const QModelIndex &index)
{
    detailsWindow = new Details(this);
    detailsWindow->show();
    detailsWindow->AcceptData(index.siblingAtColumn(0).data().toString(), 2);
}

