#ifndef BROWSE_H
#define BROWSE_H

#include <QMainWindow>
#include "mydb.h"
#include "addbooks.h"
#include "details.h"

namespace Ui {
class Browse;
}

class Browse : public QMainWindow
{
    Q_OBJECT

public:
    explicit Browse(QWidget *parent = nullptr);
    ~Browse();
    void display();

private slots:
    void on_exitBtn_clicked();

    void on_refresh_clicked();

    void on_addNew_clicked();

    void on_searchingElement_textChanged(const QString &arg1);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::Browse *ui;
    addbooks *adBooks;
    bool searchStarted;
    Details *detailsWindow;
};

#endif // BROWSE_H
