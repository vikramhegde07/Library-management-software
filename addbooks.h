#ifndef ADDBOOKS_H
#define ADDBOOKS_H

#include <QMainWindow>
#include "mydb.h"
#include <QMessageBox>

namespace Ui {
class addbooks;
}

class addbooks : public QMainWindow
{
    Q_OBJECT

public:
    explicit addbooks(QWidget *parent = nullptr);
    ~addbooks();

private slots:

    void on_copies_currentIndexChanged(int index);

    void on_closeBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::addbooks *ui;
};

#endif // ADDBOOKS_H
