#include "addbooks.h"
#include "ui_addbooks.h"

addbooks::addbooks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addbooks)
{
    ui->setupUi(this);
    ui->copies->setCurrentIndex(1);
}

addbooks::~addbooks()
{
    delete ui;
}

void addbooks::on_copies_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->endingLabel->hide();
        ui->endNo->hide();
        ui->startingLabel->setText("Accession No");
    }
    else if(index == 1)
    {
        ui->endingLabel->show();
        ui->endNo->show();
        ui->startingLabel->setText("Starting No");
    }
}
void addbooks::on_closeBtn_clicked()
{
    addbooks::~addbooks();
}

void addbooks::on_addBtn_clicked()
{
    QString title = ui->bookTitle->text();
    QString author = ui->bookAuthor->text();
    QString pages = ui->pages->text();
    QString year = ui->publishedYear->text();
    QString price = ui->price->text();
    QString edition = ui->Edition->text();
    QString starting = ui->startNo->text();
    QString publisher = ui->bookPublisher->text();
    QString place = ui->place->text();
    QString source = ui->source->text();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    if(ui->copies->currentIndex() == 0){
        query.prepare("insert into bookRegistry values('" + starting + "','" + title +"','"+ author +"','"+ publisher +"','"+ place +"','"+ year +"','"+ pages +"','"+ price +"','"+ source +"','"+ edition +"')");

        if(query.exec())
        {
            QMessageBox::information(this,"Success","Information added to database successfully");
        }
        else{
            QMessageBox::critical(this,"Failed", "Error while adding information");
        }
    }
    else if(ui->copies->currentIndex() == 1)
    {
        QString ending = ui->endNo->text();
        if(starting.toInt() > ending.toInt())
        {

        }
        else
        {
            for(int i = starting.toInt(); i <= ending.toInt(); i++)
            {
                QString n = QString::number(i);
                query.prepare("insert into bookRegistry values('" + n + "','" + title +"','"+ author +"','"+ publisher +"','"+ place +"','"+ year +"','"+ pages +"','"+ price +"','"+ source +"','"+ edition +"')");
                if(query.exec())
                {
                    QMessageBox::information(this,"Success","Information added to database successfully");
                }
                else{
                    QMessageBox::critical(this,"Failed", "Error while adding information");
                }
            }
        }
    }

}

