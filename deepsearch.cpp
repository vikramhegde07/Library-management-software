#include "deepsearch.h"
#include "ui_deepsearch.h"

DeepSearch::DeepSearch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeepSearch)
{
    ui->setupUi(this);
    currentIndex = 0;
    ui->titleRadio->setChecked(true);
    ui->authorRadio->setChecked(false);
    ui->publisherRadio->setChecked(false);
    searchStarted = false;
    display();
}

DeepSearch::~DeepSearch()
{
    delete ui;
}

void DeepSearch::display()
{
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    if(searchStarted){
        QString searchingElement = "%";
        searchingElement.append(ui->searchingArea->text());
        searchingElement.append("%");

        switch(currentIndex)
        {
        case 0:
            if(ui->titleRadio->isChecked())
                query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry where bookTitle like '" + searchingElement + "'");
            if(ui->authorRadio->isChecked())
                query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry where bookAuthor like '" + searchingElement + "'");
            if(ui->publisherRadio->isChecked())
                query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry where bookPublisher like '" + searchingElement + "'");
            if(ui->bookidRadio->isChecked())
                query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry where accessionNum like '" + searchingElement + "'");
            break;
        case 1:
            if(ui->titleRadio->isChecked())
                query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student where regNo like '" + searchingElement +"'");
            if(ui->authorRadio->isChecked())
                query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student where name like '" + searchingElement +"'");
            if(ui->publisherRadio->isChecked())
                query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student where course like '" + searchingElement +"'");
            break;
        case 2:
            if(ui->titleRadio->isChecked())
                query.prepare("SELECt ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo where ledger.borrowId like '" + searchingElement + "'");
            if(ui->authorRadio->isChecked())
                query.prepare("SELECt ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo where bookRegistry.accessionNum like '" + searchingElement + "'");
            if(ui->publisherRadio->isChecked())
                query.prepare("SELECt ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo where student.regNo like '" + searchingElement + "'");
            break;
        }
    }
    else{
        switch(currentIndex)
        {
        case 0:
            query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry");
            break;
        case 1:
            query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student order by regNo ASC");
            break;
        case 2:
            query.prepare("SELECt ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo order by ledger.borrowId DESC");
        }
    }

    if(query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    }
    else
        qDebug() << query.lastError();


}
void DeepSearch::on_searchingArea_textChanged(const QString &arg1)
{
    if(arg1 != "")
        searchStarted = true;
    else
        searchStarted = false;
    display();
}


void DeepSearch::on_databaseOptions_currentIndexChanged(int index)
{
    currentIndex = index;
    switch(currentIndex)
    {
    case 0:
        ui->titleRadio->setText("Book Title");
        ui->authorRadio->setText("Author");
        ui->publisherRadio->setText("Publisher");
        ui->bookidRadio->show();
        break;
    case 1:
        ui->titleRadio->setText("Register No");
        ui->authorRadio->setText("Name");
        ui->publisherRadio->setText("Course");
        ui->bookidRadio->hide();
        if(ui->bookidRadio->isChecked())
            ui->titleRadio->setChecked(true);
        break;
    case 2:
        ui->titleRadio->setText("Borrow Id");
        ui->authorRadio->setText("Book Id");
        ui->publisherRadio->setText("Student Register No");
        ui->bookidRadio->hide();
        if(ui->bookidRadio->isChecked())
            ui->titleRadio->setChecked(true);
        break;
    }
    ui->searchingArea->setText("");
    searchStarted = false;
    display();
}


void DeepSearch::on_exitBtn_clicked()
{
    DeepSearch::~DeepSearch();
}

