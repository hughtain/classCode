#ifndef SQLWIDGET_H
#define SQLWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>


namespace Ui {
class sqlWidget;
}

class QSqlTableModel;

class sqlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit sqlWidget(QWidget *parent = 0);
    ~sqlWidget();
    
private slots:
    void on_checkButton_clicked();

    void on_tableButton_clicked();

    void on_id_upButton_clicked();

    void on_id_downButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::sqlWidget *ui;
    QSqlTableModel *model;
};

#endif // SQLWIDGET_H
