#include "input.h"

Input_base::Input_base()
#if INPUT_VERSION == FROM_TEXT
    : direccion("/home/pi/Documents/Files/Pruebas/entrada_seno.txt")
#endif
{

}

double Input_base::readLast()
{
    return lastValue;
}

//leer desde texto
#if INPUT_VERSION == FROM_TEXT

/*leer del archivo pt100.txt
 */
double Input_base::read()
{
//    DTRACE("input read from text");
    QFile archivo(direccion);
    if(!archivo.open(QFile::ReadOnly)){
        DLOG("Error al abrir archivo pt100");
        return -1;
    }

    static int reglon_count = 0;

    if(archivo.atEnd()){
        DLOG("Error: Archivo pt100 vacio");
        return -2;
    }

    QString reglon = archivo.readLine();

    for(int i = 0; i < reglon_count; i++){
        if(archivo.atEnd()){
            archivo.seek(0);
        }
        reglon = archivo.readLine();
    }

    archivo.close();

    reglon_count++;
    lastValue = reglon.toDouble();
    return lastValue;
}


/*-------------------------------------------------------------------------------
 * Input ph
 */

Input_ph::Input_ph()
{
    direccion = "/home/pi/Documents/Files/Pruebas/ph1.txt";
}

#endif // leer desde texto
