#ifndef OUTPUT_RELE_H
#define OUTPUT_RELE_H

/* Esta clase hace de interfaz con el actuador del sistema
 *
 */

/*  NOTA:
 *  probablemente sea necesario hacer que herede de QObject para usar un slot para
 * activar y desactivar el rele, y señalar que se activo y se desactivo para
 * mostrar en la interfaz
 */

#include <QDebug>
#include "dev_op.h"
#include "tscontainer.h"

/* configuracion de version
 */
#define TO_TEXT     0   //carga el valor en un texto
#define TO_RELAY    1   //carga el valor en la salida rele

#ifndef OUTPUT_VERSION
#define OUTPUT_VERSION TO_TEXT
#endif

#if OUTPUT_VERSION == TO_TEXT //interfaz desde texto
    #include <QFile>
    #include <QString>
#endif  //interfaz desde texto


class Output_rele
{
public:
    Output_rele();

    //interfaz
    void config(const int n_Ts_ = 1);
    double setOutput(const double output_);

    void emergencyStop();

    protected:
    // variables privadas
    double output_value;
    int n_Ts;   //numero de ciclos del rele en un tiempo de muestreo

    double salidaMinima, salidaMaxima;

    //metodos privados
    double checkSaturacion(const double valor_);

#if OUTPUT_VERSION == TO_TEXT
    QString direccion;
#endif
};

#endif // OUTPUT_RELE_H
