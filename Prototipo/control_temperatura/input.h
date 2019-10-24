#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QDebug>
#include "dev_op.h"

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
#define INPUT_VERSION FROM_TEXT
#endif

#if INPUT_VERSION == FROM_TEXT //interfaz desde texto
    #include <QFile>
    #include <QString>
#endif  //interfaz desde texto

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


#endif
