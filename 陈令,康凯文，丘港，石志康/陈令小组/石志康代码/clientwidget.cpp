#include "sqlwidget.h"
#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QString>
#include "Connection.h"
#include <QDebug>

clientWidget::clientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientWidget)
{
    ui->setupUi(this);
    id_count=0;
    socket = new QTcpSocket(this);
    connect(ui->pushButton_connect,SIGNAL(clicked()),this,SLOT(onConnect()));     //点击相关按钮触发相关槽函数
    connect(ui->pushButton_disconnect,SIGNAL(clicked()),this,SLOT(onDisconnect()));
    //connect(ui->pushButton_send,SIGNAL(clicked()),this,SLOT(onSend()));
    connect(socket,SIGNAL(connected()),this,SLOT(imcoming()));    //管道建立后触发相关函数
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onlight())); //kaideng
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(onlight1())); //kaideng2
    //ui->pushButton_send->setShortcut(tr("Ctrl+R"));     //设置发送相关快捷键
}

clientWidget::~clientWidget()
{
    delete socket;
    delete ui;
}
/*连接按钮点击后的函数*/
void clientWidget::onConnect()
{
    ui->pushButton_connect->setDisabled(true);    //设置相关按键使能与否

    socket->connectToHost(QString(ui->lineEdit_socket->text()),9090);    //这里可以在lineEdit里写相应ip，如果只是测试只要输入localhost即可，且配置好端口
    if(!socket->waitForConnected(3000))              //等待3s，如果管道没接通那么则行{}内容
    {
        ui->pushButton_connect->setEnabled(true);
        ui->textEdit->append("connect failed!");
        return;

    }
    ui->pushButton_disconnect->setEnabled(true);  //设置相关按键使能与否
    //ui->pushButton_send->setEnabled(true);
    ui->textEdit->append("connected to host");
  //  connect(socket,SIGNAL(readyRead()),this,SLOT(onread()));



}


/*点击Disconnect按钮后执行函数*/
void clientWidget::onDisconnect()
{
    socket->abort();     //强行断开管道
    ui->textEdit->append("disconnected!");     //设置相关按键使能与否
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setDisabled(true);
    //ui->pushButton_send->setDisabled(true);
   // connect(socket,SIGNAL(readyRead()),this,SLOT(onread()));
}


/*点击Send按钮后触发函数*/
/*void clientWidget::onSend()
{
    socket->write(ui->lineEdit->text().toUtf8());    //写信息进管道
   // socket->write("Hello",strlen("Hello"));    //写信息进管道
    socket->flush();                //推信息
    ui->lineEdit->clear();

}*/

void clientWidget::onlight(){

    socket->write("tr",strlen("tr"));    //写信息进管道
   // socket->write("Hello",strlen("Hello"));    //写信息进管道
    socket->flush();

}

void clientWidget::onlight1(){

    socket->write("fa",strlen("fa"));    //写信息进管道
   // socket->write("Hello",strlen("Hello"));    //写信息进管道
    socket->flush();

}

/*读信息函数*/
void clientWidget::onread()
{

   char bufclient[100];//缓冲区
   char tem[5],hum[5];
   memset(bufclient,0,sizeof(bufclient));   //清空缓冲区
   int lengthc = socket->bytesAvailable();   //从管道中计算传送数据长度
   socket->read(bufclient,lengthc);                //把指定长度数据从管道中放入缓冲区buf
   memset(tem,0,sizeof(tem));
   memset(hum,0,sizeof(hum));
   tem[0]=bufclient[0];
   tem[1]=bufclient[1];
   hum[0]=bufclient[4];
   hum[1]=bufclient[5];
   //QByteArray jieshou=bufclient;
   //QByteArray wendu=jieshou.left(2);
   //QByteArray shidu=jieshou.right(4);
   ui->textEdit->insertPlainText("\n");
   ui->textEdit->insertPlainText("server : ");         //显示相关发信息人，以及时间等
   ui->textEdit->insertPlainText(QDateTime::currentDateTime().toString("yyyy-mm-dd  "));
   ui->textEdit->insertPlainText(QTime::currentTime().toString("hh:mm:ss"));//textEdit文本框显示当前时间
   ui->textEdit->insertPlainText("\n");
   ui->textEdit->append(bufclient);            //显示信息
   ui->textEdit->insertPlainText("\n");
   ui->lineEdit_2->setText(tem);
   ui->lineEdit_3->setText(hum);
   //ui->textEdit->append(bufclient);
   //query.prepare("insert into keshe(id,temperature,humidity) valuse(:i, :t, :h)");
   //qDebug()<<"error on here";
   QSqlQuery query;
   int i;
   i=id_count;
   id_count++;
   query.exec(QString ("insert into keshe values('%1','%2','%3')").arg(i).arg(tem).arg(hum));
   //qDebug()<<tem<<hum;
}


/*管道建立后，触发的相关函数*/
void clientWidget::imcoming()
{

    ui->textEdit->append("connected.");
    connect(socket,SIGNAL(readyRead()),this,SLOT(onread()));   //准备，然后触发读信息槽
    connect(socket,SIGNAL(disconnected()),this,SLOT(enServerButton()));//管道断开，触发相关槽
}


/*断开后，各按键相关使能函数*/
void clientWidget::enServerButton()
{
    ui->pushButton_connect->setEnabled(true);  //各按键使能
    ui->pushButton_disconnect->setDisabled(true);
    //ui->pushButton_send->setDisabled(true);
 //   socket->abort();

}

void clientWidget::on_sqlButton_clicked()
{
    sql_wid = new sqlWidget;
    sql_wid->show();
}
