#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextCodec>
#include <QTime>
#include <QDate>
#include <QTimer>


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    QTcpServer *server;
    QTcpSocket *socket;
    void openserve();
    void add(QString a);


     void run();
     void stop();

signals:

public slots:
    void imcoming();
    void send();
    void changebutton();
private:

     QTimer *readTimer;
    
};
 static char sendbuf[100];
 static int so=0;
#endif // MYTHREAD_H
