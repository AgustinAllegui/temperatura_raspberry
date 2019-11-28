#ifndef DEV_OP_H
#define DEV_OP_H

//--------------------------------------------------------------------------------------------
/*  Info de version
 */
#define NUMERO_VERSION "1.0.2"


//--------------------------------------------------------------------------------------------
/*  configuracion del dispositivo actual
 */

#define ON_RASPBERRY    0
#define ON_PC           1

#ifndef CURRENT_DEVICE
#define CURRENT_DEVICE  ON_RASPBERRY
//#define CURRENT_DEVICE  ON_PC
#endif

//--------------------------------------------------------------------------------------------
/*  configuracion de direcciones para los archivos
 */


#if CURRENT_DEVICE == ON_PC

//archivos de funcionamiento interno
#define PID_DIR         "/home/pi/Documents/temperatura_raspberry/Files/Internos/PID_rbp.m"
#define REF_SIMPLE_DIR  "/home/pi/Documents/temperatura_raspberry/Files/Internos/simp_fun.m"
#define LOG_BUFFER_DIR  "/home/pi/Documents/temperatura_raspberry/Files/Internos/log_buffer.txt"
#define LOG_FUN_MAT     "/home/pi/Documents/temperatura_raspberry/Files/Internos/guardarMat.m"
#define LOG_DIR_OUT_M   "/home/pi/Documents/temperatura_raspberry/Files/Internos/setDirOut.m"
#define LOG_DIR_IN_M    "/home/pi/Documents/temperatura_raspberry/Files/Internos/setDirIn.m"
#define CONFIG_DIR      "/home/pi/Documents/temperatura_raspberry/Files/Internos/config.ini"

//archivos entrada y salida para pruebas
#define ENTRADA_FILE_DIR "/home/pi/Documents/temperatura_raspberry/Files/Pruebas/entrada_seno.txt"
#define SALIDA_FILE_DIR "/home/pi/Documents/temperatura_raspberry/Files/Pruebas/salida.txt"


#elif CURRENT_DEVICE == ON_RASPBERRY

//archivos de funcionamiento interno
#define REF_SIMPLE_DIR  "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/simp_fun.m"
#define PID_DIR         "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/PID_rbp.m"
#define LOG_BUFFER_DIR  "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/log_buffer.txt"
#define LOG_FUN_MAT     "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/guardarMat.m"
#define LOG_DIR_OUT_M   "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/setDirOut.m"
#define LOG_DIR_IN_M    "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/setDirIn.m"
#define CONFIG_DIR      "/home/pi/Documents/control_temperatura/temperatura_raspberry/Files/Internos/config.ini"

#endif



//--------------------------------------------------------------------------------------------
/*  Niveles demensajes en la consola
 */
#include <QDebug>
#include <QString>


#ifndef DEBUG_LEVEL

#define DEB_RELEACE     0
#define DEB_LOG         1   // reporte de errores y logros
#define DEB_TRACE       2   // nombre de la funcion a la que entra
#define DEB_DEBUG       3   // valores en informacion sobre el funcionamiento del codigo


#define DEBUG_LEVEL DEB_RELEACE
//#define DEBUG_LEVEL DEB_LOG
//#define DEBUG_LEVEL DEB_TRACE
//#define DEBUG_LEVEL DEB_DEBUG

#endif //debug_level defined

#if (DEBUG_LEVEL >= DEB_RELEACE)
    #define D_INFO(A) qDebug() << "-INFO" << A
#else
    #define D_INFO(A)
#endif

#if (DEBUG_LEVEL >= DEB_LOG)
    #define D_LOG(A) qDebug() << "-LOG:" << A
#else
    #define D_LOG(A)
#endif


#if (DEBUG_LEVEL >= DEB_TRACE)
    #define D_TRACE(A) qDebug() << "-TRACE:" << A << "\t[" << __FILE__ << __LINE__ <<']'
#else
    #define D_TRACE(A)
#endif


#if (DEBUG_LEVEL >= DEB_DEBUG)
    #define D_DEBUG(A) qDebug() << "--DEBUG:" << A
#else
    #define D_DEBUG(A)
#endif

#if (DEBUG_LEVEL == DEB_RELEACE)
    #define D_ERROR(A) qDebug() << "---Error:" << A
#elif (DEBUG_LEVEL > DEB_RELEACE)
    #define D_ERROR(A) qDebug() << "---Error:" << A << "\t[" << __FILE__ << __LINE__ <<']'
#else
    #define D_ERROR(A)
#endif


#endif // DEV_OP_H
