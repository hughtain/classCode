#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <posix_qextserialport.h> //add touwenjian
#include<QTimer>
#include"QMessageBox"

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextCodec>
#include <QTime>
#include <QDate>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpServer *server;
    QTcpSocket *socket;

private:
    Ui::MainWindow *ui;
    Posix_QextSerialPort *mycom; //xinjianduixiang
    QTimer *readTimer;
    int warnboxflag;

private slots:
        void readMyCom();
        //void timeroutslot();
        void delay();
        void imcoming();
        void onread();
        void onsend();
        void onlightfast();
        void onlightslow();



};

#endif // MAINWINDOW_H
