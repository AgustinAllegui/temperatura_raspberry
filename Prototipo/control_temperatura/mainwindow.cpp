#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    entrada_refresh_time(5000)
{
    D_INFO("Controlador de temperatura");
    D_INFO("Version" << NUMERO_VERSION);
    ui->setupUi(this);

    showMaximized();
    pinMode(PIN_LED_APP, OUTPUT);
    digitalWrite(PIN_LED_APP, HIGH);
    doConections();
    configureStopBouton();
    setInitialValues();
    configureTempLimit();


    //dibujar el ultimo resultado en resultados
    ui->g_resultados->showAll(logger.getTiempo(), logger.getRef(), logger.getTemperatura(), logger.getU());

}

MainWindow::~MainWindow()
{
    if(controlSys.isRuning()) OutRele.emergencyStop();
    pinMode(PIN_LED_APP,LOW);
    delete ui;
}

void MainWindow::doConections()
{
    //tickers
    connect(&entradas_ticker, SIGNAL(timeout()), this, SLOT(slot_entradas_ticker_timeout()));
    entradas_ticker.start(entrada_refresh_time);

    control_ticker.setTimerType(Qt::PreciseTimer);
    connect(&control_ticker, SIGNAL(timeout()), this, SLOT(slot_control_ticker_timeout()));

    //control tic
    connect(&controlSys, SIGNAL(s_control_data(double, double, double, double, double)),
            this, SLOT(slot_controlSys_s_control_data(double, double, double, double, double)));

    //control end
    connect(&controlSys, SIGNAL(s_control_stop()), this, SLOT(slot_control_stoped()));

    //conectar lectura de sensores a mensajes en pantalla
#if CURRENT_DEVICE == ON_RASPBERRY
    connect(&pt100, SIGNAL(s_inputPT100_read(double)), this, SLOT(slot_lecturaPT100(double)));
    connect(&termocupla, SIGNAL(s_inputTermocupla_read(double)), this, SLOT(slot_lecturaTermocupla(double)));
#endif

    //conectar señales de salida a mensajes en pantalla
    connect(&OutRele, SIGNAL(s_outputChange(bool)), this, SLOT(slot_output_rele_state_changed(bool)));
    connect(&OutRele, SIGNAL(s_outputValueChange(double)), this, SLOT(slot_output_value_changed(double)));

    //conectar señales de limite de temperatura
    connect(&pt100, SIGNAL(s_inputPT100_safeLimitReached()), this, SLOT(slot_safeLimitReached()));
    connect(&termocupla, SIGNAL(s_inputTermocupla_safeLimitReached()), this, SLOT(slot_safeLimitReached()));

}

void MainWindow::configureStopBouton()
{
    InterruptCallbackHandler::callToEmit(&interruptEmitter);
    connect(&interruptEmitter, SIGNAL(s_interrupt()), this, SLOT(on_b_detener_clicked()));
}

void MainWindow::setInitialValues()
{
    controlSys.salida = &OutRele;
    ui->l_ts->setText("10");
    on_l_ts_editingFinished();

    ui->rb_PT100->setChecked(true);
    //ui->cb_sensor_ph->setChecked(false);
    on_cb_sensor_ph_toggled(false);

    ui->l_ref_simple->setText("50+50*sin(2*pi*t*(1/100))");
    ui->rb_ref_simple->setChecked(true);

    ui->l_Kp->setText("5");
    ui->l_Ki->setText("1");
    ui->l_Kd->setText("0");
    ui->rb_PID->setChecked(true);

    ui->cb_t_final->setChecked(false);
}

void MainWindow::configureTempLimit()
{
    QFile archivo(CONFIG_DIR);
    QMessageBox error;
    error.setIcon(QMessageBox::Critical);
    if(!archivo.exists()){
        D_ERROR("no se encontro archivo de configuracion");
        error.setText("Error: no se encontro el archivo de configuracion config.ini");
        error.exec();
        return;
    }

    if(!archivo.open(QFile::ReadOnly | QFile::Text)){
        D_ERROR("no se pudo abrir el archivo de configuracion");
        error.setText("Error: no se pudo abrir el archivo config.ini");
        error.exec();
        return;
    }

    //escanear el archivo buscando las configuraciones
    QString reglon;
    double valorEncontrado;
    archivo.seek(0);

    while(!archivo.atEnd()){
        reglon = archivo.readLine();
        if(reglon.startsWith(';')){
            continue;
        }

        //buscar el limite de seguridad de la PT100
        if(reglon.startsWith("PT100-limite")){
            valorEncontrado = reglon.split('=').at(1).toDouble();
            pt100.setSafeLimit(valorEncontrado);
            ui->label_PT100_safeLimit->setText(QString::number(valorEncontrado, 'f', 0).append("°C"));
        }

        //buscar el limite de seguridad de la termocupla
        if(reglon.startsWith("termocupla-limite")){
            valorEncontrado = reglon.split('=').at(1).toDouble();
            termocupla.setSafeLimit(valorEncontrado);
            ui->label_Termocupla_safeLimit->setText(QString::number(valorEncontrado, 'f', 0).append("°C"));
        }
    }


}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// configuracion del controlador

// configuraciones de pestaña "Muestreo"

void MainWindow::on_l_ts_editingFinished()
{
    D_TRACE("Ts editado");
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
    D_TRACE("actualizar Referencia simple");
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
    ui->label_prot_ref->setEnabled(checked);

    //configurar referencia
    if(checked){
        if(!ui->l_dir_c_custom->text().isEmpty()){
            on_l_dir_ref_fun_editingFinished();
        }
    }
}

void MainWindow::on_b_e_ref_fun_clicked()
{
    CONTROL_MODIFY_CHECK;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir referencia en funcion *.m"), "~/Documents/", tr("m file (*.m)"));
    ui->l_dir_ref_fun->setText(fileName);
    on_l_dir_ref_fun_editingFinished();
}

void MainWindow::on_l_dir_ref_fun_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    controlSys.referencia = &refCustom;
    refCustom.setFile(ui->l_dir_ref_fun->text());
    //D_DEBUG("Referencia de funcion actualizada");
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


    //configurar referencia
    if(checked){
        if(!ui->l_dir_ref_val->text().isEmpty()){
            on_l_dir_ref_val_editingFinished();
        }
    }
}

void MainWindow::on_b_e_ref_val_clicked()
{
    CONTROL_MODIFY_CHECK;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir referencia en valores *.txt"), "~/Documents/", tr("archivo de texto (*.txt)"));
    ui->l_dir_ref_val->setText(fileName);
    on_l_dir_ref_val_editingFinished();
}

void MainWindow::on_l_dir_ref_val_editingFinished()
{
    CONTROL_MODIFY_CHECK;
    controlSys.referencia = &refValores;
    refValores.setFile(ui->l_dir_ref_val->text());
    refValores.verificar();
    //D_DEBUG("Referencia de valores actualizada");
    if(ui->rb_end_mantener->isChecked()){
        refValores.setEndAction(Ref_valores::Mantener);
    }else if(ui->rb_end_0->isChecked()){
        refValores.setEndAction(Ref_valores::Cero);
    }else if(ui->rb_end_repetir->isChecked()){
        refValores.setEndAction(Ref_valores::Repetir);
    }
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
        if(!ui->l_dir_c_custom->text().isEmpty()){
            on_l_dir_c_custom_editingFinished();
        }
    }
}

void MainWindow::on_b_e_c_custom_clicked()
{
    CONTROL_MODIFY_CHECK;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir algoritmo personalizado"), "~/Documents/", tr("m file (*.m)"));
    ui->l_dir_c_custom->setText(fileName);
    on_l_dir_c_custom_editingFinished();
}

void MainWindow::on_l_dir_c_custom_editingFinished()
{
    D_TRACE("Direccion de controlador editada");
    CONTROL_MODIFY_CHECK;
    controlSys.algoritmo = &algoritmoCustom;
    algoritmoCustom.setFileDir(ui->l_dir_c_custom->text());
    //D_DEBUG("Algoritmo actualizado");
}

void MainWindow::on_sb_future_ref_valueChanged(int arg1)
{
    CONTROL_MODIFY_CHECK;
    algoritmoCustom.setN_fut(arg1);
    ui->label_prot_cont->setText((arg1 >= 0)?
                                     "function u = UisR_fut(Ts, t, ref0, temp1, futRef)"
                                   : "function u = algoritmo(Ts, t, ref0, temp)");
}


// configuracion de pestaña "duracion"

void MainWindow::on_cb_t_final_toggled(bool checked)
{
    D_TRACE("Modificar duracion");
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
    //D_DEBUG("largo double" << largo);
    double duracion = TsContainer::Ts * largo;
    //D_DEBUG("duracion double" << duracion);

    int duracion_int = (int) duracion +1;
    //D_DEBUG("duracion int" << duracion_int);
    ui->timeEdit_duracion->setTime(QTime(0,0).addSecs(duracion_int));
}


// cambio de pestaña

void MainWindow::on_tabWidget_currentChanged(int index)
{
    D_TRACE("cambio de pestaña" << ui->tabWidget->tabText(index));
    if(ui->tabWidget->tabText(index) == "Resumen"){
        //escribir resumen
        if(!controlSys.isRuning()){
            ui->te_resumen->clear();
            ui->te_resumen->append(generarResumen());
        }
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
        resumen.append("\nLimite de seguridad: ");
        resumen.append(ui->label_Termocupla_safeLimit->text());
    }else if(ui->rb_PID->isChecked()){
        resumen.append("PT100");
        resumen.append("\nLimite de seguridad: ");
        resumen.append(ui->label_PT100_safeLimit->text());
    }

//    if(ui->cb_sensor_ph->isChecked()){
//        resumen.append("\nSensor de PH habilitado");
//    }

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

// Supervision

void MainWindow::on_b_iniciar_clicked()
{
    D_TRACE("on_b_iniciar_clocked");

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
//        algoritmoCustom.setPh_flag(ui->cb_sensor_ph->isChecked());
        algoritmoCustom.setPh_flag(false);
        algoritmoCustom.setN_fut(ui->sb_future_ref->text().toInt());
    }else if(ui->rb_PID->isChecked()){
        controlSys.algoritmo = &algoritmoPID;
    }

    if(ui->rb_PT100->isChecked()){
        controlSys.sensor = &pt100;
    }else if(ui->rb_term->isChecked()){
        controlSys.sensor = &termocupla;
    }

    logger.clear();

    on_b_dibujarRef_clicked();

    if(!controlSys.controlStart()){
        D_LOG("sistema de control no iniciado");
        QMessageBox mensajeError;
        mensajeError.setText("Error: no se pudo iniciar el experimento");
        mensajeError.setIcon(QMessageBox::Critical);
        mensajeError.exec();
        ui->b_iniciar->setEnabled(true);
        return;
    }

    D_LOG("sistema de control iniciado");

    ui->b_detener->setEnabled(true);
    ui->b_dibujarRef->setEnabled(false);
    ui->tab_ts->setEnabled(false);
    ui->tab_tiempo->setEnabled(false);
    ui->tab_sensor->setEnabled(false);
    ui->tab_resultados->setEnabled(false);
    ui->tab_referencia->setEnabled(false);
    ui->tab_controlador->setEnabled(false);
    //detener el timer de lectura
    entradas_ticker.stop();
    //iniciar el timer
    int Ts_ms = TsContainer::Ts * 1000;
    control_ticker.start(Ts_ms);

    D_LOG("tickers iniciados");
}

void MainWindow::on_b_detener_clicked()
{
    controlSys.controlStop();
}

void MainWindow::on_b_dibujarRef_clicked()
{
    //dibujar referencia si no esta iniciado
//    ui->g_supervision->rearmar(ui->cb_sensor_ph->isChecked());
    ui->g_supervision->rearmar(false);
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


// Resulatados

void MainWindow::on_b_exportar_clicked()
{
    QString selectedFilter;
    QString fileDir = QFileDialog::getSaveFileName(this,
                                                   tr("guardar datos del ensayo"),
                                                   "~/Documents/",
                                                   tr("Texto (*.txt);;Valores separados por coma (*.csv);;Archivo de valores de MatLab (*.mat)"),
                                                   &selectedFilter;
                                                   );
    if(!fileDir.isEmpty()){
        if(selectedFilter.contains(".txt")){
            if(!fileDir.endsWith(".txt")){
                fileDir.append(".txt");
            }
        }else if(selectedFilter.contains(".csv")){
            if(!fileDir.endsWith(".csv")){
                fileDir.append(".csv");
            }
        }else if(selectedFilter.contains(".mat")){
            if(!fileDir.endsWith(".mat")){
                fileDir.append(".mat");
            }
        }
    }else{
        return;
    }
    logger.saveFile(fileDir, controlSys.algoritmo->getPh_flag());
}


//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Funcionamiento del sistema de control

void MainWindow::slot_entradas_ticker_timeout()
{
    pt100.read();
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
    ui->b_dibujarRef->setEnabled(true);

    ui->tab_ts->setEnabled(true);
    ui->tab_tiempo->setEnabled(true);
    ui->tab_sensor->setEnabled(true);
    ui->tab_resultados->setEnabled(true);
    ui->tab_referencia->setEnabled(true);
    ui->tab_controlador->setEnabled(true);

    ui->g_resultados->limpiar();
    if(controlSys.algoritmo->getPh_flag()){
        ui->g_resultados->showAll(logger.getTiempo(), logger.getRef(), logger.getTemperatura(), logger.getU(), logger.getPh());
    }else{
        ui->g_resultados->showAll(logger.getTiempo(), logger.getRef(), logger.getTemperatura(), logger.getU());
    }

}

void MainWindow::slot_controlSys_s_control_data(double t_, double ref_, double temp_, double u_, double ph_)
{
    //agregar al grafico
    if(controlSys.algoritmo->getPh_flag()){
        ui->g_supervision->addPhPoint(t_, ph_);
    }
    ui->g_supervision->addPoint(t_, ref_, temp_, u_);

    //agregar al log
    logger.addPoint(t_, ref_, temp_, u_, ph_);
}

//slots para mostrar valores en pantalla

void MainWindow::slot_lecturaPT100(double temperatura)
{
    if(temperatura == -1){
        ui->label_pt100_value->setText("NC");
        return;
    }

    ui->label_pt100_value->setText(QString::number(temperatura, 'f', 2).append("°C"));
}

void MainWindow::slot_lecturaTermocupla(double temperatura)
{
    if(temperatura == -1){
        ui->label_term_value->setText("NC");
    }
    ui->label_term_value->setText(QString::number(temperatura, 'f', 2).append("°C"));
}

void MainWindow::slot_output_rele_state_changed(bool activated)
{
    if(activated){
        ui->label_act_state->setText("Activado");
    }else{
        ui->label_act_state->setText("Desactivado");
    }
}

void MainWindow::slot_output_value_changed(double valor)
{
    ui->label_act_value->setText(QString::number(valor, 'f', 1).append('%'));
}

/* se alcanzo el limite de temperatura programado para un sensor
 *  detener el experimento inmediatamente
 */
void MainWindow::slot_safeLimitReached()
{
    on_b_detener_clicked();
    QMessageBox mensajeError;
    mensajeError.setText("Se alcanzo el limite de temperatura"
                         "El experimento se detuvo para evitar daños");
    mensajeError.setIcon(QMessageBox::Warning);
    mensajeError.exec();

}
