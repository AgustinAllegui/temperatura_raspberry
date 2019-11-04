#include "output_rele.h"

Output_rele::Output_rele(QObject *parent)
    : QObject(parent)
{
    output_value = 0;
    n_Ts = 1;
    salidaMinima = 0;
    salidaMaxima = 100;

    emit s_outputChange(false);

#if CURRENT_DEVICE == ON_PC
    direccion = SALIDA_FILE_DIR;
#elif CURRENT_DEVICE == ON_RASPBERRY
    pinMode(PIN_RELE, OUTPUT);
    digitalWrite(PIN_RELE, LOW);
    activeOutTimer.setSingleShot(true);
    activeOutTimer.setTimerType(Qt::PreciseTimer);
    connect(&activeOutTimer, SIGNAL(timeout()), this, SLOT(slot_activeOutTimer_timeout()));
#endif
}


//pensada para cuestiones de compatibilidad
void Output_rele::config(const int n_Ts_)
{
    n_Ts = n_Ts_;

#if CURRENT_DEVICE == ON_PC
    QFile archivo(direccion);
    if(archivo.exists()){
        archivo.remove();
    }
#endif
}


double Output_rele::setOutput(const double output_)
{
    DTRACE("set output" << output_);
    output_value = checkSaturacion(output_);

#if CURRENT_DEVICE == ON_PC   // salida a texto
    QFile archivo(direccion);
    if(!archivo.open(QFile::WriteOnly | QFile::Append)){
        //error al abrir el archivo
        DERROR("no se pudo abrir el archivo out.txt");
    }

    QByteArray byteArray;
    byteArray.append(QString::number(output_) + "\n");
//    archivo.seek(archivo.size());
    archivo.write(byteArray);
    archivo.close();

#elif CURRENT_DEVICE == ON_RASPBERRY    //salida a rele

    emit s_outputValueChange(output_value);
    if(output_value == 0){
        digitalWrite(PIN_RELE, LOW);
        emit s_outputChange(false);
    }else if(output_value == 100){
        digitalWrite(PIN_RELE, HIGH);
        emit s_outputChange(true);
    }else{
        //avtivar el rele y bajarlo cuando el timer haga timeout
        digitalWrite(PIN_RELE, HIGH);
        emit s_outputChange(true);
        //DDEBUG("tiempo timer double" << (TsContainer::Ts)*(output_value/100));
        int timerTime = int((TsContainer::Ts)*(output_value/100));
        //DDEBUG("tiempo timer" << timerTime << "Segundos");
        timerTime *= 1000;
        //DDEBUG("tiempo timer" << timerTime << "Mseg");
        activeOutTimer.start(timerTime);
    }

#endif
    return output_value;
}


void Output_rele::emergencyStop()
{
    setOutput(0);
#if CURRENT_DEVICE == ON_RASPBERRY
    digitalWrite(PIN_RELE, LOW);
#endif
}

double Output_rele::checkSaturacion(const double valor_)
{
    if(valor_ <= salidaMinima){
        return salidaMinima;
    }
    if(valor_ >= salidaMaxima){
        return salidaMaxima;
    }

    return valor_;
}

#if CURRENT_DEVICE == ON_RASPBERRY

void Output_rele::slot_activeOutTimer_timeout()
{
    digitalWrite(PIN_RELE, LOW);
    emit s_outputChange(false);
}

#endif



