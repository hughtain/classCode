#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextCodec>
#include <QTime>
#include <QObject>
#include <QDateTime>
#include "sqlwidget.h"

namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientWidget(QWidget *parent = 0);
    ~clientWidget();
    sqlWidget *sql_wid;
    int id_count;

private:
    Ui::clientWidget *ui;
    QTcpSocket *socket;
private slots:
    void onConnect();
    void onDisconnect();
    void onread();
    void imcoming();
    void enServerButton();
    void onlight();
    void onlight1();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_sqlButton_clicked();
};

#endif // CLIENTWIDGET_H
