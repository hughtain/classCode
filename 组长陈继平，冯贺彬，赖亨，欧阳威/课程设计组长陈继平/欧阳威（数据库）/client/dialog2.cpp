#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("create table password(id varchar(50) primary key,pwd varchar(50))");
    query.exec("insert into password values('123', '123456')");
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton_clicked()
{
           QSqlQuery query;
           query.exec("select pwd from password");
           query.next();
           if (query.value(0).toString() == ui->lineEdit_2->text()) {
               dia.exec();
           } else {
               QMessageBox::warning(this, tr("密码错误"), tr("请输入正确的密码再登录！"), QMessageBox::Ok);
}
}

void Dialog2::on_pushButton_2_clicked()
{
    this->close();
}
