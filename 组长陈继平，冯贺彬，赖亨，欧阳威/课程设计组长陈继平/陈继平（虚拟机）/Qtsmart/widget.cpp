
#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stopthread_button->hide();

    //connect(t,SIGNAL(ab()),this,SLOT(change()));

    myCom= new Posix_QextSerialPort("/dev/ttyUSB0",QextSerialBase::Polling);







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
            for(i=0;i<10;i++);
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

   int index = temp.indexOf(":");

      wendu= temp.mid(index-2,2);

      shidu= temp.mid(index+1,2);

   ui->textEdit->insertPlainText(wendu);

   ui->textEdit_2->insertPlainText(shidu);

   thread.add(temp);
   delay(100);
   temp.clear();


}



void Widget::on_startthread_button_clicked()
{
    thread.start();
    ui->startthread_button->hide();
    ui->stopthread_button->show();

}

void Widget::on_stopthread_button_clicked()
{
    if(thread.isRunning())
    {
        thread.stop();
        ui->startthread_button->show();
        ui->stopthread_button->hide();
    }
}

