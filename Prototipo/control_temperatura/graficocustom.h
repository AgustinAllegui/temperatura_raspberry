#ifndef GRAFICO_H
#define GRAFICO_H

#include "Libs/qcustomplot.h"
#include "dev_op.h"


class GraficoCustom : public QCustomPlot
{
public:
    explicit GraficoCustom(QWidget *parent);
    ~GraficoCustom();

    //interfaz
    void rearmar(const bool phFlag_);

    void setRef(QVector<double> referencia_, QVector<double> tiempo_);
    void addPoint(const double t_, const double referencia_, const double temperatura_, const double u_);
    void addPhPoint(const double t_, const double ph_);



    // elementos del grafico
    QCPAxisRect *graficoTemp, *graficoU, *graficoPh;
    QCPGraph *lineaRef, *lineaTemp;
    QCPGraph *lineaU;
    QCPGraph *lineaPh;

//    QCPLegend *leyenda;
    QCPMarginGroup *margenIzq, *margenDer;
//    QSharedPointer<QCPAxisTickerTime> tiempoTick;
};

#endif // GRAFICO_H
