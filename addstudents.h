#ifndef ADDSTUDENTS_H
#define ADDSTUDENTS_H

#include <QMainWindow>
#include "mydb.h"
#include <QMessageBox>

namespace Ui {
class addStudents;
}

class addStudents : public QMainWindow
{
    Q_OBJECT

public:
    explicit addStudents(QWidget *parent = nullptr);
    ~addStudents();

private slots:
    void on_exitBtn_clicked();

    void on_clearBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::addStudents *ui;
};

#endif // ADDSTUDENTS_H
