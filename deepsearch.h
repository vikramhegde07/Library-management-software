#ifndef DEEPSEARCH_H
#define DEEPSEARCH_H

#include <QMainWindow>
#include "mydb.h"

namespace Ui {
class DeepSearch;
}

class DeepSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeepSearch(QWidget *parent = nullptr);
    ~DeepSearch();
    void display();

private slots:
    void on_searchingArea_textChanged(const QString &arg1);

    void on_databaseOptions_currentIndexChanged(int index);

    void on_exitBtn_clicked();

private:
    Ui::DeepSearch *ui;
    int currentIndex;
    bool searchStarted;
};

#endif // DEEPSEARCH_H
