#include "mydb.h"

MyDB* MyDB::instance = nullptr;

MyDB::MyDB()
{
    initialize();
}
void MyDB::initialize()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    db.setDatabaseName("C:/Users/vikra/Desktop/Library Database/LibraryManagement.db");
//    db.setDatabaseName("C:/Users/vikra/Dropbox/PC/Desktop/Library Database/LibraryManagement.db");


//    if(QFile::exists("C:/Users/vikra/Dropbox/PC/Desktop/Library Database/LibraryManagement.db"))
        if(QFile::exists("C:/Users/vikra/Desktop/Library Database/LibraryManagement.db"))
            qDebug() << "\n";
        else
           qDebug() << "DB file doesn't exists";

        if (!db.open())
            qDebug() << db.lastError().text();
}

MyDB *MyDB::getInstance()
{
    qDebug() << "in MyDB::getInstance()";

    if(instance == nullptr)
        instance = new MyDB();

    return instance;
}

QSqlDatabase MyDB::getDBInstance()
{
    qDebug() <<"in getDBInstance()";
    return db;
}

void MyDB::ResetInstance()
{
      qDebug() << "deleting instance of MyDB";
      delete instance;
      instance = nullptr;
}

MyDB::~MyDB()
{
   qDebug() << "closing database connection";
   db.close();
}
