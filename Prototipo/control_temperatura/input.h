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


#if CURRENT_DEVICE == ON_PC //interfaz desde texto
    #include <QFile>
    #include <QString>

#elif CURRENT_DEVICE == ON_RASPBERRY  //interfaz desde pines

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

#if CURRENT_DEVICE == ON_PC
    QString direccion;
#endif

};

class Input_ph
    : public Input_base
{
public:
    Input_ph();

    //interfaz
    double read();
};

class InputTermocupla
    : public Input_base
{
public:
    InputTermocupla();

#if CURRENT_DEVICE == ON_RASPBERRY
    double read();

signals:
    void s_inputTermocupla_read(double temperatura_);

private:
    PinHandler pinHandler;
#endif
};

class InputPT100
    : public Input_base
{
public:
    InputPT100();

#if CURRENT_DEVICE == ON_RASPBERRY
    double read();

signals:
    void s_inputPT100_read(double temperatura_);


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
