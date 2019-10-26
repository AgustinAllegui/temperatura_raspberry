#include "input.h"

Input_base::Input_base()
#if INPUT_VERSION == FROM_TEXT
    : direccion("/home/pi/Documents/Files/Pruebas/entrada_seno.txt")
#endif
{

}

double Input_base::readLast()
{
    return lastValue;
}

//leer desde texto
#if INPUT_VERSION == FROM_TEXT

/*leer del archivo pt100.txt
 */
double Input_base::read()
{
//    DTRACE("input read from text");
    QFile archivo(direccion);
    if(!archivo.open(QFile::ReadOnly)){
        DERROR("no se pudo abrir archivo pt100");
        return -1;
    }

    static int reglon_count = 0;

    if(archivo.atEnd()){
        DERROR("Archivo pt100 vacio");
        return -2;
    }

    QString reglon = archivo.readLine();

    for(int i = 0; i < reglon_count; i++){
        if(archivo.atEnd()){
            archivo.seek(0);
        }
        reglon = archivo.readLine();
    }

    archivo.close();

    reglon_count++;
    lastValue = reglon.toDouble();
    return lastValue;
}
#elif INPUT_VERSION == FROM_SENS

double Input_base::read()
{
    DERROR("intento de lectura en Input Base");
    return -1;
}

#endif

/*-------------------------------------------------------------------------------
 * Input ph
 */

Input_ph::Input_ph()
{
#if INPUT_VERSION == FROM_TEXT
    direccion = "/home/pi/Documents/Files/Pruebas/ph1.txt";
#endif
}


/*-------------------------------------------------------------------------------
 * Input Termocupla
 */

InputTermocupla::InputTermocupla()
{
#if CURRENT_DEVICE == ON_RASPBERRY
    //inicializar PIN_TERMOCUPLA_CS como salida y setear en alto
    pinMode(PIN_TERMOCUPLA_CS, OUTPUT);
    digitalWrite(PIN_TERMOCUPLA_CS, HIGH);
    //inicializar SPI
    pinHandler.spiInit(0, 500000);
#endif
}

#if CURRENT_DEVICE == ON_RASPBERRY
double InputTermocupla::read()
{
    DTRACE("lectura termocupla");
    unsigned char lectura[2];
    digitalWrite(PIN_TERMOCUPLA_CS, LOW);
    wiringPiSPIDataRW(0, lectura, 2);
    digitalWrite(PIN_TERMOCUPLA_CS, HIGH);

    DDEBUG(QString("lectura crudo %1 %2").arg(lectura[0],8,2,QLatin1Char('0')).arg(lectura[1],8,2,QLatin1Char('0')));

    if(lectura[1] & 0b00000100){
        DERROR("termocupla no conectada");
        return -1;
    }

    uint16_t lectura16 = 0;
    lectura16 += lectura[0];
    lectura16 = lectura16<<8;
    lectura16 += lectura[1];

    DDEBUG(QString("lectura junta %1").arg(lectura16,16,2,QLatin1Char('0')));

    lectura16 &= 0b0111111111111000;
    lectura16 = lectura16 >>3;
    DDEBUG(QString("lectura uint16_t %1").arg(lectura16,16,2,QLatin1Char('0')));

    double temperatura = lectura16;
    DDEBUG("lectura:" << lectura16);
    DDEBUG("temperatura:" << temperatura);
    temperatura = temperatura/4;
    DDEBUG("temperatura:" << temperatura);
    return temperatura;
}

#endif








