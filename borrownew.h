#ifndef BORROWNEW_H
#define BORROWNEW_H

#include <QMainWindow>
#include "mydb.h"
#include <QMessageBox>

namespace Ui {
class borrowNew;
}

class borrowNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit borrowNew(QWidget *parent = nullptr);
    ~borrowNew();

private slots:
    void on_Exit_clicked();

    void on_bookIdSearch_clicked();

    void on_StudentIdSearch_clicked();

    void on_AddToRecord_clicked();

private:
    Ui::borrowNew *ui;
    QString borrowId;
};

#endif // BORROWNEW_H
