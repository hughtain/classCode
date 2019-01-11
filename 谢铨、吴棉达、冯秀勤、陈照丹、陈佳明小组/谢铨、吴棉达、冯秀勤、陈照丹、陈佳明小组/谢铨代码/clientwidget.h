#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextCodec>
#include <QTime>
#include <QDateTime>
#include <QDebug>

#include <dialog2.h>



namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientWidget(QWidget *parent = 0);


    ~clientWidget();

private:
    Ui::clientWidget *ui;
    QTcpSocket *socket;
private slots:
    void onConnect();
    void onDisconnect();
    void onSend();
    void onread();
    void imcoming();
    void enServerButton();
    void on_opensqlbutton_clicked();
    void on_cleanbutton_clicked();
    void on_pushBotton_clear_clicked();
};


#endif // CLIENTWIDGET_H
