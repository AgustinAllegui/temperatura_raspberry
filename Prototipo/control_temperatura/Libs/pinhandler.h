#ifndef PINHANDLER_H
#define PINHANDLER_H

#include "../dev_op.h"

/* definicion de pines
 */

#define PIN_TERMOCUPLA_CS   3


#define PIN_PT100_MOSI      4
#define PIN_PT100_MISO      5
#define PIN_PT100_CLK       0
#define PIN_PT100_CS        2

#define PIN_RELE            7

#define PIN_LED_APP         23
#define PIN_LED_RUN         22
#define PIN_LED_RELE        21

#define PIN_BOTON_STOP      26



/*  constantes para el calculo de PT100
 */
#define PT100_R_REF         430.0
#define PT100_R_NOMINAL     100.0

#define PT100_RTD_A 3.9083e-3
#define PT100_RTD_B -5.775e-7





#if CURRENT_DEVICE == ON_RASPBERRY

#include <wiringPi.h>
#include <wiringPiSPI.h>

#elif CURRENT_DEVICE == ON_PC


#endif

#include <unistd.h>



class PinHandler
{
public:
    PinHandler();
    bool spiInit(const int channel_, const int speed_);

private:
    static bool pinInited;
    static bool spiCh0Inited;

};

#endif // PINHANDLER_H
