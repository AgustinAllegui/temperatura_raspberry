#include "controlsys.h"

ControlSys::ControlSys(QObject *parent)
    : QObject(parent)
    , runState(false)
{
    pinMode(PIN_LED_RUN, OUTPUT);
    digitalWrite(PIN_LED_RUN, LOW);
}

void ControlSys::setDuracion(const double duracion_)
{
    D_TRACE("set duracion" << duracion_);
    duracion = duracion_;
}

bool ControlSys::isRuning()
{
    return runState;
}

void ControlSys::controlTic()
{
    D_TRACE("Control TIC");
    if(!runState){
        qDebug() << "error: control tic con el sistema sin iniciar";
    }
    double tempValue = sensor->read();

    double phValue;
    if(algoritmo->getPh_flag()){
        phValue = sensor_ph->read();
        algoritmo->passPh(phValue);
    }else{
        phValue = 0;
    }

    double refValue;
    double futureRefValue[algoritmo->getN_fut()];
    if(algoritmo->getN_fut() == 0){
        refValue = referencia->getRef(timeSinceStart);
    }else{
        refValue = referencia->getRef(timeSinceStart, algoritmo->getN_fut(), futureRefValue);
        algoritmo->passFutureRef(futureRefValue);
    }

    double salidaValue = algoritmo->tic(timeSinceStart, refValue, tempValue);

    salidaValue = salida->setOutput(salidaValue);

    emit s_control_data(timeSinceStart, refValue, tempValue, salidaValue, phValue);

    D_LOG("t =" << timeSinceStart);
    D_LOG("t_limite" << duracion);
    D_LOG("temperatura =" << tempValue);
    D_LOG("referencia =" << refValue);
    D_LOG("salida =" << salidaValue);

    timeSinceStart += TsContainer::Ts;
    if(duracion != 0){
        if(timeSinceStart >= duracion){
            controlStop();
        }
    }
}

bool ControlSys::controlStart()
{
    D_TRACE("Control system: Control start");
    timeSinceStart = 0;
    if(!referencia->verificar()){
        D_ERROR("referencia no verificada");
        emit s_control_stop();
        return false;
    }
    //D_DEBUG("referencia verificada");
    if(!algoritmo->verificar()){
        D_ERROR("Algoritmo no verificado");
        emit s_control_stop();
        return false;
    }
    //D_DEBUG("algoritmo verificado");
    algoritmo->limpiarScope();
    //D_DEBUG("scope de octave limpiado");
    salida->config(1);
    runState = true;
    digitalWrite(PIN_LED_RUN,HIGH);
    controlTic();
    return true;
}

void ControlSys::controlStop()
{
    salida->setOutput(0);
    runState = false;
    digitalWrite(PIN_LED_RUN,LOW);
    emit s_control_stop();
}
