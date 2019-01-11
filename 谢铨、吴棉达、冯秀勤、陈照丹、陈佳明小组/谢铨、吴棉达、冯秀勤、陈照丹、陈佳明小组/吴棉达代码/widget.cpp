
#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    //connect(t,SIGNAL(ab()),this,SLOT(change()));

    myCom= new Posix_QextSerialPort("/dev/ttyUSB0",QextSerialBase::Polling);







     //readTimer->start(100);
    myCom->open(QIODevice::ReadWrite);

       //以读写方式打开串口

      myCom->setBaudRate(BAUD9600);

       //波特率设置，我们设置为9600

      myCom->setDataBits(DATA_8);

      //数据位设置，我们设置为8位数据位

      myCom->setParity(PAR_NONE);

       //奇偶校验设置，我们设置为无校验

      myCom->setStopBits(STOP_1);

       //停止位设置，我们设置为1位停止位

      myCom->setFlowControl(FLOW_OFF);

       //数据流控制设置，我们设置为无数据流控制
      myCom->setTimeout(10);






   readTimer=new QTimer(this);
   readTimer->start(1000);
   connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
   ui->textEdit->insertPlainText("1");



}


void Widget::change()
{
    ui->startthread_button->setEnabled(true);
    ui->stopthread_button->setEnabled(true);


}

void delay(unsigned int a)
{
        unsigned int i;
        while (--a!=0)
        {
            for(i=0;i<600;i++);
        }
}





Widget::~Widget()
{
    delete ui;
}




void Widget::readMyCom()//读取串口数据并显示出来

{

   ui->textEdit->clear();
   ui->textEdit_2->clear();
   QString temp = myCom->readAll();
//ui->textBrowser->insertPlainText(temp);
    //读取串口缓冲区的所有数据给临时变量temp
  int index = temp.indexOf(":");
   //int index=2;
      wendu= temp.mid(index-2,2);
      //delay(1000);
      shidu= temp.mid(index+1,2);
     // delay(1000);

   ui->textEdit->insertPlainText(wendu);
  // ui->textEdit->insertPlainText(temp);

   //delay(1000);
   ui->textEdit_2->insertPlainText(shidu);
    //将串口的数据显示在窗口的文本浏览器中
  /*char sendbuf[100]={0};
   QByteArray ba = temp.toLatin1();

   strcpy(sendbuf,ba.data());
   socket->write(sendbuf,strlen(sendbuf));   //把相关数据送入管道
   socket->flush(); //防止数据较少不能自动发送，所以推一把
*/

   thread.add(temp);
   delay(100);
   temp.clear();

}



void Widget::on_pushButton_clicked()
{

}

void Widget::on_startthread_button_clicked()
{
    thread.start();
    ui->startthread_button->setEnabled(false);
    ui->stopthread_button->setEnabled(true);

}

void Widget::on_stopthread_button_clicked()
{
    if(thread.isRunning())
    {
        thread.stop();
        ui->startthread_button->setEnabled(true);
        ui->stopthread_button->setEnabled(true);
    }
}
