#ifndef STUDENTREGISTRY_H
#define STUDENTREGISTRY_H

#include <QMainWindow>
#include "mydb.h"
#include "addstudents.h"

namespace Ui {
class studentRegistry;
}

class studentRegistry : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentRegistry(QWidget *parent = nullptr);
    ~studentRegistry();

    void display();

private slots:
    void on_exitBtn_clicked();

    void on_refresh_clicked();

    void on_addNewStudent_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::studentRegistry *ui;
    addStudents *AS;
    int choice;
};

#endif // STUDENTREGISTRY_H
