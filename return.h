#ifndef RETURN_H
#define RETURN_H

#include <QMainWindow>
#include "mydb.h"
#include <QMessageBox>
#include <QDate>
#include "details.h"

namespace Ui {
class Return;
}

class Return : public QMainWindow
{
    Q_OBJECT

public:
    explicit Return(QWidget *parent = nullptr);
    ~Return();
    void display();

private slots:
    void on_exitBtn_clicked();

    void on_refresh_clicked();

    void on_searchBtn_clicked();

    void on_confirmBtn_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::Return *ui;
    bool searchBtn;
    Details *detailWindow;
};

#endif // RETURN_H
