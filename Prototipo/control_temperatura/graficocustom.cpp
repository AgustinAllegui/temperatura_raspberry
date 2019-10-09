#include "graficocustom.h"

GraficoCustom::GraficoCustom(QWidget *parent = 0)
    : QCustomPlot(parent)
{
    plotLayout()->clear();

    // grafico de temperatura
    graficoTemp = new QCPAxisRect(this);

    lineaRef = addGraph(graficoTemp->axis(QCPAxis::atBottom), graficoTemp->axis(QCPAxis::atLeft));
    lineaRef->setName("Referencia");
    lineaRef->setPen(QPen(QColor(Qt::black)));
    lineaTemp = addGraph(graficoTemp->axis(QCPAxis::atBottom), graficoTemp->axis(QCPAxis::atLeft));
    lineaTemp->setPen(QPen(QColor(Qt::red)));

    // grafico de Accion de control
    graficoU = new QCPAxisRect(this);


    rearmar(false);
}

GraficoCustom::~GraficoCustom()
{

}

