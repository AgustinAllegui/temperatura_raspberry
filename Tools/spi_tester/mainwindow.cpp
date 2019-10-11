#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_l_in_returnPressed()
{
    on_b_enviar_clicked();
}

void MainWindow::on_b_enviar_clicked()
{
    DTRACE("Enviar");
    //configurar canal
    int canal;
    int velocidad;
    if(ui->rb_ch0->isChecked()){
        canal = 0;
        velocidad = ui->l_speed0->text().toInt();
    }else if(ui->rb_ch1->isChecked()){
        canal = 1;
        velocidad = ui->l_speed1->text().toInt();
    }else{
        DLOG("no se selecciono ningun canal");
        return;
    }

    if( (velocidad < 500000) || (velocidad > 32000000) ){
        DLOG("Velocidad fuera de rango");
        return;
    }

    DDEBUG("canal" << canal);
    DDEBUG("velocidad" << velocidad);

#if CURRENT_PC == PC_RASPBERRY_PI
    if(wiringPiSPISetup(canal, velocidad) == -1){
        DLOG("no se pudo configurar el canal");
        return;
    }

#endif


    //convertir datos si necesario

    char in_char[ui->l_in->text().length()];
    int largo;
    QByteArray in_byteArray;

    if(ui->rb_hex->isChecked()){
        in_byteArray = QByteArray::fromHex(ui->l_in->text().toLatin1());
    }else if(ui->rb_ascii->isChecked()){
        in_byteArray = ui->l_in->text().toLatin1();
    }else{
        DLOG("Formato no seleccionado");
        return;
    }

    DDEBUG("datos a enviar" << in_byteArray);

    largo = in_byteArray.length();
    for(int i = 0; i<largo; i++){
        in_char[i] = in_byteArray[i];
    }


    int enviados = 0;

#if CURRENT_PC == PC_RASPBERRY_PI
    enviados = wiringPiSPIDataRW(canal, reinterpret_cast<unsigned char*>(in_char), largo);
#endif

    DDEBUG("cantidad de datos enviados" << enviados);

    QByteArray out_byteArray = QByteArray(in_char, largo);
    DDEBUG("out byteArray" << out_byteArray);
    DDEBUG("out byteArray hex" << out_byteArray.toHex());

    QString out_str = "";
    out_str.append(in_byteArray.toHex());
    out_str.append("->>");
    out_str.append(out_byteArray.toHex());

    ui->tb_out->append(out_str);
    ui->l_in->clear();

    return;
}



void MainWindow::on_b_limpiar_clicked()
{
    ui->tb_out->clear();
}
