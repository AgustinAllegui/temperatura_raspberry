#include "output_rele.h"

Output_rele::Output_rele()
    : output_value(0)
    , n_Ts(1)
#if OUTPUT_VERSION == TO_TEXT
    , direccion(SALIDA_FILE_DIR)
#endif
{
    salidaMinima = 0;
    salidaMaxima = 100;
}

void Output_rele::config(const int n_Ts_)
{
    n_Ts = n_Ts_;

#if OUTPUT_VERSION == TO_TEXT
    QFile archivo(direccion);
    if(archivo.exists()){
        archivo.remove();
    }
#endif
}

#if OUTPUT_VERSION == TO_TEXT   // salida a texto

double Output_rele::setOutput(const double output_)
{
    DTRACE("set output" << output_);
    output_value = checkSaturacion(output_);
    QFile archivo(direccion);
    if(!archivo.open(QFile::WriteOnly | QFile::Append)){
        //error al abrir el archivo
        DERROR("no se pudo abrir el archivo out.txt");
    }

    QByteArray byteArray;
    byteArray.append(QString::number(output_) + "\n");
//    archivo.seek(archivo.size());
    archivo.write(byteArray);
    archivo.close();
    return output_value;
}

#endif  //salida a texto

void Output_rele::emergencyStop()
{
    setOutput(0);
}

double Output_rele::checkSaturacion(const double valor_)
{
    if(valor_ <= salidaMinima){
        return salidaMinima;
    }
    if(valor_ >= salidaMaxima){
        return salidaMaxima;
    }

    return valor_;
}


