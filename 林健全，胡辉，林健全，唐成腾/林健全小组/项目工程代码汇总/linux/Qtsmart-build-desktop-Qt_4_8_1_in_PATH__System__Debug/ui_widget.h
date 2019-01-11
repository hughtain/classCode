/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Mon Dec 31 12:47:40 2018
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *startthread_button;
    QPushButton *stopthread_button;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 300);
        frame = new QFrame(Widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 401, 301));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 160, 98, 27));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 160, 98, 27));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 66, 17));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 70, 66, 17));
        textEdit = new QTextEdit(frame);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(180, 40, 104, 21));
        textEdit_2 = new QTextEdit(frame);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(180, 70, 104, 21));
        startthread_button = new QPushButton(frame);
        startthread_button->setObjectName(QString::fromUtf8("startthread_button"));
        startthread_button->setGeometry(QRect(60, 210, 98, 27));
        stopthread_button = new QPushButton(frame);
        stopthread_button->setObjectName(QString::fromUtf8("stopthread_button"));
        stopthread_button->setGeometry(QRect(230, 210, 98, 27));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Widget", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "wendu", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "shidu", 0, QApplication::UnicodeUTF8));
        startthread_button->setText(QApplication::translate("Widget", "start", 0, QApplication::UnicodeUTF8));
        stopthread_button->setText(QApplication::translate("Widget", "stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
