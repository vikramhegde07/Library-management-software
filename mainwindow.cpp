#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    L.setModal(true);
//    L.exec();
//    checkLogin();
    display_info();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::checkLogin()
{
    if(L.windowState().toInt() == 0)
        MainWindow::~MainWindow();
}

void MainWindow::on_bookRegistry_clicked()
{
    browse = new Browse(this);
    browse->show();
}


void MainWindow::on_borrowNew_clicked()
{
    borrownewbook = new borrowNew(this);
    borrownewbook->show();
}


void MainWindow::on_ReturnBook_clicked()
{
    returnBook = new Return(this);
    returnBook->show();
}

void MainWindow::on_studentRegistry_clicked()
{
    SR = new studentRegistry(this);
    SR->show();
}


void MainWindow::on_history_clicked()
{
    borrowHistory = new history(this);
    borrowHistory->show();
}


void MainWindow::on_deleteRecords_clicked()
{
    dRecords = new deleteRecords(this);
    dRecords->show();
}


void MainWindow::on_DeepSearch_clicked()
{
    DS = new DeepSearch(this);
    DS->show();
}

void MainWindow::display_info()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select count(accessionNum) from bookRegistry");
    QString s;
    if(query.exec())
        while(query.next())
            s = query.value(0).toString();
    ui->book_count->setText(s);

    query.prepare("select count(borrowId) from ledger");
    if(query.exec())
        while(query.next())
            s = query.value(0).toString();
    ui->issue_count->setText(s);

    query.prepare("select count(borrowId) from ledger where returnDate != ''");
    if(query.exec())
        while(query.next())
            s = query.value(0).toString();
    ui->return_count->setText(s);

    query.prepare("select count(borrowId) from ledger where returnDate = ''");
    if(query.exec())
        while(query.next())
            s = query.value(0).toString();
    ui->not_return_count->setText(s);
}

void MainWindow::on_refresh_Btn_clicked()
{
    display_info();
}


void MainWindow::on_backup_Btn_clicked()
{
    fstream read , write , log;
    string line;

    string backupfile = "C:/Users/Vikra/Dropbox/PC/Desktop/Library Database/Backups/backup -";
    backupfile.append(QDate::currentDate().toString().toStdString());
    backupfile.append(".db");

    read.open("C:/Users/Vikra/Dropbox/PC/Desktop/Library Database/LibraryManagement.db", ios::in | ios::binary);
    write.open(backupfile, ios::app | ios::binary);
    log.open("C:/Users/vikra/Dropbox/PC/Desktop/Library Database/backup_log.txt",ios::app);

    if(read){
        while (getline(read, line)) {
                    write << line << "\n";
                }
        QMessageBox::information(this,"Success","Data has been Successfully Backed Up");
        log << "\n" << QDate::currentDate().toString().toStdString();

    }else
        QMessageBox::warning(this,"Error","Cannot Read The Targeted Database File");

    read.close();
    write.close();
    log.close();
}


void MainWindow::on_restore_Btn_clicked()
{
    fstream read , write , log;
    string line;

    log.open("C:/Users/Vikra/Dropbox/PC/Desktop/Library Database/backup_log.txt",ios::in);
    while(getline(log,line)){}

    string backupfile = "C:/Users/Vikra/Dropbox/PC/Desktop/Library Database/Backups/backup -";
    backupfile.append(line);
    backupfile.append(".db");

    read.open(backupfile, ios::in | ios::binary);
    write.open("C:/Users/Vikra/Dropbox/PC/Desktop/Library Database/LibraryManagement2.db", ios::app | ios::binary);

    if(read){
        while (getline(read, line)) {
                    write << line << "\n";
                }
        QMessageBox::information(this,"Success","Data has been Successfully Restored");

    }else
        QMessageBox::warning(this,"Error","Cannot Read The Targeted Database File");
}

