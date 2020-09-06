#ifndef ALGORITMO_H
#define ALGORITMO_H

/* esta clase contiene el algoritmo de control a aplicar
 *  y realiza el llamado a las funciones de octave usando la API de Octave
 */

#include <QString>
#include <QFile>
#include <QVector>
#include "dev_op.h"

#include "Libs/octave_interface.h"
#include "tscontainer.h"

class Algoritmo_base
{
public:
    Algoritmo_base();

    //interfaz
    virtual double tic(const double t_, const double ref_, const double temp_);
    void limpiarScope();
    virtual bool verificar();

    //carga de entradas a la funcion
    void passFutureRef(double *futureRef_);
    void passPh(const double ph_);

    // Setters
    void setFileDir(QString fileDir_);
    void setN_fut(const int n_fut_);
    void setPh_flag(const bool ph_flag_);

    //getters
    bool getPh_flag();
    int getN_fut();

protected:
    QString fileDir;

    QVector<double> futureRef;
    double ph;
    int n_fut;
    bool ph_flag;

    //    bool functionCheck(const bool ph_);

private:
    Octave_interface octave;
};

class Algoritmo_pid : public Algoritmo_base
{
public:
    Algoritmo_pid();

    //interfaz
    double tic(const double t_, const double ref_, const double temp_);
    bool verificar();

    //setters
    void setPID(const double Kp_, const double Ki_, const double Kd_, const double C_);

private:
    double Kp, Ki, Kd, C;
};

#endif // ALGORITMO_H
