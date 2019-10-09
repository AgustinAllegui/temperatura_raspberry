#ifndef OCTAVE_INTERFACE_H
#define OCTAVE_INTERFACE_H

/* Esta clase inicializa la interfaz con octave
 *
 * solo con declarar un objeto de la clase Octave_interface se inicializa el interprete de octave
 */

#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/toplev.h>

#include <QDebug>


class Octave_interface
{
public:
    Octave_interface();
    ~Octave_interface();

private:
    static unsigned int init_octave_count;
};

#endif // OCTAVE_INTERFACE_H
