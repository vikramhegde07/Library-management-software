#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "addbooks.h"
#include "browse.h"
#include "borrownew.h"
#include "history.h"
#include "return.h"
#include "studentregistry.h"
#include "deleterecords.h"
#include "deepsearch.h"
#include "mydb.h"
#include <QMessageBox>
#include <string.h>
#include <fstream>
#include <QDate>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void checkLogin();
    void display_info();

private slots:
    void on_borrowNew_clicked();

    void on_ReturnBook_clicked();

    void on_bookRegistry_clicked();

    void on_studentRegistry_clicked();

    void on_history_clicked();

    void on_deleteRecords_clicked();

    void on_DeepSearch_clicked();

    void on_refresh_Btn_clicked();

    void on_backup_Btn_clicked();

    void on_restore_Btn_clicked();

private:
    Ui::MainWindow *ui;
    Login L;
    addbooks *addBook;
    Browse *browse;
    borrowNew *borrownewbook;
    history *borrowHistory;
    Return *returnBook;
    studentRegistry *SR;
    deleteRecords *dRecords;
    DeepSearch *DS;
};
#endif // MAINWINDOW_H
