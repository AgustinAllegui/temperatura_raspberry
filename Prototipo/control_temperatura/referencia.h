#ifndef REFERENCIA_H
#define REFERENCIA_H

/*  Esta clase contiene la referencia a usar en el sistema de control
 *
 * llama al archivo, funcion o lo que sea necesario para obtener el valor
 */

#include <QString>
#include <QFile>
#include <QDebug>

#include "dev_op.h"

#include "Libs/octave_interface.h"
#include "tscontainer.h"

class Ref_base
{
public:
    Ref_base();

    //interfaz
    virtual double getRef(const double t_);
    double getRef(const double t_, const int n_, double *ref_array_);
    void getInitRef(QVector<double> &t_, QVector<double> &ref_, const double TFinal_);
    virtual bool verificar();
};


/* Referencia proviene de un archivo de valores
 * (los comentarios comienzan con %)
 */
class Ref_valores
    : public Ref_base
{
public:
    Ref_valores();

    //interfaz
    double getRef(const double t_);
    bool verificar();

    //setters
    void setFile(QString fileDir_);

    enum EndAction {
        Mantener,
        Cero,
        Repetir
    };
    void setEndAction(EndAction endAction_);

    unsigned int getFileLength();


protected:
    double getKRef(const unsigned int k_);
    unsigned int fileLength;
    QString fileDir;
    EndAction endAction;

};

/* Referencia proviene de un archivo de funcion
 */
class Ref_funcionC
    :public Ref_base
{
public:
    Ref_funcionC();

    //interfaz
    double getRef(const double t_);
    bool verificar();

    //setters
    void setFile(QString fileDir_);

protected:
    QString fileDir;
    Octave_interface octave;
};


/* Referencia proviene de una funcion simple
 */

class Ref_funcionS
    :public Ref_funcionC
{
public:
    Ref_funcionS();

    void setFunction(QString simpFunction_, QString fileDir_);
    bool verificar();

};

#endif // REFERENCIA_H
