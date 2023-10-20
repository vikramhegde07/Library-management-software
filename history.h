#ifndef HISTORY_H
#define HISTORY_H

#include <QMainWindow>
#include "mydb.h"
#include "details.h"

namespace Ui {
class history;
}

class history : public QMainWindow
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();
    void display();

private slots:
    void on_refreshBtn_clicked();

    void on_backBtn_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::history *ui;
    Details *detailsWindow;
};

#endif // HISTORY_H
