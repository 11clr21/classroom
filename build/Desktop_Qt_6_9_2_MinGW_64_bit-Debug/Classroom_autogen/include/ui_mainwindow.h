/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_8;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout;
    QTextEdit *course_text;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *createfile1;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QPlainTextEdit *next_course_text;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *createfile2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *newtime;
    QPushButton *updata;
    QGridLayout *gridLayout_4;
    QTableView *classList;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *classnumber_text;
    QPushButton *findclassNumber;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *classname_text;
    QPushButton *findclassName;
    QFrame *frame_2;
    QGridLayout *gridLayout_7;
    QLabel *notice_label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(628, 547);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_8 = new QGridLayout(centralwidget);
        gridLayout_8->setObjectName("gridLayout_8");
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #E0E0E0;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #212121; /* \346\267\261\347\201\260\351\273\221\350\211\262\347\232\204\345\255\227 */\n"
"    background-color: transparent;\n"
"}\n"
""));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setObjectName("gridLayout_6");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(frame_3);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(9);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        dateTimeEdit = new QDateTimeEdit(frame_3);
        dateTimeEdit->setObjectName("dateTimeEdit");

        horizontalLayout->addWidget(dateTimeEdit);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_8->addWidget(frame_3, 0, 0, 1, 2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        course_text = new QTextEdit(centralwidget);
        course_text->setObjectName("course_text");
        QFont font1;
        font1.setPointSize(11);
        course_text->setFont(font1);

        gridLayout->addWidget(course_text, 1, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        createfile1 = new QPushButton(centralwidget);
        createfile1->setObjectName("createfile1");

        horizontalLayout_5->addWidget(createfile1);


        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        next_course_text = new QPlainTextEdit(centralwidget);
        next_course_text->setObjectName("next_course_text");
        next_course_text->setFont(font1);

        gridLayout_2->addWidget(next_course_text, 1, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        createfile2 = new QPushButton(centralwidget);
        createfile2->setObjectName("createfile2");

        horizontalLayout_4->addWidget(createfile2);


        gridLayout_5->addLayout(horizontalLayout_4, 2, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_5, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        newtime = new QLineEdit(centralwidget);
        newtime->setObjectName("newtime");

        horizontalLayout_3->addWidget(newtime);

        updata = new QPushButton(centralwidget);
        updata->setObjectName("updata");

        horizontalLayout_3->addWidget(updata);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        classList = new QTableView(centralwidget);
        classList->setObjectName("classList");

        gridLayout_4->addWidget(classList, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        classnumber_text = new QLineEdit(centralwidget);
        classnumber_text->setObjectName("classnumber_text");

        horizontalLayout_2->addWidget(classnumber_text);

        findclassNumber = new QPushButton(centralwidget);
        findclassNumber->setObjectName("findclassNumber");

        horizontalLayout_2->addWidget(findclassNumber);


        gridLayout_4->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        classname_text = new QLineEdit(centralwidget);
        classname_text->setObjectName("classname_text");

        horizontalLayout_7->addWidget(classname_text);

        findclassName = new QPushButton(centralwidget);
        findclassName->setObjectName("findclassName");

        horizontalLayout_7->addWidget(findclassName);


        gridLayout_4->addLayout(horizontalLayout_7, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_3, 2, 1, 1, 1);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #E0E0E0;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #212121; /* \346\267\261\347\201\260\351\273\221\350\211\262\347\232\204\345\255\227 */\n"
"    background-color: transparent;\n"
"}\n"
""));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_7 = new QGridLayout(frame_2);
        gridLayout_7->setObjectName("gridLayout_7");
        notice_label = new QLabel(frame_2);
        notice_label->setObjectName("notice_label");
        notice_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    /* \347\272\242\350\211\262\357\274\210\344\271\237\345\217\257\347\224\250\345\215\201\345\205\255\350\277\233\345\210\266 #FF0000\357\274\214\346\225\210\346\236\234\344\270\200\350\207\264\357\274\211 */\n"
"    color: #FF0000;\n"
"    /* \345\212\240\347\262\227 */\n"
"    font-weight: bold;\n"
"    /* 22\345\217\267\345\255\227\344\275\223\357\274\210\350\213\245\346\203\263\347\224\250\345\267\245\345\217\267\357\274\214\345\217\257\346\224\271\344\270\272 22pt\357\274\211 */\n"
"    font-size: 22px;\n"
"    /* \346\214\207\345\256\232\344\270\255\346\226\207\345\255\227\344\275\223\357\274\214\351\201\277\345\205\215\347\263\273\347\273\237\351\273\230\350\256\244\345\255\227\344\275\223\344\271\261\347\240\201 */\n"
"    font-family: \"Microsoft YaHei\", \"SimHei\", \"Arial\";\n"
"    /* \350\207\252\345\212\250\346\215\242\350\241\214\357\274\210\351\225\277\346\226\207\346\234\254\344\270\215\344\274\232\350\266\205\345\207\272label\350\214\203\345\233\264\357\274\211 */\n"
"    word"
                        "-wrap: break-word;\n"
"    /* \345\205\201\350\256\270\346\226\207\346\234\254\346\215\242\350\241\214\357\274\210\351\273\230\350\256\244QLabel\345\217\257\350\203\275\344\270\215\346\215\242\350\241\214\357\274\211 */\n"
"    white-space: normal;\n"
"    /* \345\217\257\351\200\211\357\274\232\346\226\207\346\234\254\345\261\205\344\270\255\346\230\276\347\244\272 */\n"
"    text-align: center;\n"
"}"));
        notice_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_7->addWidget(notice_label, 0, 0, 1, 1);


        gridLayout_8->addWidget(frame_2, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\225\231\345\256\244\344\277\241\346\201\257\345\261\225\347\244\272\347\263\273\347\273\237", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\245\346\234\237", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\225\231\345\256\244\345\256\211\346\216\222\350\257\276\347\250\213\357\274\232", nullptr));
        createfile1->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\347\217\255\347\272\247\344\273\212\345\244\251\347\232\204\350\257\276\347\250\213\357\274\232", nullptr));
        createfile2->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256", nullptr));
        updata->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\226\260\345\220\214\346\255\245", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\225\231\345\256\244\345\217\267\347\255\233\351\200\211\357\274\232", nullptr));
        findclassNumber->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\347\217\255\347\272\247\345\220\215\347\247\260\347\255\233\351\200\211\357\274\232", nullptr));
        findclassName->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        notice_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
