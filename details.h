#ifndef DETAILS_H
#define DETAILS_H

#include <QMainWindow>
#include "mydb.h"
#include <QDate>
#include <QMessageBox>

namespace Ui {
class Details;
}

class Details : public QMainWindow
{
    Q_OBJECT

public:
    explicit Details(QWidget *parent = nullptr);
    ~Details();
    void AcceptData(QString data, int n);
    void disableField();
    void setStrings(QString data, int n);
    void FillData(int n);
    void enableField();
    void hideField(int n);
    void updateTables();

private slots:
    void on_Edit_clicked();

    void on_Exit_clicked();

    void on_ConfirmReturn_clicked();

private:
    Ui::Details *ui;
    QString title,author,publisher,accessionNum,place,year,edition,source,pages,price;
    QString name,renNo,course;
    QString issueDate,returnDate,dueDate,borrowId;
    bool returned,editingStarted;
    int incomingDatabase;
};

#endif // DETAILS_H
