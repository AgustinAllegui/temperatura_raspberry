#ifndef LOGGER_H
#define LOGGER_H

#include "dev_op.h"
#include <QFile>

#include "Libs/octave_interface.h"

class Logger
{
public:
    Logger();

    //interfaz
    void clear();
    void addPoint(double t_, double ref_, double temp_, double u_, double ph_);

    QVector<double> getTiempo()         {return getColumna(1);}
    QVector<double> getRef()            {return getColumna(2);}
    QVector<double> getTemperatura()    {return getColumna(3);}
    QVector<double> getU()              {return getColumna(4);}
    QVector<double> getPh()             {return getColumna(5);}

    void saveFile(QString direccion_, const bool phFlag);


private:
    //variables privadas
    QString direccionBuffer;

    //metodos privados
    QVector<double> getColumna(const int columna_);

    void saveTxtCsv(QString direccion_, const bool phFlag, const char separator_ = ' ');
    void saveMat(QString direccion_, const bool phFlag);


    Octave_interface octaveInterface;

};

#endif // LOGGER_H
