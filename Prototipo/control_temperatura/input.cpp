#include "input.h"

Input_base::Input_base()
{

#if CURRENT_DEVICE == ON_PC
    direccion = ENTRADA_FILE_DIR;
#endif
    lastValue = 0;
}

double Input_base::readLast()
{
    return lastValue;
}

//leer desde texto
#if CURRENT_DEVICE == ON_PC

/*leer del archivo pt100.txt
 */
double Input_base::read()
{
//    DTRACE("input read from text");
    QFile archivo(direccion);
    if(!archivo.open(QFile::ReadOnly)){
        DERROR("no se pudo abrir archivo de lectura");
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
#elif CURRENT_DEVICE == ON_RASPBERRY

double Input_base::read()
{
    DERROR("intento de lectura en Input Base");
    lastValue = -1;
    return -1;
}

#endif

/*-------------------------------------------------------------------------------
 * Input ph
 */

Input_ph::Input_ph()
{
#if CURRENT_DEVICE == ON_PC
    direccion = "/home/pi/Documents/Files/Pruebas/ph1.txt";
#endif
}

double Input_ph::read()
{
    lastValue = -1;
    return 7;
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

//    //DDEBUG(QString("lectura crudo %1 %2").arg(lectura[0],8,2,QLatin1Char('0')).arg(lectura[1],8,2,QLatin1Char('0')));

    if(lectura[1] & 0b00000100){
        DERROR("termocupla no conectada");
        return -1;
    }

    uint16_t lectura16 = 0;
    lectura16 += lectura[0];
    lectura16 = lectura16<<8;
    lectura16 += lectura[1];

//    //DDEBUG(QString("lectura junta %1").arg(lectura16,16,2,QLatin1Char('0')));

    lectura16 &= 0b0111111111111000;
    lectura16 = lectura16 >>3;
//    //DDEBUG(QString("lectura uint16_t %1").arg(lectura16,16,2,QLatin1Char('0')));

    double temperatura = lectura16;
//    //DDEBUG("lectura:" << lectura16);
//    //DDEBUG("temperatura:" << temperatura);
    temperatura = temperatura/4;
    DDEBUG("temperatura Termocupla:" << temperatura);

    lastValue = temperatura;
    emit s_inputTermocupla_read(temperatura);
    return temperatura;
}

#endif

/*-------------------------------------------------------------------------------
 * Input PT100
 */

InputPT100::InputPT100()
{
#if CURRENT_DEVICE == ON_RASPBERRY
    //inicializar pines de comunicacion SPI
    pinMode(PIN_PT100_MOSI, OUTPUT);
    pinMode(PIN_PT100_MISO, INPUT);
    pinMode(PIN_PT100_CLK, OUTPUT);
    pinMode(PIN_PT100_CS, OUTPUT);

    digitalWrite(PIN_PT100_CLK, LOW);
    digitalWrite(PIN_PT100_CS, HIGH);

    uint8_t reg0 = leerRegistro(0x00);
    //configurar para 3 cables
    reg0 |= 0x10;

    //habilitar alimentacion de PT100 (Bias)
    reg0 |= 0x80;

    //deshabilitar autoconversion
    reg0 &= ~0x40;

    escribirRegistro(0x80, reg0);

    limpiarFallas();

#endif
}

#if CURRENT_DEVICE == ON_RASPBERRY

double InputPT100::read()
{
    DTRACE("lectura de PT100");

    limpiarFallas();

    //realizar una lectura (one shot)
    uint8_t reg0 = leerRegistro(0x00);
    DDEBUG(QString("reg0: %1").arg(reg0, 8, 2, QLatin1Char('0')));
    if(reg0 != 0b10010000){
        escribirRegistro(0x80, 0b10010000);
        reg0 = 0b10010000;
    }
    reg0 |= 0x20;
    escribirRegistro(0x80, reg0);

    //retardo de 65ms mientras se realiza la medicion
    delay(65);

    //leer el resultado
    uint8_t rtdLow, rtdHigh;
    uint16_t rtd = 0;

    digitalWrite(PIN_PT100_CLK, LOW);
    digitalWrite(PIN_PT100_CS, LOW);
    spiTransfer(0x01);
    rtdHigh = spiTransfer(0xFF);
    rtdLow = spiTransfer(0xFF);
    digitalWrite(PIN_PT100_CS, HIGH);

    rtd = rtdHigh;
    rtd <<= 8;

    rtd |= rtdLow;
    DDEBUG("lectura reg rtd:" << rtd);

    if(rtd & 0x01){
        DERROR("Falla en la lectura de PT100" << leerFalla());
        return -1;
    }
    rtd >>= 1;  //quitar bit de falla de lectura
    DDEBUG("rtd:" << rtd);

    //convertir lectura en temperatura
    double Rt = rtd;
    Rt /= 32768;
    Rt *= PT100_R_REF;

    double Z1 = -PT100_RTD_A;
    double Z2 = PT100_RTD_A * PT100_RTD_A - (4 * PT100_RTD_B);
    double Z3 = (4 * PT100_RTD_B) / PT100_R_NOMINAL;
    double Z4 = 2 * PT100_RTD_B;

    double temperatura = Z2 + (Z3 * Rt);
    temperatura = (sqrt(temperatura) + Z1) / Z4;

    DDEBUG("temperatura PT100:" << temperatura);
    if(temperatura >= 0){
        lastValue = temperatura;
        emit s_inputPT100_read(temperatura);
        return temperatura;
    }

    //ugh (?)
    Rt /= PT100_R_NOMINAL;
    Rt *= 100;

    double rpoly = Rt;

    temperatura = -242.02;
    temperatura += 2.2228 * rpoly;
    rpoly *= Rt;  // square
    temperatura += 2.5859e-3 * rpoly;
    rpoly *= Rt;  // ^3
    temperatura -= 4.8260e-6 * rpoly;
    rpoly *= Rt;  // ^4
    temperatura -= 2.8183e-8 * rpoly;
    rpoly *= Rt;  // ^5
    temperatura += 1.5243e-10 * rpoly;

    DDEBUG("temperatura PT100 2:" << temperatura);
    lastValue = temperatura;
    emit s_inputPT100_read(temperatura);
    return temperatura;

}



uint8_t InputPT100::spiTransfer(uint8_t data)
{
    uint8_t reply = 0;

    for(int i = 7; i>=0;  i--){
        reply <<=1;
        digitalWrite(PIN_PT100_CLK, HIGH);
        digitalWrite(PIN_PT100_MOSI, data&(1<<i));
        digitalWrite(PIN_PT100_CLK, LOW);
        if(digitalRead(PIN_PT100_MISO)){
            reply |= 1;
        }
    }
    return reply;
}


uint8_t InputPT100::leerRegistro(uint8_t direccion)
{
    direccion &= 0x7F;

    digitalWrite(PIN_PT100_CLK, LOW);
    digitalWrite(PIN_PT100_CS, LOW);

    spiTransfer(direccion);
    uint8_t respuesta = spiTransfer(0xFF);

    digitalWrite(PIN_PT100_CS, HIGH);

    return respuesta;
}

void InputPT100::escribirRegistro(uint8_t direccion, uint8_t valor)
{
    direccion |= 0x80;

    digitalWrite(PIN_PT100_CLK, LOW);
    digitalWrite(PIN_PT100_CS, LOW);

    spiTransfer(direccion);
    spiTransfer(valor);

    digitalWrite(PIN_PT100_CS, HIGH);
}

void InputPT100::limpiarFallas()
{
    uint8_t t = leerRegistro(0x00);
    t &= ~0x2C;
    t |= 0x02;
    escribirRegistro(0x00, t);
}

uint8_t InputPT100::leerFalla()
{
    return leerRegistro(0x07);
}


#endif


