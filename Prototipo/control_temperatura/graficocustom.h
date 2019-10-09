#ifndef GRAFICO_H
#define GRAFICO_H

#include "Libs/qcustomplot.h"
#include "dev_op.h"


class GraficoCustom : public QCustomPlot
{
public:
    explicit GraficoCustom(QWidget *parent = 0);
    ~GraficoCustom();

    //interfaz
    void rearmar(const bool phFlag_);



    // elementos del grafico
    QCPAxisRect *graficoTemp, *graficoU, *graficoPh;
    QCPGraph *lineaRef, *lineaTemp;
    QCPGraph *lineaU;
    QCPGraph *lineaPh;

    QCPLegend *leyenda;
    QCPMarginGroup *margenIzq, *margenDer;
};

#endif // GRAFICO_H
