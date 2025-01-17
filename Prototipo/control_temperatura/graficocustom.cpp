#include "graficocustom.h"

GraficoCustom::GraficoCustom(QWidget *parent)
    : QCustomPlot(parent)
{
    plotLayout()->clear();

    // grafico de temperatura
    QCPAxisRect *graficoTemp = new QCPAxisRect(this);
    graficoTemp->axis(QCPAxis::atLeft)->setLabel("Temperatura [°C]");

    lineaRef = addGraph(graficoTemp->axis(QCPAxis::atBottom), graficoTemp->axis(QCPAxis::atLeft));
    lineaRef->setName("Referencia");
    lineaRef->setPen(QPen(QColor(Qt::black)));
    lineaTemp = addGraph(graficoTemp->axis(QCPAxis::atBottom), graficoTemp->axis(QCPAxis::atLeft));
    lineaTemp->setName("Temperatura");
    lineaTemp->setPen(QPen(QColor(Qt::red)));

    plotLayout()->addElement(0,0,graficoTemp);



    // grafico de Accion de control
    QCPAxisRect *graficoU = new QCPAxisRect(this);
    graficoU->axis(QCPAxis::atLeft)->setLabel("U [%]");


    lineaU = addGraph(graficoU->axis(QCPAxis::atBottom), graficoU->axis(QCPAxis::atLeft));
    lineaU->setName("Accion de control");

    plotLayout()->addElement(2,0,graficoU);

    // grafico de ph
    graficoPh = new QCPAxisRect(this);
    lineaPh = addGraph(graficoPh->axis(QCPAxis::atBottom), graficoPh->axis(QCPAxis::atLeft));
    lineaPh->setName("PH");
    graficoPh->axis(QCPAxis::atLeft)->setLabel("PH");

    //leyenda
    QCPLegend *leyenda = new QCPLegend();
    plotLayout()->addElement(1,0,leyenda);
    plotLayout()->setRowStretchFactor(1,0.0000001);
    leyenda->setWrap(1);
    for(int i = 0; i<5; i++){
        leyenda->removeItem(i);
    }
    lineaRef->addToLegend(leyenda);
    lineaTemp->addToLegend(leyenda);
    leyenda->setVisible(true);

    margenIzq = new QCPMarginGroup(this);
    margenDer = new QCPMarginGroup(this);

//    tiempoTick = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
//    tiempoTick->setTimeFormat("%h:%m:%s");
//    graficoTemp->axis(QCPAxis::atBottom)->setTicker(tiempoTick);
//    graficoU->axis(QCPAxis::atBottom)->setTicker(tiempoTick);

    graficoTemp->setMarginGroup(QCP::msLeft, margenIzq);
    graficoU->setMarginGroup(QCP::msLeft, margenIzq);
    leyenda->setMarginGroup(QCP::msLeft, margenIzq);

    graficoTemp->setMarginGroup(QCP::msRight, margenDer);
    graficoU->setMarginGroup(QCP::msRight, margenDer);
    leyenda->setMarginGroup(QCP::msRight, margenDer);

    phShowed = false;
    rearmar(false);
}

GraficoCustom::~GraficoCustom()
{

}

/*  pone y saca el grafico de ph
 */
void GraficoCustom::rearmar(const bool phFlag_)
{
    if(phFlag_ == phShowed){
        replot();
        return;
    }

    if(phFlag_){
        plotLayout()->addElement(3,0,graficoPh);
        graficoPh->setMarginGroup(QCP::msLeft, margenIzq);
        graficoPh->setMarginGroup(QCP::msRight, margenDer);
        graficoPh->setVisible(true);
    }else{
        plotLayout()->take(graficoPh);
        graficoPh->setVisible(false);
        plotLayout()->simplify();
    }

    phShowed = phFlag_;
    reescalar();
    replot();
}

/* limpia los datos de las lineas
 */
void GraficoCustom::limpiar()
{
    lineaTemp->data().data()->clear();
    lineaU->data().data()->clear();
    lineaPh->data().data()->clear();
    lineaRef->data().data()->clear();
    replot();
}


/*  borra los datos de todas las lineas e inserta la linea de referencia en el grafico de temperatura
 */
void GraficoCustom::setRef(QVector<double> referencia_, QVector<double> tiempo_)
{
    D_TRACE("dibujar referencia inicial");
    limpiar();
    lineaRef->setData(tiempo_, referencia_, true);
    reescalar();
    replot();
}


void GraficoCustom::addPoint(const double t_, const double referencia_, const double temperatura_, const double u_)
{
    lineaRef->addData(t_, referencia_);
    lineaTemp->addData(t_, temperatura_);
    lineaU->addData(t_, u_);
    reescalar();
    replot();
}

void GraficoCustom::addPhPoint(const double t_, const double ph_)
{
    lineaPh->addData(t_, ph_);
    reescalar();
    replot();
}


void GraficoCustom::reescalar()
{
//    lineaRef->rescaleKeyAxis();
    rescaleAxes();
    lineaU->keyAxis()->setRange(lineaRef->keyAxis()->range());
    lineaPh->keyAxis()->setRange(lineaRef->keyAxis()->range());
    replot();
}



/*  mostrar todos todos los datos en el grafico
 */
void GraficoCustom::showAll(QVector<double> tiempo, QVector<double> referencia, QVector<double> temperatura, QVector<double> u)
{
    D_TRACE("mostrar todo en grafico");
    rearmar(false);
//    //D_DEBUG("largo de tiempo" << tiempo.length());
//    //D_DEBUG("tiempo" << tiempo);
    lineaRef->setData(tiempo, referencia);
    lineaTemp->setData(tiempo, temperatura);
    lineaU->setData(tiempo, u);
    reescalar();
}

void GraficoCustom::showAll(QVector<double> tiempo, QVector<double> referencia, QVector<double> temperatura, QVector<double> u, QVector<double> ph)
{
    D_TRACE("mostrar todo en grafico con ph");
    showAll(tiempo, referencia, temperatura, u);
    lineaPh->setData(tiempo, ph);
    rearmar(true);
    reescalar();
}


