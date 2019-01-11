#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include "connection.h"
#include <QMessageBox>

static int sum=0;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
     QTableView *tableView;
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
