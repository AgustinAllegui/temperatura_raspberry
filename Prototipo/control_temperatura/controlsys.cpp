#include "controlsys.h"

ControlSys::ControlSys(QObject *parent)
    : QObject(parent)
    , runState(false)
{

}

void ControlSys::setDuracion(const double duracion_)
{
    DTRACE("set duracion" << duracion_);
    duracion = duracion_;
}

bool ControlSys::isRuning()
{
    return runState;
}

void ControlSys::controlTic()
{
    DTRACE("Control TIC");
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

    DDEBUG("t =" << timeSinceStart);
    DDEBUG("t_limite" << duracion);
    DDEBUG("temperatura =" << tempValue);
    DDEBUG("referencia =" << refValue);
    DDEBUG("salida =" << salidaValue);

    timeSinceStart += TsContainer::Ts;
    if(duracion != 0){
        if(timeSinceStart >= duracion){
            controlStop();
        }
    }
}

bool ControlSys::controlStart()
{
    DTRACE("Control system: Control start");
    timeSinceStart = 0;
    if(!referencia->verificar()){
        DERROR("referencia no verificada");
        emit s_control_stop();
        return false;
    }
    DDEBUG("referencia verificada");
    if(!algoritmo->verificar()){
        DERROR("Algoritmo no verificado");
        emit s_control_stop();
        return false;
    }
    DDEBUG("algoritmo verificado");
    algoritmo->limpiarScope();
    DDEBUG("scope de octave limpiado");
    salida->config(1);
    runState = true;
    controlTic();
    return true;
}

void ControlSys::controlStop()
{
    salida->setOutput(0);
    runState = false;
    emit s_control_stop();
}
