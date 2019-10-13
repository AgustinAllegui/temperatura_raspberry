#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "dev_op.h"

#define PC_RASPBERRY_PI 0
#define PC_NOTEBOOK     1

#define CURRENT_PC PC_RASPBERRY_PI
//#define CURRENT_PC PC_NOTEBOOK


#if (CURRENT_PC == PC_RASPBERRY_PI)

#include <wiringPi.h>
#include <wiringPiSPI.h>

#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_l_in_returnPressed();
    void on_b_enviar_clicked();
    void on_b_limpiar_clicked();

private:
    Ui::MainWindow *ui;

    int pinCs0;
    int pinCs1;


};

#endif // MAINWINDOW_H
