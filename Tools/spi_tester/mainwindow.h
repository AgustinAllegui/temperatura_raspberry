#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dev_op.h"
//#include <wiringPi.h>
//#include <wiringPiSpi.h>

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


};

#endif // MAINWINDOW_H
