#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QDebug>
#include "dev_op.h"
#include <math.h>

/* Esta clase hace de interfaz con los sensores del sistema
 *
 */


/* hacer que cada sensor emita una señal cuando se hace la
 * lectura y usar eso para actualizar el valor en la barra
 * de estado de la interfaz
 */

#define FROM_TEXT   0   //extrae los valores desde un archivo de texto
#define FROM_SENS   1   //extrae los valores desde los sensores

#ifndef INPUT_VERSION
//#define INPUT_VERSION FROM_TEXT
#define INPUT_VERSION FROM_SENS
#endif

#if INPUT_VERSION == FROM_TEXT //interfaz desde texto
    #include <QFile>
    #include <QString>

#elif INPUT_VERSION == FROM_SENS  //interfaz desde pines

#include "Libs/pinhandler.h"

#endif

class Input_base : public QObject
{
    Q_OBJECT
public:
    Input_base();

//interfaz
    virtual double read();
    double readLast();

protected:
    double lastValue;

#if INPUT_VERSION == FROM_TEXT
    QString direccion;
#endif

};

class Input_ph
    : public Input_base
{
public:
    Input_ph();

    //interfaz
//    double read();
};

class InputTermocupla
    : public Input_base
{
public:
    InputTermocupla();

#if CURRENT_DEVICE == ON_RASPBERRY
    double read();
private:
    PinHandler pinHandler;
#endif
};

class InputPT100
    : public InputPT100
{
public:
    InputPT100();

#if CURRENT_DEVICE == ON_RASPBERRY
    double read();

private:
    PinHandler pinHandler;

    void limpiarFallas();
    uint8_t leerFalla();

    uint8_t leerRegistro(uint8_t direccion);
    void escribirRegistro(uint8_t direccion, uint8_t valor);

    uint8_t spiTransfer(uint8_t data);

    int pinMosi, pinMiso, pinClk, pinCs;
#endif
};


#endif
