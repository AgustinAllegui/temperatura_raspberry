#include "octave_interface.h"

unsigned int Octave_interface::init_octave_count = 0;

Octave_interface::Octave_interface()
{
    // inicializacion de octave
    if(init_octave_count == 0){
        qDebug() << "inicializando interprete de octave";

        string_vector oct_str_vct (2);
        oct_str_vct(0) = "embedded";
        oct_str_vct(1) = "-q";
        octave_main(2, oct_str_vct.c_str_vec(), 1);
    }
    init_octave_count++;
    qDebug() << "Octaves utilizados:" << init_octave_count;
}

Octave_interface::~Octave_interface()
{
    init_octave_count--;
    qDebug() << "octaves restantes por cerrar:" << init_octave_count;
    if(init_octave_count == 0){
        qDebug() << "cerrando octave";
        clean_up_and_exit(0);
    }
}
