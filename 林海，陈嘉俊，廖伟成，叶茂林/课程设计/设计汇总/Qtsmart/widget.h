#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "qextserialbase.h"
#include <QTimer>
#include "mythread.h"
//server


namespace Ui {
class Widget;

}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();
    
private slots:
    void on_pushButton_clicked();
    void readMyCom();

    void change();

    void on_startthread_button_clicked();

    void on_stopthread_button_clicked();

private:
    MyThread thread;

    Ui::Widget *ui;
    Posix_QextSerialPort *myCom;
    QTimer *readTimer;

    QByteArray  requestData;//（用于存储从串口那读取的数据）
    QString wendu;
    QString shidu;
    QString a;


};

#endif // WIDGET_H
