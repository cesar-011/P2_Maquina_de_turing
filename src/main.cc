#include <iostream>
#include <fstream>
#include <string>
#include "../include/MaquinaTuring.h"
#include "../include/funciones.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Uso: " << argv[0] << " -config <docs/fichero_configuracion>\n";
    return 1;
  }

  std::string fichero_config = argv[2];
  std::ifstream archivo(fichero_config);

  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo de configuracion: " << fichero_config << "\n";
    return 1;
  }

  MaquinaTuring mt;
  CargarMaquinaTuring(mt, archivo);
  archivo.close();

  // Comprobar validez formal
  if (!mt.ComprobarValidez()) {
    std::cerr << "\nLa máquina contiene errores formales. Abortando ejecución.\n";
    return 1;
  }

  std::cout << "\nMáquina cargada y validada correctamente.\n";
  
  mt.Mostrar();

  // Bucle para probar cadenas hasta que el usuario decida salir
  std::string entrada_usuario;
  std::cout << "\nIntroduce la cadena de entrada a evaluar (o escribe 'salir' para terminar):\n> ";
  
  while (std::cin >> entrada_usuario && entrada_usuario != "salir") {
    // Iniciamos la simulación
    mt.Simular(entrada_usuario);
    std::cout << "\nIntroduce otra cadena de entrada (o 'salir'):\n> ";
  }
  return 0;
}