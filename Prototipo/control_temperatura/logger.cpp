#include "logger.h"

Logger::Logger()
{
    D_TRACE("Constructor Logger");
    direccionBuffer = LOG_BUFFER_DIR;

    //si no existe el archivo, crearlo
    QFile archivo(direccionBuffer);
    if(!archivo.exists()){
        D_LOG("no se encontro archivo de log. Creando");
        if(!archivo.open(QFile::WriteOnly | QFile::Append)){
            D_ERROR("no se pudo crear el archivo");
        }
        archivo.close();

    }

}


/*  limpiar el archivo log
 */
void Logger::clear()
{
    D_TRACE("Clear archivo log");
    QFile archivo(direccionBuffer);

    if(archivo.exists()){
        archivo.remove();
    }

    if(!archivo.open(QFile::WriteOnly | QFile::Append)){
        D_ERROR("no se pudo crear el archivo");
    }
    archivo.close();
}


/*  añade un reglon al archivo de log temporal
 */
void Logger::addPoint(double t_, double ref_, double temp_, double u_, double ph_)
{
    QFile archivo(direccionBuffer);
    if(!archivo.exists()){
        D_LOG("no se encontro archivo de log. Se creara");
    }

    if(!archivo.open(QFile::WriteOnly | QFile::Append)){
        D_ERROR("no se pudo abrir el archivo");
        return;
    }

    QString reglon =          QString::number(t_);
    reglon.append(' ').append(QString::number(ref_));
    reglon.append(' ').append(QString::number(temp_));
    reglon.append(' ').append(QString::number(u_));
    reglon.append(' ').append(QString::number(ph_));

    //D_DEBUG("añadida linea");
    //D_DEBUG(reglon);

    reglon.append("\r\n");

    QByteArray reglon_byte;
    reglon_byte.append(reglon);

    archivo.write(reglon_byte);

    archivo.close();
}


/*  extrae la columna indicada del archivo temporal y la devuelve como QVector
 */
QVector<double> Logger::getColumna(const int columna_)
{
    D_TRACE("logger Get Columna" << columna_);
    QVector<double> respuesta;
    QStringList reglon;
    QFile archivo(direccionBuffer);

    //abrir archivo
    if(!archivo.open(QFile::ReadOnly | QFile::Text)){
        D_ERROR("no se pudo abrir el archivo");
        return respuesta;
    }

    archivo.seek(0);

    while(!archivo.atEnd()){
        //leer reglon
        reglon = QString(archivo.readLine()).split(' ');
        if(reglon.count() < 5){ //salir del bucle si no hay 5 valores
            break;
        }

        respuesta.append(reglon.at(columna_ - 1).toDouble());
    }

    archivo.close();

    return respuesta;

}


/*  guardar el archivo con el formato indicado
 */
void Logger::saveFile(QString direccion_, const bool phFlag)
{
    if(direccion_.endsWith(".txt",Qt::CaseInsensitive)){
        saveTxtCsv(direccion_, phFlag);
        return;
    }

    if(direccion_.endsWith(".csv",Qt::CaseInsensitive)){
        saveTxtCsv(direccion_, phFlag, ',');
        return;
    }

    if(direccion_.endsWith(".mat",Qt::CaseInsensitive)){
        saveMat(direccion_, phFlag);
        return;
    }

    D_ERROR("formato del archivo no correcto");
}



void Logger::saveTxtCsv(QString direccion_, const bool phFlag, const char separator_)
{
    D_TRACE("guardar txt/csv");
    QFile archivoOut(direccion_);
    QFile archivoIn(direccionBuffer);

    if(!archivoIn.open(QFile::ReadOnly | QFile::Text)){
        D_ERROR("no se pudo abrir el archivo de buffer");
        archivoIn.close();
        return;
    }

    if(archivoOut.exists()){
        D_LOG("se borrara el archivo txt anterior");
        archivoOut.remove();
    }

    if(!archivoOut.open(QFile::WriteOnly | QFile::Append)){
        D_ERROR("no se pudo crear el archivo de salida");
        archivoIn.close();
        archivoOut.close();
        return;
    }


    QString reglon;
    archivoIn.seek(0);

    if(separator_ == ','){
        reglon = "Tiempo,Referencia,Temperatura,U";
        if(phFlag){
            reglon.append(",PH");
        }
        archivoOut.write(QByteArray().append(reglon + "\r\n"));
    }

    while(!archivoIn.atEnd()){
        reglon = archivoIn.readLine();
        if(!phFlag){
            //D_DEBUG("antes de recortar" << reglon);
            reglon.chop(reglon.size()-reglon.lastIndexOf(' '));
            //D_DEBUG("despues de recortar" << reglon);
        }
        archivoOut.write(QByteArray().append(reglon + "\r\n"));
    }

    archivoIn.close();
    archivoOut.close();

}

void Logger::saveMat(QString direccion_, const bool phFlag)
{
    D_TRACE("guardar archivo .mat");
    //llamar a funcion de octave que guarda los datos
    // /home/pi/Documents/temperatura_raspberry/Files/Internos/guardarMat.m
    QFile dirOut(LOG_DIR_OUT_M);
    QFile dirIn(LOG_DIR_IN_M);

    //setear el archivo de direccion de salida
    if(dirOut.exists()){
        dirOut.remove();
    }

    if(!dirOut.open(QFile::WriteOnly | QFile::Append)){
        D_ERROR("no se pudo generar el archivo");
        dirOut.close();
        return;
    }

    dirOut.write(QByteArray().append("dirOut = '"));
    dirOut.write(QByteArray().append(direccion_ + "';"));
    dirOut.close();

    //setear el archivo de direccion de entrada
    if(dirIn.exists()){
        dirIn.remove();
    }

    if(!dirIn.open(QFile::WriteOnly | QFile::Append)){
        D_ERROR("no se pudo generar el archivo");
        dirIn.close();
        return;
    }

    dirIn.write(QByteArray().append("dirIn = '"));
    dirIn.write(QByteArray().append(LOG_BUFFER_DIR));
    dirIn.write(QByteArray().append("';"));
    dirIn.close();


    //ejecutar funcion que genera el archivo .mat

    QString funDir = LOG_FUN_MAT;
    std::string std_fileDir = funDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    if(phFlag){
        entrada_list(0) = 1;
    }else{
        entrada_list(0) = 0;
    }

    feval(funcion, entrada_list, 1);

}




