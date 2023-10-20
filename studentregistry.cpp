#include "studentregistry.h"
#include "ui_studentregistry.h"

studentRegistry::studentRegistry(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::studentRegistry)
{
    ui->setupUi(this);
    choice = 0;
    display();
}

studentRegistry::~studentRegistry()
{
    delete ui;
}

void studentRegistry::display()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    if(choice == 0)
        query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student order by regNo ASC");
    else if(choice == 1)
        query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student where course == 'BCA' order by regNo ASC");
    else
        query.prepare("SELECT regNo as 'Register No', name as 'Student Name',course as 'Course' from student where course == 'BCom' order by regNo ASC");


    if(query.exec())
        model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void studentRegistry::on_exitBtn_clicked()
{
    studentRegistry::~studentRegistry();
}


void studentRegistry::on_refresh_clicked()
{
    display();
}


void studentRegistry::on_addNewStudent_clicked()
{
    AS = new addStudents(this);
    AS->show();
}


void studentRegistry::on_comboBox_currentIndexChanged(int index)
{
    choice = ui->comboBox->currentIndex();
    display();
}

