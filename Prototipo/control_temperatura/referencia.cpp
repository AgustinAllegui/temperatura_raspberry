#include "referencia.h"


/*-------------------------------------------------------------------------------
 * Ref_base
 */

Ref_base::Ref_base()
{

}

double Ref_base::getRef(const double t_)
{
    return -1+0*t_;
}

double Ref_base::getRef(const double t_, const int n_, double *ref_array_)
{
    double ref0 = getRef(t_); // la referencia actual
    for(int i=0; i<n_; i++){
        ref_array_[i] = getRef(t_+((i+1)*TsContainer::Ts));
    }
    return ref0;
}

void Ref_base::getInitRef(QVector<double> &t_, QVector<double> &ref_, const double TFinal_)
{
    D_TRACE("generar vectores hasta" << TFinal_);
    t_.clear();
    ref_.clear();
    for(double t = 0; t < TFinal_; t+=TsContainer::Ts){
        t_.append(t);
        ref_.append(getRef(t));
    }
}

bool Ref_base::verificar()
{
    D_ERROR("intento de verificar referencia base");
    return false;
}

/*-------------------------------------------------------------------------------
 * Ref_valores
 */

Ref_valores::Ref_valores()
{

}

void Ref_valores::setFile(QString fileDir_)
{
    fileDir = fileDir_;
}

void Ref_valores::setEndAction(EndAction endAction_)
{
    endAction = endAction_;
}

bool Ref_valores::verificar()
{
    D_TRACE("verificar ref_valores");
    //abrir el archivo
    QFile archivo(fileDir);
    if(!archivo.open(QFile::ReadOnly)){
        D_ERROR(" no se pudo abrir archivo");
        return false;
    }

    fileLength = 0;

    bool thereIsValid = false;
    bool okFlag;
    QString reglon;
    archivo.seek(0);
//    qDebug() << "Archivo:";
    while(!archivo.atEnd()){
        reglon = archivo.readLine();
//        qDebug() << reglon;
        reglon.remove(' ');
        reglon.remove('\n');
        if(reglon.isEmpty()){
            continue;
        }
        if(reglon.startsWith('%')){
            continue;
        }

        reglon.toDouble(&okFlag);
        if(okFlag){
            thereIsValid = true;
            fileLength++;
        }else{                      //si hay almenos un valor no valido, retornar false
//            qDebug() << "Error: hay al menos un valor no valido" << reglon;
            return false;
        }
    }

    if(!thereIsValid){
        D_ERROR("no hay valores validos en el archivo despues de "<< fileLength << "filas");
    }
    return thereIsValid;
}


unsigned int Ref_valores::getFileLength()
{
    return fileLength;
}

double Ref_valores::getRef(const double t_)
{
    D_TRACE("get ref value");
    static double respuesta = 0;

    unsigned int k = (unsigned int)(t_/TsContainer::Ts);
    //D_DEBUG("K: " << k);

    switch(endAction){
        case Cero:{
            if(k>fileLength){
                respuesta = 0;
            }else{
                respuesta = getKRef(k);
            }
            break;
        }
        case Repetir:{
            if(k>fileLength){
                k = k % fileLength;
            }
            respuesta = getKRef(k);
            break;
        }

        case Mantener:{
            if(k<=fileLength){
                respuesta = getKRef(k);
            }
            break;
        }
    }
    return respuesta;
}

double Ref_valores::getKRef(const unsigned int k_)
{
    //Leer archivo y retornar valor k
    QFile archivo(fileDir);
    if(!archivo.open(QFile::ReadOnly)){
        qDebug() << "Error al abrir archivo";
        return -1;
    }
    archivo.seek(0);

    //buscar el reglon K dentro del archivo
    unsigned int lineCount = 0;
    QString reglon;
    while(!archivo.atEnd()){
        reglon = archivo.readLine();
        reglon.remove(' ');
        if( (reglon.isEmpty()) && (reglon.startsWith('%')) ){
            continue;
        }
        //reglon valido
        if(lineCount >= k_){
            break;
        }
        lineCount++;
    }
    archivo.close();

    return reglon.toDouble();
}

/*-------------------------------------------------------------------------------
 * Ref_funcionC
 */

Ref_funcionC::Ref_funcionC()
{

}

void Ref_funcionC::setFile(QString fileDir_)
{
    fileDir = fileDir_;
    QFile archivo(fileDir);
    if(!archivo.exists()){
        D_ERROR("archivo no existe");
        return;
    }

    //checkear si hay funcion de octave en el archivo
    if(!archivo.open(QFile::ReadOnly)){
        D_ERROR("no se pudo abrir archivo");
        return;
    }

    QString reglon;
    while(1){
        reglon = archivo.readLine();
        if(reglon.startsWith("function",Qt::CaseInsensitive)){
            D_LOG("funcion encontrada");
            break;
        }
        if(archivo.atEnd()){
            D_ERROR("el archivo no contiene una funcion");
            break;
        }
    }
}

double Ref_funcionC::getRef(const double t_)
{
//    D_TRACE("get ref funcion" << TsContainer::Ts << t_);
    //calcular y retornar el siguiente valor para t = t_
    std::string std_fileDir = fileDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    entrada_list(0) = TsContainer::Ts;
    entrada_list(1) = t_;

    octave_value_list salida_list = feval(funcion, entrada_list, 1);

    double referencia = salida_list(0).double_value();
//    //D_DEBUG("Referencia" << referencia);
    return referencia;
}

bool Ref_funcionC::verificar()
{
    D_TRACE("ref_funcion C verificar");
    std::string std_fileDir = fileDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    entrada_list(0) = 1;
    entrada_list(1) = 1;

    octave_value_list salida_list = feval(funcion, entrada_list, 1);
    if(salida_list.length()>0){
        return true;
    }else{
        return false;
    }

}

/*-------------------------------------------------------------------------------
 * Ref_funcionS
 */

Ref_funcionS::Ref_funcionS()
{

}

void Ref_funcionS::setFunction(QString simpFunction_, QString fileDir_)
{
    D_TRACE("Ref_funcion S set funcion");
    fileDir = fileDir_;
    QFile archivo(fileDir);

    if(archivo.exists()){
        archivo.remove();
    }
    if(!archivo.open(QFile::WriteOnly)){
        D_ERROR("no se pudo generar el archivo");
    }

    archivo.write("% archivo del sistema. no modificar\n");
    archivo.write("function [ref] = simp_fun(Ts, t)\n  ref = ");
    archivo.write(simpFunction_.toStdString().c_str());
    archivo.write(";\nendfunction");
    archivo.close();

}

bool Ref_funcionS::verificar()
{
    D_TRACE("ref_funcion S verificar");
    return Ref_funcionC::verificar();
}
