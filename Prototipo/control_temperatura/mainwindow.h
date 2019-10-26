#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

#include "dev_op.h"

#include "tscontainer.h"
#include "controlsys.h"
#include "input.h"
#include "referencia.h"
#include "output_rele.h"


#define CONTROL_MODIFY_CHECK do{                                                                                                \
    if(controlSys.isRuning()){                                                                                                  \
        DERROR("no modifique la configuracion");                                                                           \
        QMessageBox dontModify;                                                                                                 \
        dontModify.setText("Advertencia: no modifique la configuracion del controlador mientras se ejecuta un experimento");    \
        dontModify.setIcon(QMessageBox::Critical);                                                                              \
        dontModify.exec();                                                                                                      \
        return;                                                                                                                 \
    }                                                                                                                           \
    }while(0)


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
    void on_l_ts_editingFinished();

    void on_rb_PT100_toggled(bool checked);
    void on_rb_term_toggled(bool checked);
    void on_cb_sensor_ph_toggled(bool checked);

    void on_rb_ref_simple_toggled(bool checked);
    void on_l_ref_simple_editingFinished();
    void on_rb_ref_fun_toggled(bool checked);
    void on_b_e_ref_fun_clicked();
    void on_l_dir_ref_fun_editingFinished();
    void on_rb_ref_val_toggled(bool checked);
    void on_b_e_ref_val_clicked();
    void on_l_dir_ref_val_editingFinished();
    void on_rb_end_mantener_toggled(bool checked);
    void on_rb_end_0_toggled(bool checked);
    void on_rb_end_repetir_toggled(bool checked);

    void on_rb_PID_toggled(bool checked);
    void on_l_Kp_editingFinished();
    void on_l_Ki_editingFinished();
    void on_l_Kd_editingFinished();
    void on_rb_c_custom_toggled(bool checked);
    void on_b_e_c_custom_clicked();
    void on_l_dir_c_custom_editingFinished();
    void on_sb_future_ref_valueChanged(int arg1);

    void on_timeEdit_duracion_timeChanged(const QTime &time);
    void on_cb_t_final_toggled(bool checked);
    void on_b_usar_t_val_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_b_iniciar_clicked();
    void on_b_detener_clicked();

    void slot_entradas_ticker_timeout();
    void slot_control_ticker_timeout();
    void slot_control_stoped();

    void slot_controlSys_s_control_data(double t_, double ref_, double temp_, double u_, double ph_);


private:
    Ui::MainWindow *ui;

    //sistema de control
    ControlSys controlSys;

    TsContainer tsContainer;

    InputPT100 pt100;
    InputTermocupla termocupla;
    Input_ph phMeter;

    Ref_valores refValores;
    Ref_funcionC refCustom;
    Ref_funcionS refSimple;

    Algoritmo_base algoritmoCustom;
    Algoritmo_pid algoritmoPID;

    Output_rele OutRele;

    //timers
    QTimer entradas_ticker;
    QTimer control_ticker;

    //metodos privados
    QString generarResumen();
    void setInitialValues();
    void doConections();

    //variables privadas
    const int entrada_refresh_time; //ms

};

#endif // MAINWINDOW_H
