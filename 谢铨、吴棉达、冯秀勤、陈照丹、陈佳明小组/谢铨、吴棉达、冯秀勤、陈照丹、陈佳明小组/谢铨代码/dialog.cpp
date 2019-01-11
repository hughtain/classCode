#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    tableView=new QTableView(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
     int r=0;
      QSqlQuery query;
      query.exec("select * from type");

     QStandardItemModel *model=new QStandardItemModel(sum,4,this);
     while(query.next())
   {



        QStandardItem *item=new QStandardItem(query.value(0).toString());
        model->setItem(r,0,item);

        QStandardItem *item1=new QStandardItem(query.value(1).toString());
        model->setItem(r,1,item1);

        QStandardItem *item2=new QStandardItem(query.value(2).toString());
        model->setItem(r,2,item2);

        QStandardItem *item3=new QStandardItem(query.value(3).toString());
        model->setItem(r,3,item3);

        r++;
    }


       tableView->resize(400,300);
       tableView->setModel(model);
       tableView->show();

       sum=0;
}

void Dialog::on_pushButton_2_clicked()
{
    QSqlQuery query;
    tableView->close();
    query.exec("delete from type");
    sum=0;
}
