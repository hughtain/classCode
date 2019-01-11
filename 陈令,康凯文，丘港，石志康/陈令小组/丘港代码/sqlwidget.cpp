#include "sqlwidget.h"
#include "ui_sqlwidget.h"
#include "Connection.h"

sqlWidget::sqlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sqlWidget)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("keshe");
    model->select();
    // 设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

}

sqlWidget::~sqlWidget()
{
    delete ui;
}

void sqlWidget::on_checkButton_clicked()
{
    QString che = ui->lineEdit->text();
    //根据姓名进行筛选，一定要使用单引号
    model->setFilter(QString("id = '%1'").arg(che));
    model->select();

}

void sqlWidget::on_tableButton_clicked()
{
    model->setTable("keshe");
    model->select();
}

void sqlWidget::on_id_upButton_clicked()
{
    //id属性，即第0列，升序排列
    model->setSort(0, Qt::AscendingOrder);
    model->select();

}

void sqlWidget::on_id_downButton_clicked()
{
    model->setSort(0, Qt::DescendingOrder);
    model->select();

}

void sqlWidget::on_deleteButton_clicked()
{
    // 获取选中的行
    int curRow = ui->tableView->currentIndex().row();
    // 删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("Delete record!"),
                    tr("Are you sure? "),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {   // 如果不删除， 则撤销
        model->revertAll();
    }
    else
    {   // 否则提交， 在数据库中删除该行
        model->submitAll();
    }

}
