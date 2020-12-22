#include"DataBase.h"

QSqlDatabase sqlInit()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("chasingdatabase");
    if(!db.open()){
        QMessageBox::critical(nullptr,"error",db.lastError().text(),QMessageBox::Ok);
        exit(0);
    }
    return db;
}
