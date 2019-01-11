#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QDateTime>
#include <QDebug>

static bool createConnection()
{   qDebug()<<"aa";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<"bb";
    db.setDatabaseName("ss.db");
    qDebug()<<"cc";
    if (!db.open()) {
         QMessageBox::critical(0, QObject::tr("无法打开数据库"),
             "无法创建数据库连接！", QMessageBox::Cancel);
         qDebug()<<"dd";
         return false;
     }

    QSqlQuery query;

    QString aaaa;
    QString bbbb;
    bbbb=QTime::currentTime().toString("hh:mm:ss");
    aaaa=QDateTime::currentDateTime().toString("yyyy-MM-dd");
    qDebug()<<aaaa;
    qDebug()<<bbbb;
    // 创建分类表
    query.exec("create table type(data varchar(500),time varchar(500),wendu varchar(500), shidu varchar(500))");
    query.exec(QString("insert into type values('%1','%2','30','40')").arg(aaaa).arg(bbbb));
    qDebug()<<"ee";
    return true;
}

#endif // CONNECTION_H

