#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    entrada_refresh_time(5000)
{
    ui->setupUi(this);
    doConections();
    setInitialValues();

    //iniciar timer entradas
}

MainWindow::~MainWindow()
{
    if(controlSys.isRuning()) OutRele.emergencyStop();
    delete ui;
}

void MainWindow::doConections()
{
    //tickers
    control_ticker.setTimerType(Qt::PreciseTimer);
    connect(&entradas_ticker, SIGNAL(timeout()), this, SLOT(slot_entradas_ticker_timeout()));
    connect(&control_ticker, SIGNAL(timeout()), this, SLOT(slot_control_ticker_timeout()));
    entradas_ticker.start(entrada_refresh_time);

    //control tic
    connect(&controlSys, SIGNAL(s_control_data(double,double,double,double)), this, SLOT(slot_controlSys_s_control_data(double,double,double,double)));

    //control end
    connect(&controlSys, SIGNAL(s_control_stop()), this, SLOT(slot_control_stoped()));
}

void MainWindow::setInitialValues()
{
    controlSys.salida = &OutRele;
    ui->l_ts->setText("10");
    on_l_ts_editingFinished();

    ui->rb_PT100->setChecked(true);
    ui->cb_sensor_ph->setChecked(false);

    ui->l_ref_simple->setText("0.2*t/Ts");
    ui->rb_ref_simple->setChecked(true);

    ui->l_Kp->setText("5");
    ui->l_Ki->setText("1");
    ui->l_Kd->setText("0");
    ui->rb_PID->setChecked(true);

    ui->cb_t_final->setChecked(false);
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// configuracion del controlador

// configuraciones de pestaña "Muestreo"

void MainWindow::on_l_ts_editingFinished()
{
    DTRACE("Ts editado");
    CONTROL_MODIFY_CHECK;
    tsContainer.Ts = ui->l_ts->text().toDouble();
}

// configuraciones de pestaña "Sensor"

void MainWindow::on_rb_PT100_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    // configurar controlador
    if(checked){
        controlSys.sensor = &pt100;
    }
}

void MainWindow::on_rb_term_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    //configurar controlador
    if(checked){
        controlSys.sensor = &termocupla;
    }
}

void MainWindow::on_cb_sensor_ph_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    //configurar controlador
    controlSys.sensor_ph = &phMeter;
    algoritmoCustom.setPh_flag(checked);
}

// configuraciones de pestaña "Referencia"

void MainWindow::on_rb_ref_simple_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    ui->label_ref_simple->setEnabled(checked);
    ui->l_ref_simple->setEnabled(checked);

    if(checked){
        //configurar controlador
        controlSys.referencia = &refSimple;
        on_l_ref_simple_editingFinished();
    }
}

void MainWindow::on_l_ref_simple_editingFinished()
{
    DTRACE("actualizar Referencia simple");
    CONTROL_MODIFY_CHECK;
    // configurar referencia simple
    refSimple.setFunction(ui->l_ref_simple->text(), REF_SIMPLE_DIR);
    refSimple.verificar();
}

void MainWindow::on_rb_ref_fun_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    ui->l_dir_ref_fun->setEnabled(checked);
    ui->b_e_ref_fun->setEnabled(checked);
    if(checked){
        //configurar controlador
        controlSys.referencia = &refCustom;
        refCustom.setFile(ui->l_dir_ref_fun->text());
    }
}

void MainWindow::on_b_e_ref_fun_clicked()
{
    CONTROL_MODIFY_CHECK;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir referencia en funcion *.m"), "~/", tr("m file (*.m)"));
    ui->l_dir_ref_fun->setText(fileName);
    on_l_dir_ref_fun_editingFinished();
}

void MainWindow::on_l_dir_ref_fun_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    refCustom.setFile(ui->l_dir_ref_fun->text());
    DDEBUG("Referencia de funcion actualizada");
}

void MainWindow::on_rb_ref_val_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    ui->l_dir_ref_val->setEnabled(checked);
    ui->b_e_ref_val->setEnabled(checked);
    ui->label_end->setEnabled(checked);
    ui->rb_end_0->setEnabled(checked);
    ui->rb_end_mantener->setEnabled(checked);
    ui->rb_end_repetir->setEnabled(checked);

    if(ui->cb_t_final->isChecked() && checked){
        ui->b_usar_t_val->setEnabled(true);
    }else{
        ui->b_usar_t_val->setEnabled(false);
    }


    if(checked){
        //configurar controlador
        controlSys.referencia = &refValores;
        refValores.setFile(ui->l_dir_ref_val->text());
        if(ui->rb_end_mantener->isChecked()){
            refValores.setEndAction(Ref_valores::Mantener);
        }else if(ui->rb_end_0->isChecked()){
            refValores.setEndAction(Ref_valores::Cero);
        }else if(ui->rb_end_repetir->isChecked()){
            refValores.setEndAction(Ref_valores::Repetir);
        }
    }
}

void MainWindow::on_b_e_ref_val_clicked()
{
    CONTROL_MODIFY_CHECK;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir referencia en valores *.txt"), "~/", tr("archivo de texto (*.txt)"));
    ui->l_dir_ref_val->setText(fileName);
    on_l_dir_ref_val_editingFinished();
}

void MainWindow::on_l_dir_ref_val_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    refValores.setFile(ui->l_dir_ref_val->text());
    refValores.verificar();
    DDEBUG("Referencia de valores actualizada");
}

void MainWindow::on_rb_end_mantener_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    // configuracion de referencia de valores
    if(checked){
        refValores.setEndAction(Ref_valores::Mantener);
    }
}

void MainWindow::on_rb_end_0_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    // configuracion de referencia de valores
    if(checked){
        refValores.setEndAction(Ref_valores::Cero);
    }
}

void MainWindow::on_rb_end_repetir_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    // configuracion de referencia de valores
    if(checked){
        refValores.setEndAction(Ref_valores::Repetir);
    }
}


// configuracion de la pestaña "Controlador"

void MainWindow::on_rb_PID_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    ui->label_Kp->setEnabled(checked);
    ui->label_Ki->setEnabled(checked);
    ui->label_Kd->setEnabled(checked);
    ui->l_Kp->setEnabled(checked);
    ui->l_Ki->setEnabled(checked);
    ui->l_Kd->setEnabled(checked);
    if(checked){
        //configurar controlador
        controlSys.algoritmo = &algoritmoPID;
        algoritmoPID.setPID(ui->l_Kp->text().toDouble(), ui->l_Ki->text().toDouble(), ui->l_Kd->text().toDouble());
    }
}

void MainWindow::on_l_Kp_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    on_l_Kd_editingFinished();
}
void MainWindow::on_l_Ki_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    on_l_Kd_editingFinished();
}
void MainWindow::on_l_Kd_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    algoritmoPID.setPID(ui->l_Kp->text().toDouble(), ui->l_Ki->text().toDouble(), ui->l_Kd->text().toDouble());
}


void MainWindow::on_rb_c_custom_toggled(bool checked)
{
    CONTROL_MODIFY_CHECK;
    ui->l_dir_c_custom->setEnabled(checked);
    ui->b_e_c_custom->setEnabled(checked);
    ui->label_ref_fut->setEnabled(checked);
    ui->sb_future_ref->setEnabled(checked);
    if(checked){
        //configurar controlador
        controlSys.algoritmo = &algoritmoCustom;
        algoritmoCustom.setFileDir(ui->l_dir_c_custom->text());
    }
}

void MainWindow::on_b_e_c_custom_clicked()
{
    CONTROL_MODIFY_CHECK;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir algoritmo personalizado"), "~/", tr("m file (*.m)"));
    ui->l_dir_c_custom->setText(fileName);
    on_l_dir_c_custom_editingFinished();
}

void MainWindow::on_l_dir_c_custom_editingFinished()
{
    DTRACE("Direccion de controlador editada");
    CONTROL_MODIFY_CHECK;
    algoritmoCustom.setFileDir(ui->l_dir_c_custom->text());
    DDEBUG("Algoritmo actualizado");
}

void MainWindow::on_sb_future_ref_valueChanged(int arg1)
{
    CONTROL_MODIFY_CHECK;
    algoritmoCustom.setN_fut(arg1);
}


// configuracion de pestaña "duracion"

void MainWindow::on_cb_t_final_toggled(bool checked)
{
    DTRACE("Modificar duracion");
    CONTROL_MODIFY_CHECK;
    ui->timeEdit_duracion->setEnabled(checked);

    if(ui->rb_ref_val->isChecked() && checked){
        ui->b_usar_t_val->setEnabled(true);
    }else{
        ui->b_usar_t_val->setEnabled(false);
    }

    double duracion;
    if(checked){
        duracion = ui->timeEdit_duracion->time().hour()*3600;
        duracion += ui->timeEdit_duracion->time().minute()*60;
        duracion += ui->timeEdit_duracion->time().second();
    }else{
        duracion = 0;
    }

    //configurar controlador
    controlSys.setDuracion(duracion);
}

void MainWindow::on_timeEdit_duracion_timeChanged(const QTime &time)
{
    if(ui->cb_t_final->isChecked()){
        double duracion = time.hour()*3600;
        duracion += time.minute()*60;
        duracion += time.second();
        controlSys.setDuracion(duracion);
    }
}

void MainWindow::on_b_usar_t_val_clicked()
{
    CONTROL_MODIFY_CHECK;
    double largo = (double) refValores.getFileLength();
    DDEBUG("largo double" << largo);
    double duracion = TsContainer::Ts * largo;
    DDEBUG("duracion double" << duracion);

    int duracion_int = (int) duracion +1;
    DDEBUG("duracion int" << duracion_int);
    ui->timeEdit_duracion->setTime(QTime(0,0).addSecs(duracion_int));
}


// cambio de pestaña

void MainWindow::on_tabWidget_currentChanged(int index)
{
    DTRACE("cambio de pestaña" << ui->tabWidget->tabText(index));
    if(ui->tabWidget->tabText(index) == "Resumen"){
        //escribir resumen
        if(!controlSys.isRuning()){
            ui->te_resumen->clear();
            ui->te_resumen->append(generarResumen());
        }
    }else if(ui->tabWidget->tabText(index) == "Supervision"){
        //dibujar referencia si no esta iniciado
        ui->g_supervision->rearmar(ui->cb_sensor_ph->isChecked());
        QVector<double> refT, refV;
        double tFinal = 10*60;
        if(ui->cb_t_final->isChecked()){
            tFinal = ui->timeEdit_duracion->time().hour()*3600;
            tFinal += ui->timeEdit_duracion->time().minute()*60;
            tFinal += ui->timeEdit_duracion->time().second();
        }
        controlSys.referencia->getInitRef(refT, refV, tFinal);
        ui->g_supervision->setRef(refV, refT);

    }
}

QString MainWindow::generarResumen()
{
    QString resumen;
    resumen = "Controlador: ";
    if(ui->rb_PID->isChecked()){
        resumen.append("PID\n"
                       "Kp=");
        resumen.append(ui->l_Kp->text());
        resumen.append("; Ki=");
        resumen.append(ui->l_Ki->text());
        resumen.append("; Kd=");
        resumen.append(ui->l_Kd->text());
    }else if(ui->rb_c_custom){
        resumen.append("Funcion en archivo\n");
        resumen.append(ui->l_dir_c_custom->text());
    }

    resumen.append("\nSensor de temperatura: ");
    if(ui->rb_term->isChecked()){
        resumen.append("Termocupla");
    }else if(ui->rb_PID->isChecked()){
        resumen.append("PT100");
    }

    if(ui->cb_sensor_ph->isChecked()){
        resumen.append("\nSensor de PH habilitado");
    }

    resumen.append("\nReferencia: ");
    if(ui->rb_ref_simple->isChecked()){
        resumen.append("R(Ts,t) = " + ui->l_ref_simple->text());
    }else if(ui->rb_ref_fun->isChecked()){
        resumen.append("Funcion en archivo\n");
        resumen.append(ui->l_dir_ref_fun->text());
    }else if(ui->rb_ref_val->isChecked()){
        resumen.append("Valores en archivo\n");
        resumen.append(ui->l_dir_ref_val->text());
    }

    resumen.append("\nTiempo de muestreo: " + ui->l_ts->text() + " segundos");

    if(ui->cb_t_final->isChecked()){
        resumen.append("\nEl experimento se detendra despues de " + ui->timeEdit_duracion->text());
    }

    return resumen;

}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Supervision


void MainWindow::on_b_iniciar_clicked()
{
    DTRACE("on_b_iniciar_clocked");

    ui->b_iniciar->setEnabled(false);

    if(ui->rb_ref_simple->isChecked()){
        controlSys.referencia = &refSimple;
    }else if(ui->rb_ref_fun->isChecked()){
        controlSys.referencia = &refCustom;
    }else if(ui->rb_ref_val->isChecked()){
        controlSys.referencia = &refValores;
    }

    if(ui->rb_c_custom->isChecked()){
        controlSys.algoritmo = &algoritmoCustom;
        algoritmoCustom.setPh_flag(ui->cb_sensor_ph->isChecked());
        algoritmoCustom.setN_fut(ui->sb_future_ref->text().toInt());
    }else if(ui->rb_PID->isChecked()){
        controlSys.algoritmo = &algoritmoPID;
    }

    if(ui->rb_PT100->isChecked()){
        controlSys.sensor = &pt100;
    }else if(ui->rb_term->isChecked()){
        controlSys.sensor = &termocupla;
    }

    if(!controlSys.controlStart()){
        DLOG("sistema de control no iniciado");
        QMessageBox mensajeError;
        mensajeError.setText("Error: no se pudo iniciar el experimento");
        mensajeError.setIcon(QMessageBox::Critical);
        mensajeError.exec();
        ui->b_iniciar->setEnabled(true);
        return;
    }

    DLOG("sistema de control iniciado");

    ui->b_detener->setEnabled(true);
    //detener el timer de lectura
    entradas_ticker.stop();
    //iniciar el timer
    int Ts_ms = TsContainer::Ts * 1000;
    control_ticker.start(Ts_ms);

    DLOG("tickers iniciados");
}

void MainWindow::on_b_detener_clicked()
{
    controlSys.controlStop();
}


void MainWindow::slot_entradas_ticker_timeout()
{
//    pt100.read();
    termocupla.read();
}

void MainWindow::slot_control_ticker_timeout()
{
    controlSys.controlTic();
}

void MainWindow::slot_control_stoped()
{
    control_ticker.stop();
    entradas_ticker.start(entrada_refresh_time);
    ui->b_detener->setEnabled(false);
    ui->b_iniciar->setEnabled(true);
}

void MainWindow::slot_controlSys_s_control_data(double t_, double ref_, double temp_, double u_, double ph_)
{
    //agregar al grafico
    if(controlSys.algoritmo->getPh_flag()){
        ui->g_supervision->addPhPoint(t_, ph_);
    }
    ui->g_supervision->addPoint(t_, ref_, temp_, u_);

    //agregar al log
}
