#include "deleterecords.h"
#include "ui_deleterecords.h"

deleteRecords::deleteRecords(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::deleteRecords)
{
    ui->setupUi(this);
    i = 0;
    searchStarted = false;
    display();
}

deleteRecords::~deleteRecords()
{
    delete ui;
}

void deleteRecords::on_comboBox_currentIndexChanged(int index)
{
    i = index;
    display();
}

void deleteRecords::display()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    if(searchStarted){
        QString referenceid = ui->referenceID->text();
        referenceid.append("%");
        if(i == 0){
            query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry where accessionNum like '" + referenceid + "'");
        }
        else if(i == 1){
            query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student order by regNo ASC where regNo like '" + referenceid + "'");
        }
        else{
            query.prepare("select ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo order by ledger.borrowId DESC where ledger.borrowId like '" + referenceid + "'");
        }
    }else{
        if(i == 0){
            query.prepare("SELECT accessionNum as 'Book Accession No', bookTitle as 'Title', bookAuthor as 'Author', bookPublisher as 'Publisher', publicationPlace as 'Publication Place', publicationYear as 'Pubication Year', pages as 'No of Pages',price as 'Price',Source as 'Source',edition as 'Edition' from bookRegistry");
        }
        else if(i == 1){
            query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student order by regNo ASC");
        }
        else{
            query.prepare("select ledger.borrowId as 'Borrow ID',ledger.accessionNum as 'Book ID',bookRegistry.bookTitle as Title,ledger.regNo as 'Register No',student.name as Name,ledger.issueDate as 'Issue Date',ledger.returnDate as 'Return Date' from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo order by ledger.borrowId DESC");
        }
    }

    if(query.exec()){
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    }
}

void deleteRecords::on_deleteBtn_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    QString reference = ui->referenceID->text();
    QString title;

    if(i == 0){
        query.prepare("select bookTitle from bookRegistry where accessionNum == '" + reference + "'");
        title.append("Book Title : ");
    }
    else if(i == 1){
        query.prepare("select name from student where regNo == '" + reference + "'");
        title.append("Student Name : ");
    }else{
        query.prepare("select borrowID from ledger where borrowId == '" + reference + "'");
        title.append("Borrow ID : ");
    }

    if(query.exec())
        while(query.next())
            title.append(query.value(0).toString());

    QMessageBox::StandardButton reply = QMessageBox::warning(this,"Warning","Do you want to delete this record? \n'" + title + "'",QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){

        if(i == 0){
            query.prepare("delete from bookRegistry where accessionNum == '" + reference + "'");
        }
        else if(i == 1){
            query.prepare("delete from student where regNo == '" + reference + "'");
        }else{
            query.prepare("delete from ledger where borrowId == '" + reference + "'");
        }

        if(query.exec()){
            QMessageBox::information(this,"Successful","Record has been successfully deleted");
            ui->referenceID->setText("");
            display();
        }
        else{
            QMessageBox::warning(this,"Warning","Error while deleting the record");
        }
    }
}


void deleteRecords::on_backBtn_clicked()
{
    deleteRecords::~deleteRecords();
}


void deleteRecords::on_referenceID_textChanged(const QString &arg1)
{
    if(arg1 != ""){
        searchStarted = true;
    }
    else{
        searchStarted = false;
    }
    display();
}

