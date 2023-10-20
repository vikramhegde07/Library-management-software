#include "browse.h"
#include "ui_browse.h"

Browse::Browse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Browse)
{
    ui->setupUi(this);
    searchStarted = false;
    display();
}

Browse::~Browse()
{
    delete ui;
}

void Browse::display()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString searchingElement;
    searchingElement.append("%");
    searchingElement.append(ui->searchingElement->text());
    searchingElement.append("%");

    if(searchStarted)
        query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry where bookTitle like '" + searchingElement + "'");
    else
        query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry");
    if(query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    }
    else
        qDebug() << query.lastError();
}

void Browse::on_exitBtn_clicked()
{
    Browse::~Browse();
}


void Browse::on_refresh_clicked()
{
    display();
}


void Browse::on_addNew_clicked()
{
    adBooks = new addbooks(this);
    adBooks->show();
}

void Browse::on_searchingElement_textChanged(const QString &arg1)
{
    searchStarted = true;
    display();
}

void Browse::on_tableView_doubleClicked(const QModelIndex &index)
{
    detailsWindow = new Details(this);
    detailsWindow->show();
    detailsWindow->AcceptData(index.siblingAtColumn(0).data().toString(), 1);

}
