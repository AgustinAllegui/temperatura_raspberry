/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *l_in;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rb_hex;
    QRadioButton *rb_ascii;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QRadioButton *rb_ch1;
    QLineEdit *l_speed0;
    QLabel *label_3;
    QRadioButton *rb_ch0;
    QLineEdit *l_speed1;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QTextBrowser *tb_out;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *b_limpiar;
    QPushButton *b_enviar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(607, 448);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        l_in = new QLineEdit(centralWidget);
        l_in->setObjectName(QStringLiteral("l_in"));

        horizontalLayout_3->addWidget(l_in);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rb_hex = new QRadioButton(widget);
        rb_hex->setObjectName(QStringLiteral("rb_hex"));
        rb_hex->setChecked(true);

        horizontalLayout_2->addWidget(rb_hex);

        rb_ascii = new QRadioButton(widget);
        rb_ascii->setObjectName(QStringLiteral("rb_ascii"));

        horizontalLayout_2->addWidget(rb_ascii);


        horizontalLayout_3->addWidget(widget);


        verticalLayout->addLayout(horizontalLayout_3);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        rb_ch1 = new QRadioButton(widget_2);
        rb_ch1->setObjectName(QStringLiteral("rb_ch1"));

        gridLayout->addWidget(rb_ch1, 2, 0, 1, 1);

        l_speed0 = new QLineEdit(widget_2);
        l_speed0->setObjectName(QStringLiteral("l_speed0"));

        gridLayout->addWidget(l_speed0, 1, 1, 1, 1);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        rb_ch0 = new QRadioButton(widget_2);
        rb_ch0->setObjectName(QStringLiteral("rb_ch0"));
        rb_ch0->setChecked(true);

        gridLayout->addWidget(rb_ch0, 1, 0, 1, 1);

        l_speed1 = new QLineEdit(widget_2);
        l_speed1->setObjectName(QStringLiteral("l_speed1"));

        gridLayout->addWidget(l_speed1, 2, 1, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);


        verticalLayout->addWidget(widget_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        tb_out = new QTextBrowser(centralWidget);
        tb_out->setObjectName(QStringLiteral("tb_out"));

        verticalLayout->addWidget(tb_out);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        b_limpiar = new QPushButton(centralWidget);
        b_limpiar->setObjectName(QStringLiteral("b_limpiar"));

        horizontalLayout->addWidget(b_limpiar);

        b_enviar = new QPushButton(centralWidget);
        b_enviar->setObjectName(QStringLiteral("b_enviar"));

        horizontalLayout->addWidget(b_enviar);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 607, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Input", Q_NULLPTR));
        rb_hex->setText(QApplication::translate("MainWindow", "Hexa", Q_NULLPTR));
        rb_ascii->setText(QApplication::translate("MainWindow", "ASCII", Q_NULLPTR));
        rb_ch1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        l_speed0->setText(QApplication::translate("MainWindow", "500000", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Canal", Q_NULLPTR));
        rb_ch0->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        l_speed1->setText(QApplication::translate("MainWindow", "500000", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Velocidad [Hz]", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Output", Q_NULLPTR));
        b_limpiar->setText(QApplication::translate("MainWindow", "Limpiar", Q_NULLPTR));
        b_enviar->setText(QApplication::translate("MainWindow", "Enviar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
