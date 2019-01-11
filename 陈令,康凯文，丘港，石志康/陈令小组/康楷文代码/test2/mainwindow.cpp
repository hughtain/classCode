#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QAction>
#include <QSharedMemory>
#include "stdio.h"
#include<QTimer>
#include"qextserialport.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    warnboxflag=0;


    mycom=new  Posix_QextSerialPort( "/dev/ttyUSB0" ,QextSerialBase::Polling);//定义串口，传递参数，初始化串口，这句在linux下定义的"/dev/ttyS0"
    mycom->open(QIODevice::ReadWrite);//以读写方式打开串口

    mycom->setBaudRate(BAUD115200);
    mycom->setDataBits(DATA_8);
    mycom->setParity(PAR_NONE);
    mycom->setStopBits(STOP_1);
    mycom->setFlowControl(FLOW_OFF);//设置数据流控制，我们使用无数据流控制的默认设置
    QTimer *readTimer=new QTimer(this);//定时器关联
    QObject::connect (readTimer,SIGNAL(timeout()), this,SLOT(readMyCom() ) ) ;
    readTimer->start(3000);//延时100ms
    ui->centralWidget->setStyleSheet("transparent");
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any,9090))    //如果服务没监听到9090端口执行{}里信息
    {
        ui->textEdit->append("Listening filed!");
        return;
    }
     ui->textEdit->append("Listening...");
     connect(server,SIGNAL(newConnection()),this,SLOT(imcoming()));    //如果有新的连接信息newConnection(),触发imcoming()
     connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onsend())); //点击发送，触发相应槽
     connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(onlightfast()));
     connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(onlightslow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readMyCom()//读串口函数
  {


    QByteArray temp = mycom->readAll();

    //读取串口缓冲区的所有数据给临时变量temp

    QByteArray a=temp.left(6);
    QByteArray b=temp.right(4);
    QByteArray aa=a.right(2);
    QByteArray bb=b.right(2);
    //ui->textBrowser->insertPlainText(a.right(2));
    //ui->label->setText(a.right(2));
    //ui->lineEdit->insert(a.right(2));
    ui->lineEdit->setText(a.right(2));
    ui->lineEdit_2->setText(b);

      //int addr = aa[0]& 0x000000FF;
      //addr |=((aa[1]<<8)&0x0000FF00);2
      //addr |=((aa[2]<<16)&0x00FF0000);

    aa=a.right(2);
    bool ok;

    if (aa.toInt(&ok)>32 && (warnboxflag==0) )
    {
        QMessageBox::warning(this, tr("Waring"),
                   tr("temperature is to higher!"),
                   QMessageBox::Yes);
        warnboxflag=1;

   }
    //a.clear();
    //QTimer *Timer=new QTimer(this);
    //connect(timer,SGINAL(timeout),this,timeoutslot);
    //readTimer->start(1);
    //ui->lineEdit->clear();

    //将串口的数据显示在窗口的文本浏览器中

 }

void MainWindow::delay()//yanchi
{

    //QTimer *timer=new QTimer(this);
    //readTimer->stop();
    ui->lineEdit->insert("1");
    //ui->lineEdit->clear();
}
 void MainWindow::imcoming()
 {
     socket = server->nextPendingConnection();//把客户端的socket端口存入到服务器端的socket端口
     ui->textEdit->append("connected.");
     connect(socket,SIGNAL(readyRead()),this,SLOT(onread()));   //管道准备好读取数据，触发onread()
 }
 void MainWindow::onread()
 {
     char buf[100];                            //暂存数据中转站
     memset(buf,0,sizeof(buf));               //先清0
     int length = socket->bytesAvailable();   //从管道中计算传送数据长度
     socket->read(buf,length);                //把指定长度数据从管道中放入缓冲区buf
     mycom->write(buf,4);
 }

void MainWindow::onsend()
{
    QString data=ui->lineEdit->text();
    QString data2=ui->lineEdit_2->text();
    QString data3=" ";
    data=data+data3+data2;
    char sendbuf[100]={0};
    QByteArray ba = data.toLatin1();
    strcpy(sendbuf,ba.data());
    socket->write(sendbuf,strlen(sendbuf));   //把相关数据送入管道
    socket->flush();                      //防止数据较少不能自动发送，所以推一把
    memset(sendbuf,0,sizeof(sendbuf));

}
void MainWindow::onlightfast(){
    QByteArray a="tr";
    mycom->write(a,4);
}
void MainWindow::onlightslow(){
    QByteArray b="fa";
    mycom->write(b,4);
}
