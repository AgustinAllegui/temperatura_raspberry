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

#include "dev_op.h"

#include <QObject>
#include "tscontainer.h"

#if CURRENT_DEVICE == ON_PC

    #include <QFile>
    #include <QString>

#elif CURRENT_DEVICE == ON_RASPBERRY

    #include "Libs/pinhandler.h"
    #include <QTimer>

#endif



class Output_rele : public QObject
{
    Q_OBJECT
public:
    explicit Output_rele(QObject *parent = 0);

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

#if CURRENT_DEVICE == ON_PC
    QString direccion;
#endif

private:
#if CURRENT_DEVICE == ON_RASPBERRY
    bool pinMirror;
    PinHandler pinHandler;

    QTimer activeOutTimer;


private slots:
    void slot_activeOutTimer_timeout();
#endif

signals:
    void s_outputChange(bool isHigh);

public slots:

};

#endif // OUTPUT_RELE_H
