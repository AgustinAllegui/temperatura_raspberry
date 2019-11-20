#include "algoritmo.h"

/* -------------------------------------------------------------------
 * algoritmo de control generico
 */
Algoritmo_base::Algoritmo_base()
{

}

void Algoritmo_base::limpiarScope()
{
    feval("clear"); //ejecutar el comando >>clear
}

void Algoritmo_base::setFileDir(QString fileDir_)
{
    D_TRACE("set file dir");
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
    //D_DEBUG("direccion" << fileDir);

}

void Algoritmo_base::setN_fut(const int n_fut_)
{
    D_TRACE("set n_fut" << n_fut);
    n_fut = n_fut_;
    futureRef.clear();
    futureRef.squeeze();
    if(n_fut > 0){
        futureRef.resize(n_fut);
    }
}

int Algoritmo_base::getN_fut()
{
    return n_fut;
}

void Algoritmo_base::setPh_flag(const bool ph_flag_)
{
    ph_flag = ph_flag_;
}

bool Algoritmo_base::getPh_flag()
{
    return ph_flag;
}


void Algoritmo_base::passPh(const double ph_)
{
    if(ph_flag){
        ph = ph_;
    }else{
        qDebug() << "error, no esta habilitado el sensor de Ph";
    }
}

void Algoritmo_base::passFutureRef(double *futureRef_)
{
    for(int i = 0; i<n_fut; i++){
        futureRef[i] = futureRef_[i];
    }
}

double Algoritmo_base::tic(const double t_, const double ref_, const double temp_)
{
    D_TRACE("control tic");

    // llamar a function [u] = funcion(Ts, t, referencia, temperatura, [futRef], [ph]);
    //calcular y retornar el valor para t = t_
    std::string std_fileDir = fileDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    entrada_list(0) = TsContainer::Ts;
    entrada_list(1) = t_;
    entrada_list(2) = ref_;
    entrada_list(3) = temp_;
    int i = 4;
    Matrix futureRef_matrix;
    if(n_fut>0){
        //D_DEBUG("pass futRef");
        futureRef_matrix = Matrix(n_fut,1);
        for(octave_idx_type j = 0; j<n_fut; j++){
            futureRef_matrix.elem(j,0) = futureRef[j];
        }
        entrada_list(i) = futureRef_matrix;
        i++;
    }
    if(ph_flag){
        //D_DEBUG("pass ph");
        entrada_list(i) = ph;
    }

    //D_DEBUG("entrada seteada" << entrada_list.length());

    octave_value_list salida_list = feval(funcion, entrada_list, 1);

    //D_DEBUG("salida calculada" << salida_list.length());

    double accion_control = salida_list(0).double_value();
    return accion_control;

}

bool Algoritmo_base::verificar()
{
    D_TRACE("Algoritmo base Verificar");
    // llamar a function [u] = funcion(Ts, t, referencia, temperatura, [futRef], [ph]);
    //calcular y retornar el valor para t = 1
    //D_DEBUG("direccion" << fileDir);
    std::string std_fileDir = fileDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    entrada_list(0) = 1;
    entrada_list(1) = 2;
    entrada_list(2) = 3;
    entrada_list(3) = 4;

    Matrix futureRef_matrix;
    octave_idx_type i = 3;
    if(n_fut>0){
        i++;
        //D_DEBUG("pass futRef" << n_fut);
        futureRef_matrix = Matrix(n_fut,1);
        for(octave_idx_type j = 0; j<n_fut; j++){
            //D_DEBUG("f ref" << j+5);
            futureRef_matrix.elem(j,0) = 5+j;
        }
        entrada_list(i) = futureRef_matrix;
        //D_DEBUG("entradalist" << entrada_list(i).double_value());
    }
    if(ph_flag){
        i++;
        //D_DEBUG("pass ph" << 1);
        entrada_list(i) = 1;
    }

    //D_DEBUG("lista de datos");
    for(octave_idx_type k = 0; k<=i ; k++){
        //D_DEBUG(k << entrada_list(k).double_value());
    }

    octave_value_list salida_list = feval(funcion, entrada_list, 1);
    if(salida_list.length()>0){
        return true;
    }else{
        return false;
    }
}

/* ------------------------------------------------------------------
 * algoritmo PID
 */

Algoritmo_pid::Algoritmo_pid()
{
    n_fut = 0;
    ph_flag = false;
}

void Algoritmo_pid::setPID(const double Kp_, const double Ki_, const double Kd_)
{
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
    fileDir = PID_DIR;

}

double Algoritmo_pid::tic(const double t_, const double ref_, const double temp_)
{
    D_TRACE("algoritmo PID");
    //function [u] = PID_rbp(Ts, t, ref, temp, Kp, Ki, Kd)
    //u[%] = accion1 =  (kp*e(n) + Kd*(e(n)-e(n-1))/Ts + Ki * Ts * sumatoria(e);

    std::string std_fileDir = fileDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    entrada_list(0) = TsContainer::Ts;
    entrada_list(1) = t_;
    entrada_list(2) = ref_;
    entrada_list(3) = temp_;
    entrada_list(4) = Kp;
    entrada_list(5) = Ki;
    entrada_list(6) = Kd;

    octave_value_list salida_list = feval(funcion, entrada_list, 1);

    double accion_control = salida_list(0).double_value();
    return accion_control;
}

bool Algoritmo_pid::verificar()
{
    D_TRACE("Algoritmo PID verificar");

    //function [u] = PID_rbp(Ts, t, ref, temp, Kp, Ki, Kd)
    //u[%] = accion1 =  (kp*e(n) + Kd*(e(n)-e(n-1))/Ts + Ki * Ts * sumatoria(e);

    std::string std_fileDir = fileDir.toStdString();
    octave_function *funcion = load_fcn_from_file(std_fileDir);

    octave_value_list entrada_list;
    entrada_list(0) = 1;
    entrada_list(1) = 2;
    entrada_list(2) = 3;
    entrada_list(3) = 4;
    entrada_list(4) = 5;
    entrada_list(5) = 6;
    entrada_list(6) = 7;

    octave_value_list salida_list = feval(funcion, entrada_list, 1);

    if(salida_list.length()>0){
        return true;
    }else{
        return false;
    }
}
