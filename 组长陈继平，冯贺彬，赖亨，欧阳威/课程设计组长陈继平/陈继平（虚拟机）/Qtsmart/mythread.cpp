#include "mythread.h"

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{

}


void MyThread::run()
{
        server = new QTcpServer(this);
        server->listen(QHostAddress::Any,9090);
        connect(server,SIGNAL(newConnection()),this,SLOT(imcoming()));    //如果有新的连接信息newConnection(),触发imcoming()
        exec();

}

void MyThread::imcoming()
{

             socket = server->nextPendingConnection();   //把客户端的socket端口存入到服务器端的socket端口，理论上只有一个socket

             readTimer=new QTimer(this);
             readTimer->start(1000);
             connect(readTimer,SIGNAL(timeout()),this,SLOT(send()));
             connect(socket,SIGNAL(disconnected()),this,SLOT(changebutton()));  //管道没连接，那么出发enServerButton()设置相关按键使能与否

}

void MyThread::add(QString a)
{
        QString data=a;

        QByteArray buf = data.toLatin1();
        strcpy(sendbuf,buf.data());


}

void MyThread::send()
{
    socket->write(sendbuf,strlen(sendbuf));   //把相关数据送入管道
    socket->flush();                      //防止数据较少不能自动发送，所以推一把


}

void MyThread::stop()
{
        socket->abort();               //让管道失效


}

void MyThread::changebutton()
{
    //emit ab();
}
