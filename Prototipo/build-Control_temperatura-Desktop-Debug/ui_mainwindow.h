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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graficocustom.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_8;
    QTabWidget *tabWidget;
    QWidget *tab_ts;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_12;
    QLineEdit *l_ts;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QWidget *tab_sensor;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rb_PT100;
    QRadioButton *rb_term;
    QFrame *line_2;
    QCheckBox *cb_sensor_ph;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_referencia;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rb_ref_simple;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_ref_simple;
    QLineEdit *l_ref_simple;
    QRadioButton *rb_ref_fun;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *l_dir_ref_fun;
    QPushButton *b_e_ref_fun;
    QRadioButton *rb_ref_val;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QRadioButton *rb_end_repetir;
    QRadioButton *rb_end_0;
    QRadioButton *rb_end_mantener;
    QLabel *label_end;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *l_dir_ref_val;
    QPushButton *b_e_ref_val;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_controlador;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rb_PID;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_Kp;
    QLineEdit *l_Kp;
    QLabel *label_Ki;
    QLineEdit *l_Ki;
    QLabel *label_Kd;
    QLineEdit *l_Kd;
    QRadioButton *rb_c_custom;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *l_dir_c_custom;
    QPushButton *b_e_c_custom;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_ref_fut;
    QSpinBox *sb_future_ref;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *tab_tiempo;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *cb_t_final;
    QTimeEdit *timeEdit_duracion;
    QPushButton *b_usar_t_val;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_resumen;
    QGridLayout *gridLayout_3;
    QTextEdit *te_resumen;
    QWidget *tab_supervision;
    QHBoxLayout *horizontalLayout_9;
    QGridLayout *gridLayout;
    QPushButton *b_iniciar;
    QPushButton *b_detener;
    GraficoCustom *g_supervision;
    QWidget *tab_resultados;
    QVBoxLayout *verticalLayout_7;
    QWidget *g_resultados;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *cb_incluir_resumen;
    QPushButton *b_exportar;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *label_pt100_value;
    QLabel *label_5;
    QLabel *label_term_value;
    QLabel *label_8;
    QLabel *label_act_state;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(717, 609);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_8 = new QVBoxLayout(centralWidget);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_ts = new QWidget();
        tab_ts->setObjectName(QStringLiteral("tab_ts"));
        verticalLayout_9 = new QVBoxLayout(tab_ts);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_12 = new QLabel(tab_ts);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_7->addWidget(label_12);

        l_ts = new QLineEdit(tab_ts);
        l_ts->setObjectName(QStringLiteral("l_ts"));

        horizontalLayout_7->addWidget(l_ts);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_9->addLayout(horizontalLayout_7);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_5);

        tabWidget->addTab(tab_ts, QString());
        tab_sensor = new QWidget();
        tab_sensor->setObjectName(QStringLiteral("tab_sensor"));
        verticalLayout_3 = new QVBoxLayout(tab_sensor);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        rb_PT100 = new QRadioButton(tab_sensor);
        rb_PT100->setObjectName(QStringLiteral("rb_PT100"));
        rb_PT100->setChecked(false);

        verticalLayout_3->addWidget(rb_PT100);

        rb_term = new QRadioButton(tab_sensor);
        rb_term->setObjectName(QStringLiteral("rb_term"));
        rb_term->setChecked(true);

        verticalLayout_3->addWidget(rb_term);

        line_2 = new QFrame(tab_sensor);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        cb_sensor_ph = new QCheckBox(tab_sensor);
        cb_sensor_ph->setObjectName(QStringLiteral("cb_sensor_ph"));
        cb_sensor_ph->setChecked(true);

        verticalLayout_3->addWidget(cb_sensor_ph);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_sensor, QString());
        tab_referencia = new QWidget();
        tab_referencia->setObjectName(QStringLiteral("tab_referencia"));
        verticalLayout_5 = new QVBoxLayout(tab_referencia);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        rb_ref_simple = new QRadioButton(tab_referencia);
        rb_ref_simple->setObjectName(QStringLiteral("rb_ref_simple"));
        rb_ref_simple->setChecked(false);

        verticalLayout_5->addWidget(rb_ref_simple);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_ref_simple = new QLabel(tab_referencia);
        label_ref_simple->setObjectName(QStringLiteral("label_ref_simple"));

        horizontalLayout_12->addWidget(label_ref_simple);

        l_ref_simple = new QLineEdit(tab_referencia);
        l_ref_simple->setObjectName(QStringLiteral("l_ref_simple"));

        horizontalLayout_12->addWidget(l_ref_simple);


        verticalLayout_5->addLayout(horizontalLayout_12);

        rb_ref_fun = new QRadioButton(tab_referencia);
        rb_ref_fun->setObjectName(QStringLiteral("rb_ref_fun"));
        rb_ref_fun->setChecked(true);

        verticalLayout_5->addWidget(rb_ref_fun);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        l_dir_ref_fun = new QLineEdit(tab_referencia);
        l_dir_ref_fun->setObjectName(QStringLiteral("l_dir_ref_fun"));
        l_dir_ref_fun->setEnabled(false);

        horizontalLayout_4->addWidget(l_dir_ref_fun);

        b_e_ref_fun = new QPushButton(tab_referencia);
        b_e_ref_fun->setObjectName(QStringLiteral("b_e_ref_fun"));
        b_e_ref_fun->setEnabled(false);

        horizontalLayout_4->addWidget(b_e_ref_fun);


        verticalLayout_5->addLayout(horizontalLayout_4);

        rb_ref_val = new QRadioButton(tab_referencia);
        rb_ref_val->setObjectName(QStringLiteral("rb_ref_val"));

        verticalLayout_5->addWidget(rb_ref_val);

        widget = new QWidget(tab_referencia);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, -1, 0, -1);
        rb_end_repetir = new QRadioButton(widget);
        rb_end_repetir->setObjectName(QStringLiteral("rb_end_repetir"));
        rb_end_repetir->setEnabled(false);

        gridLayout_4->addWidget(rb_end_repetir, 4, 1, 1, 1);

        rb_end_0 = new QRadioButton(widget);
        rb_end_0->setObjectName(QStringLiteral("rb_end_0"));
        rb_end_0->setEnabled(false);

        gridLayout_4->addWidget(rb_end_0, 3, 1, 1, 1);

        rb_end_mantener = new QRadioButton(widget);
        rb_end_mantener->setObjectName(QStringLiteral("rb_end_mantener"));
        rb_end_mantener->setEnabled(false);
        rb_end_mantener->setChecked(true);

        gridLayout_4->addWidget(rb_end_mantener, 2, 1, 1, 1);

        label_end = new QLabel(widget);
        label_end->setObjectName(QStringLiteral("label_end"));
        label_end->setEnabled(false);

        gridLayout_4->addWidget(label_end, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        l_dir_ref_val = new QLineEdit(widget);
        l_dir_ref_val->setObjectName(QStringLiteral("l_dir_ref_val"));
        l_dir_ref_val->setEnabled(false);

        horizontalLayout_6->addWidget(l_dir_ref_val);

        b_e_ref_val = new QPushButton(widget);
        b_e_ref_val->setObjectName(QStringLiteral("b_e_ref_val"));
        b_e_ref_val->setEnabled(false);

        horizontalLayout_6->addWidget(b_e_ref_val);


        gridLayout_4->addLayout(horizontalLayout_6, 1, 0, 1, 3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 2, 2, 3, 1);


        verticalLayout_5->addWidget(widget);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        tabWidget->addTab(tab_referencia, QString());
        tab_controlador = new QWidget();
        tab_controlador->setObjectName(QStringLiteral("tab_controlador"));
        verticalLayout_2 = new QVBoxLayout(tab_controlador);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rb_PID = new QRadioButton(tab_controlador);
        rb_PID->setObjectName(QStringLiteral("rb_PID"));
        rb_PID->setChecked(false);

        verticalLayout_2->addWidget(rb_PID);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_Kp = new QLabel(tab_controlador);
        label_Kp->setObjectName(QStringLiteral("label_Kp"));

        horizontalLayout_5->addWidget(label_Kp);

        l_Kp = new QLineEdit(tab_controlador);
        l_Kp->setObjectName(QStringLiteral("l_Kp"));

        horizontalLayout_5->addWidget(l_Kp);

        label_Ki = new QLabel(tab_controlador);
        label_Ki->setObjectName(QStringLiteral("label_Ki"));

        horizontalLayout_5->addWidget(label_Ki);

        l_Ki = new QLineEdit(tab_controlador);
        l_Ki->setObjectName(QStringLiteral("l_Ki"));

        horizontalLayout_5->addWidget(l_Ki);

        label_Kd = new QLabel(tab_controlador);
        label_Kd->setObjectName(QStringLiteral("label_Kd"));

        horizontalLayout_5->addWidget(label_Kd);

        l_Kd = new QLineEdit(tab_controlador);
        l_Kd->setObjectName(QStringLiteral("l_Kd"));

        horizontalLayout_5->addWidget(l_Kd);


        verticalLayout_2->addLayout(horizontalLayout_5);

        rb_c_custom = new QRadioButton(tab_controlador);
        rb_c_custom->setObjectName(QStringLiteral("rb_c_custom"));
        rb_c_custom->setChecked(true);

        verticalLayout_2->addWidget(rb_c_custom);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        l_dir_c_custom = new QLineEdit(tab_controlador);
        l_dir_c_custom->setObjectName(QStringLiteral("l_dir_c_custom"));
        l_dir_c_custom->setEnabled(false);

        horizontalLayout_2->addWidget(l_dir_c_custom);

        b_e_c_custom = new QPushButton(tab_controlador);
        b_e_c_custom->setObjectName(QStringLiteral("b_e_c_custom"));
        b_e_c_custom->setEnabled(false);

        horizontalLayout_2->addWidget(b_e_c_custom);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_ref_fut = new QLabel(tab_controlador);
        label_ref_fut->setObjectName(QStringLiteral("label_ref_fut"));
        label_ref_fut->setEnabled(false);

        horizontalLayout_11->addWidget(label_ref_fut);

        sb_future_ref = new QSpinBox(tab_controlador);
        sb_future_ref->setObjectName(QStringLiteral("sb_future_ref"));
        sb_future_ref->setEnabled(false);

        horizontalLayout_11->addWidget(sb_future_ref);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_11);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab_controlador, QString());
        tab_tiempo = new QWidget();
        tab_tiempo->setObjectName(QStringLiteral("tab_tiempo"));
        verticalLayout_4 = new QVBoxLayout(tab_tiempo);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        cb_t_final = new QCheckBox(tab_tiempo);
        cb_t_final->setObjectName(QStringLiteral("cb_t_final"));
        cb_t_final->setChecked(true);

        horizontalLayout_3->addWidget(cb_t_final);

        timeEdit_duracion = new QTimeEdit(tab_tiempo);
        timeEdit_duracion->setObjectName(QStringLiteral("timeEdit_duracion"));
        timeEdit_duracion->setEnabled(false);
        timeEdit_duracion->setTime(QTime(0, 10, 0));

        horizontalLayout_3->addWidget(timeEdit_duracion);

        b_usar_t_val = new QPushButton(tab_tiempo);
        b_usar_t_val->setObjectName(QStringLiteral("b_usar_t_val"));
        b_usar_t_val->setEnabled(false);

        horizontalLayout_3->addWidget(b_usar_t_val);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_tiempo, QString());
        tab_resumen = new QWidget();
        tab_resumen->setObjectName(QStringLiteral("tab_resumen"));
        gridLayout_3 = new QGridLayout(tab_resumen);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        te_resumen = new QTextEdit(tab_resumen);
        te_resumen->setObjectName(QStringLiteral("te_resumen"));
        te_resumen->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(te_resumen, 0, 0, 1, 1);

        tabWidget->addTab(tab_resumen, QString());
        tab_supervision = new QWidget();
        tab_supervision->setObjectName(QStringLiteral("tab_supervision"));
        horizontalLayout_9 = new QHBoxLayout(tab_supervision);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        b_iniciar = new QPushButton(tab_supervision);
        b_iniciar->setObjectName(QStringLiteral("b_iniciar"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(b_iniciar->sizePolicy().hasHeightForWidth());
        b_iniciar->setSizePolicy(sizePolicy1);
        b_iniciar->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(b_iniciar, 0, 0, 1, 1);

        b_detener = new QPushButton(tab_supervision);
        b_detener->setObjectName(QStringLiteral("b_detener"));
        b_detener->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(b_detener->sizePolicy().hasHeightForWidth());
        b_detener->setSizePolicy(sizePolicy2);
        b_detener->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(b_detener, 1, 0, 1, 1);

        g_supervision = new GraficoCustom(tab_supervision);
        g_supervision->setObjectName(QStringLiteral("g_supervision"));

        gridLayout->addWidget(g_supervision, 0, 1, 2, 1);


        horizontalLayout_9->addLayout(gridLayout);

        tabWidget->addTab(tab_supervision, QString());
        tab_resultados = new QWidget();
        tab_resultados->setObjectName(QStringLiteral("tab_resultados"));
        verticalLayout_7 = new QVBoxLayout(tab_resultados);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        g_resultados = new QWidget(tab_resultados);
        g_resultados->setObjectName(QStringLiteral("g_resultados"));
        sizePolicy2.setHeightForWidth(g_resultados->sizePolicy().hasHeightForWidth());
        g_resultados->setSizePolicy(sizePolicy2);

        verticalLayout_7->addWidget(g_resultados);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);

        cb_incluir_resumen = new QCheckBox(tab_resultados);
        cb_incluir_resumen->setObjectName(QStringLiteral("cb_incluir_resumen"));
        cb_incluir_resumen->setChecked(true);

        horizontalLayout_10->addWidget(cb_incluir_resumen);

        b_exportar = new QPushButton(tab_resultados);
        b_exportar->setObjectName(QStringLiteral("b_exportar"));

        horizontalLayout_10->addWidget(b_exportar);


        verticalLayout_7->addLayout(horizontalLayout_10);

        tabWidget->addTab(tab_resultados, QString());

        verticalLayout_8->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        label_pt100_value = new QLabel(centralWidget);
        label_pt100_value->setObjectName(QStringLiteral("label_pt100_value"));

        horizontalLayout->addWidget(label_pt100_value);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        label_term_value = new QLabel(centralWidget);
        label_term_value->setObjectName(QStringLiteral("label_term_value"));

        horizontalLayout->addWidget(label_term_value);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout->addWidget(label_8);

        label_act_state = new QLabel(centralWidget);
        label_act_state->setObjectName(QStringLiteral("label_act_state"));

        horizontalLayout->addWidget(label_act_state);


        verticalLayout_8->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 717, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Tiempo de muestreo [s] =", Q_NULLPTR));
        l_ts->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_ts), QApplication::translate("MainWindow", "Muestreo", Q_NULLPTR));
        rb_PT100->setText(QApplication::translate("MainWindow", "PT100", Q_NULLPTR));
        rb_term->setText(QApplication::translate("MainWindow", "Termocupla", Q_NULLPTR));
        cb_sensor_ph->setText(QApplication::translate("MainWindow", "Sensor de Ph", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_sensor), QApplication::translate("MainWindow", "Sensor", Q_NULLPTR));
        rb_ref_simple->setText(QApplication::translate("MainWindow", "Funcion simple", Q_NULLPTR));
        label_ref_simple->setText(QApplication::translate("MainWindow", "R(Ts,t)=", Q_NULLPTR));
        l_ref_simple->setText(QApplication::translate("MainWindow", "0.2*t/Ts", Q_NULLPTR));
        rb_ref_fun->setText(QApplication::translate("MainWindow", "Archivo de funcion", Q_NULLPTR));
        b_e_ref_fun->setText(QApplication::translate("MainWindow", "Explorar", Q_NULLPTR));
        rb_ref_val->setText(QApplication::translate("MainWindow", "Archivo de valores", Q_NULLPTR));
        rb_end_repetir->setText(QApplication::translate("MainWindow", "Repetir archivo", Q_NULLPTR));
        rb_end_0->setText(QApplication::translate("MainWindow", "Referencia = 0\302\260C", Q_NULLPTR));
        rb_end_mantener->setText(QApplication::translate("MainWindow", "Mantener ultimo valor", Q_NULLPTR));
        label_end->setText(QApplication::translate("MainWindow", "Accion al terminar el archivo:", Q_NULLPTR));
        b_e_ref_val->setText(QApplication::translate("MainWindow", "Explorar", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_referencia), QApplication::translate("MainWindow", "Referencia", Q_NULLPTR));
        rb_PID->setText(QApplication::translate("MainWindow", "PID", Q_NULLPTR));
        label_Kp->setText(QApplication::translate("MainWindow", "Kp=", Q_NULLPTR));
        l_Kp->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        label_Ki->setText(QApplication::translate("MainWindow", "Ki=", Q_NULLPTR));
        l_Ki->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        label_Kd->setText(QApplication::translate("MainWindow", "Kd=", Q_NULLPTR));
        l_Kd->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        rb_c_custom->setText(QApplication::translate("MainWindow", "Contrador personalizado", Q_NULLPTR));
        b_e_c_custom->setText(QApplication::translate("MainWindow", "Explorar", Q_NULLPTR));
        label_ref_fut->setText(QApplication::translate("MainWindow", "Referencias futuras disponibles:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_controlador), QApplication::translate("MainWindow", "Controlador", Q_NULLPTR));
        cb_t_final->setText(QApplication::translate("MainWindow", "Detener experimento despues de:", Q_NULLPTR));
        timeEdit_duracion->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", Q_NULLPTR));
        b_usar_t_val->setText(QApplication::translate("MainWindow", "Largo de archivo", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_tiempo), QApplication::translate("MainWindow", "Duracion", Q_NULLPTR));
        te_resumen->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PibotoLt'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Controlador:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Sensores:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Referencia:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Tiempo de experimento:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0"
                        "px;\">Tiempo de muestreo:</p></body></html>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_resumen), QApplication::translate("MainWindow", "Resumen", Q_NULLPTR));
        b_iniciar->setText(QApplication::translate("MainWindow", "Iniciar", Q_NULLPTR));
        b_detener->setText(QApplication::translate("MainWindow", "Detener", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_supervision), QApplication::translate("MainWindow", "Supervision", Q_NULLPTR));
        cb_incluir_resumen->setText(QApplication::translate("MainWindow", "Incluir configuracion", Q_NULLPTR));
        b_exportar->setText(QApplication::translate("MainWindow", "Exportar", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_resultados), QApplication::translate("MainWindow", "Resultados", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "PT100:", Q_NULLPTR));
        label_pt100_value->setText(QApplication::translate("MainWindow", "10\302\260C", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Termocupla:", Q_NULLPTR));
        label_term_value->setText(QApplication::translate("MainWindow", "10\302\260C", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Actuador:", Q_NULLPTR));
        label_act_state->setText(QApplication::translate("MainWindow", "Desactivado", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
