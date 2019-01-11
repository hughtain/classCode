#ifndef CONNECTION_H
#define CONNECTION_H

#include<QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("G607_2.db");
    if(!db.open()){
        QMessageBox::critical(0,QObject::tr("wrong!"),"fail!",QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query(db);
    query.exec("SET NAMES 'Latin1'");
    query.exec("create table keshe(id int primary key,temperature varchar(10),humidity varchar(10))");
    query.exec("insert into keshe values(0,'32','80')");
    return true;
}
#endif // CONNECTION_H
