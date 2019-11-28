#include "pinhandler.h"

bool PinHandler::pinInited = false;
bool PinHandler::spiCh0Inited = false;

PinHandler::PinHandler()
{
#if CURRENT_DEVICE == ON_RASPBERRY
//    if(getuid() == geteuid()){
//        D_ERROR("el programa se debe ejecutar con SUDO");
//        return;
//    }

    if(!pinInited){
        wiringPiSetup();
        pinInited = true;
    }
#endif

}


bool PinHandler::spiInit(const int channel_, const int speed_)
{
#if CURRENT_DEVICE == ON_RASPBERRY
    if(wiringPiSPISetup(channel_, speed_) == -1){
        D_ERROR("no se pudo iniciar el SPI");
        return false;
    }
    spiCh0Inited = true;
#endif
    return true;
}


//-------------------------------------------------------------------------//


InterruptCallbackHandler::InterruptCallbackHandler()
{
    wiringPiISR(PIN_BOTON_STOP, INT_EDGE_FALLING, &InterruptCallbackHandler::callBack);
}

void InterruptCallbackHandler::callBack()
{
    callToEmit();
}

void InterruptCallbackHandler::callToEmit(InterruptSignalEmitter *emitter_)
{
    static InterruptSignalEmitter *emitter = 0;
    if(emitter_ != 0){
        emitter = emitter_;
        return;
    }

    if(emitter == 0){
        D_ERROR("LLamado a callback sin configurar emitter");
        return;
    }

    emitter->emitSignal();
}

InterruptSignalEmitter::InterruptSignalEmitter(QObject *parent)
    : QObject(parent)
{

}

void InterruptSignalEmitter::emitSignal()
{
    emit s_interrupt();
}









