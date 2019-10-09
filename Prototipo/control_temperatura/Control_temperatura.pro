#-------------------------------------------------
#
# Project created by QtCreator 2019-09-19T10:57:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Control_temperatura
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    controlsys.cpp \
    Libs/octave_interface.cpp \
    input.cpp \
    referencia.cpp \
    tscontainer.cpp \
    algoritmo.cpp \
    output_rele.cpp \
    Libs/qcustomplot.cpp \
    graficocustom.cpp

HEADERS  += mainwindow.h \
    tscontainer.h \
    controlsys.h \
    Libs/octave_interface.h \
    input.h \
    referencia.h \
    algoritmo.h \
    output_rele.h \
    dev_op.h \
    Libs/qcustomplot.h \
    graficocustom.h

FORMS    += mainwindow.ui



# Librerias para usar octave

INCLUDEPATH += "/usr/include/octave-4.0.3/octave"
INCLUDEPATH += "/usr/include/octave-4.0.3/octave/.."
LIBS += "/usr/lib/i386-linux-gnu/liboctinterp.so"
LIBS += "/usr/lib/i386-linux-gnu/liboctave.so"
#LIBS += "/usr/lib/arm-linux-gnueabihf/liboctave.so"
#LIBS += "/usr/lib/arm-linux-gnueabihf/liboctinterp.so"
