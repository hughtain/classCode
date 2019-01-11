#include "clientwidget.h"
#include <QApplication>
#include "Connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection())
           QMessageBox::critical(0,QObject::tr("wrong!"),"fail!",QMessageBox::Cancel);
    clientWidget w;
    w.show();

    return a.exec();
}
