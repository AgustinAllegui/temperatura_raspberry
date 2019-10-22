#include "graficocustom.h"

GraficoCustom::GraficoCustom(QWidget *parent)
    : QCustomPlot(parent)
{
    plotLayout()->clear();

    // grafico de temperatura
    graficoTemp = new QCPAxisRect(this);
    graficoTemp->axis(QCPAxis::atLeft)->setLabel("Temperatura [°C]");

    lineaRef = addGraph(graficoTemp->axis(QCPAxis::atBottom), graficoTemp->axis(QCPAxis::atLeft));
    lineaRef->setName("Referencia");
    lineaRef->setPen(QPen(QColor(Qt::black)));
    lineaTemp = addGraph(graficoTemp->axis(QCPAxis::atBottom), graficoTemp->axis(QCPAxis::atLeft));
    lineaTemp->setName("Temperatura");
    lineaTemp->setPen(QPen(QColor(Qt::red)));

    //leyenda
//    leyenda = new QCPLegend();
//    leyenda->setWrap(1);
//    lineaRef->addToLegend(leyenda);
//    lineaTemp->addToLegend(leyenda);



    // grafico de Accion de control
    graficoU = new QCPAxisRect(this);
    graficoU->axis(QCPAxis::atLeft)->setLabel("U [%]");

    lineaU = addGraph(graficoU->axis(QCPAxis::atBottom), graficoU->axis(QCPAxis::atLeft));
//    lineaU->setName("Accion de control");

    // grafico de ph
    graficoPh = new QCPAxisRect(this);
    lineaPh = addGraph(graficoPh->axis(QCPAxis::atBottom), graficoPh->axis(QCPAxis::atLeft));


    margenIzq = new QCPMarginGroup(this);
    margenDer = new QCPMarginGroup(this);

//    tiempoTick = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
//    tiempoTick->setTimeFormat("%h:%m:%s");
//    graficoTemp->axis(QCPAxis::atBottom)->setTicker(tiempoTick);
//    graficoU->axis(QCPAxis::atBottom)->setTicker(tiempoTick);

    rearmar(false);
}

GraficoCustom::~GraficoCustom()
{

}

/* quita todos los elementos del layout y los vuelve a agregar
 */
void GraficoCustom::rearmar(const bool phFlag_)
{
    //limpiar todo
    plotLayout()->clear();
    lineaRef->data().clear();
    lineaTemp->data().clear();
    lineaPh->data().clear();

    //agregar los graficos
    plotLayout()->addElement(0,0,graficoTemp);

    QCPLegend *leyenda = new QCPLegend();
    leyenda->setWrap(1);
    plotLayout()->addElement(1,0,leyenda);
    lineaRef->addToLegend(leyenda);
    lineaTemp->addToLegend(leyenda);
//    plotLayout()->addElement(1,0,leyenda);
//    legend->setVisible(true);
    plotLayout()->setRowStretchFactor(1,0.0001);
    plotLayout()->addElement(2,0,graficoU);

    if(phFlag_){
        plotLayout()->addElement(3,0,graficoPh);
    }

    //fijar los margenes
    graficoTemp->setMarginGroup(QCP::msLeft, margenIzq);
    graficoU->setMarginGroup(QCP::msLeft, margenIzq);

    graficoTemp->setMarginGroup(QCP::msRight, margenDer);
    graficoU->setMarginGroup(QCP::msRight, margenDer);

    leyenda->setMarginGroup(QCP::msLeft, margenIzq);
    leyenda->setMarginGroup(QCP::msRight, margenDer);

    if(phFlag_){
        graficoPh->setMarginGroup(QCP::msLeft, margenIzq);
        graficoPh->setMarginGroup(QCP::msRight, margenDer);
    }


    replot();
}


/*  borra los datos de todas las lineas e inserta la linea de referencia en el grafico de temperatura
 */
void GraficoCustom::setRef(QVector<double> referencia_, QVector<double> tiempo_)
{
    lineaTemp->data().clear();
    lineaU->data().clear();
    lineaPh->data().clear();
    lineaRef->data().clear();
    lineaRef->addData(tiempo_, referencia_);
    replot();
}


void GraficoCustom::addPoint(const double t_, const double referencia_, const double temperatura_, const double u_)
{
    lineaRef->addData(t_, referencia_);
    lineaTemp->addData(t_, temperatura_);
    lineaU->addData(t_, u_);
    replot();
}

void GraficoCustom::addPhPoint(const double t_, const double ph_)
{
    lineaPh->addData(t_, ph_);
    replot();
}




