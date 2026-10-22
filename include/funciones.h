#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include "MaquinaTuring.h"

#include <fstream>


// Construir a partir del fichero la maquina de turing y las cintas
void CargarMaquinaTuring(MaquinaTuring& maquina_turing, std::ifstream& fichero_configuracion);

#endif //FUNCIONES_H_