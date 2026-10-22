#include "../include/funciones.h"

#include <sstream>
#include <string>


/// @brief Lee un archivo de configuración y carga los parámetros en una Máquina de Turing
/// @param maquina_turing Referencia al objeto MaquinaTuring que será inicializado
/// @param fichero_configuracion Flujo de archivo de entrada (std::ifstream) abierto con la configuración de la máquina
void CargarMaquinaTuring(MaquinaTuring& maquina_turing, std::ifstream& fichero_configuracion) {
  std::string linea;
  int iterator{0};
  int numero_cintas{1};

  if (fichero_configuracion.is_open()) {
    while (std::getline(fichero_configuracion, linea)) {
      // Ignoramos comentarios
      if (linea.empty() || linea[0] == '#') {
        continue;
      }

      switch (iterator) {
        case 0: {
          std::stringstream line_string(linea);
          std::string estado_string;
          std::set<Estado> estados;
          while (line_string >> estado_string) {
            estados.insert(Estado(estado_string));
          }
          maquina_turing.CargarEstados(estados);
          iterator++;
          break;
        }
        case 1: {
          std::stringstream line_string(linea);
          std::string simbolo;
          std::set<std::string> alfabeto;
          while (line_string >> simbolo) {
            alfabeto.insert(simbolo);
          }
          maquina_turing.CargarAlfabetoCadena(alfabeto);
          iterator++;
          break;
        }
        case 2: {
          std::stringstream line_string(linea);
          std::string simbolo;
          std::set<std::string> alfabeto;
          while (line_string >> simbolo) {
            alfabeto.insert(simbolo);
          }
          maquina_turing.CargarAlfabetoCinta(alfabeto);
          iterator++;
          break;
        }
        case 3: {
          std::stringstream line_string(linea);
          std::string estado_inicial;
          line_string >> estado_inicial;
          maquina_turing.CargarEstadoInicial(Estado(estado_inicial));
          iterator++;
          break;
        }
        case 4: {
          std::stringstream line_string(linea);
          std::string simbolo_blanco;
          line_string >> simbolo_blanco;
          maquina_turing.CargarSimboloBlanco(simbolo_blanco);
          iterator++;
          break;
        }
        case 5: {
          std::stringstream line_string(linea);
          std::string estado_string;
          std::set<Estado> estados_aceptacion;
          while (line_string >> estado_string) {
            estados_aceptacion.insert(Estado(estado_string));
          }
          maquina_turing.CargarEstadosAceptacion(estados_aceptacion);
          iterator++;
          break;
        }
        case 6: {
          std::stringstream line_string(linea);
          line_string >> numero_cintas;
          maquina_turing.CargarNumeroCintas(numero_cintas);
          iterator++;
          break;
        }
        case 7: {
          // Como las transiciones son múltiples líneas, NO incrementamos el iterador.
          // Se quedará procesando todas las líneas restantes aquí.
          std::stringstream line_string(linea);
          std::string estado_origen, estado_destino;
          std::string simbolos_leidos, simbolos_escritos, movimientos, temp;

          // Leer Estado Origen
          line_string >> estado_origen;

          // Leer símbolos que lee tantos como cintas
          for (int i = 0; i < numero_cintas; i++) {
            line_string >> temp;
            simbolos_leidos += temp;
          }

          // Leer Estado Destino
          line_string >> estado_destino;

          // Leer símbolos que escribe
          for (int i = 0; i < numero_cintas; i++) {
            line_string >> temp;
            simbolos_escritos += temp;
          }

          // Leer movimientos (L, R, S)
          for (int i = 0; i < numero_cintas; i++) {
            line_string >> temp;
            movimientos += temp;
          }

          // Construimos el destino y lo pasamos a la máquina
          Destino destino_actual{Estado(estado_destino), simbolos_escritos, movimientos};
          maquina_turing.CargarTransicion(estado_origen, simbolos_leidos, destino_actual);
          break;
        }
        default:
          break;
      }
    }
  }
}