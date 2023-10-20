#ifndef DELETERECORDS_H
#define DELETERECORDS_H

#include <QMainWindow>
#include "mydb.h"
#include <QMessageBox>

namespace Ui {
class deleteRecords;
}

class deleteRecords : public QMainWindow
{
    Q_OBJECT

public:
    explicit deleteRecords(QWidget *parent = nullptr);
    ~deleteRecords();
    void display();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_deleteBtn_clicked();

    void on_backBtn_clicked();

    void on_referenceID_textChanged(const QString &arg1);

private:
    Ui::deleteRecords *ui;
    int i;
    bool searchStarted;
};

#endif // DELETERECORDS_H
