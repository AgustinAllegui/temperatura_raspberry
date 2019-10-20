#ifndef DEV_OP_H
#define DEV_OP_H

/*  este archivo contiene funciones para el desarrollo y debugueo
 */
#include <QDebug>
#include <QString>


#ifndef DEBUG_LEVEL

#define DEB_RELEACE     0
#define DEB_LOG         1   // reporte de errores y logros
#define DEB_TRACE       2   // nombre de la funcion a la que entra
#define DEB_DEBUG       3   // valores en informacion sobre el funcionamiento del codigo


//#define DEBUG_LEVEL DEB_RELEACE
//#define DEBUG_LEVEL DEB_TRACE
//#define DEBUG_LEVEL DEB_LOG
#define DEBUG_LEVEL DEB_DEBUG

#endif //debug_level defined


#if (DEBUG_LEVEL >= DEB_LOG)
    #define DLOG(A) qDebug() << "-LOG:" << A
#else
    #define DLOG(A)
#endif


#if (DEBUG_LEVEL >= DEB_TRACE)
    #define DTRACE(A) qDebug() << "-TRACE:" << A << "/  /" << __FILE__ << __LINE__
#else
    #define DTRACE(A)
#endif


#if (DEBUG_LEVEL >= DEB_DEBUG)
    #define DDEBUG(A) qDebug() << "--DEBUG:" << A
#else
    #define DDEBUG(A)
#endif


#endif // DEV_OP_H
