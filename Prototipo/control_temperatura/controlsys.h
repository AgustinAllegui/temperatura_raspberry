#ifndef CONTROLSYS_H
#define CONTROLSYS_H

#include <QObject>

#include "dev_op.h"

#include "tscontainer.h"
#include "input.h"
#include "referencia.h"
#include "algoritmo.h"
#include "output_rele.h"

class ControlSys : public QObject
{
    Q_OBJECT
public:
    explicit ControlSys(QObject *parent = 0);

    //inicializacion

    //configuracion
    Input_base *sensor;
    Input_base *sensor_ph;

    Ref_base *referencia;

    Algoritmo_base *algoritmo;

    void setDuracion(const double duracion_);

    Output_rele *salida;


    //funcionamiento
    bool controlStart();
    void controlStop();
    bool isRuning();

signals:
    void s_control_data(double t_, double ref_, double temp_, double u_, double ph_);
    void s_control_stop();

public slots:
    void controlTic();

private:
    //variables privadas
    double timeSinceStart;
    double duracion;

    bool runState; //true si esta corriendo el algoritmo de control (entonces no modificar la configuracion)


};

#endif // CONTROLSYS_H
