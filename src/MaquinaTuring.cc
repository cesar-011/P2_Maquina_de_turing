#include "../include/MaquinaTuring.h"

#include <iostream>
#include <vector>

/// @brief Carga el conjunto de estados de la máquina de Turing
/// @param estados Conjunto de estados a cargar
void MaquinaTuring::CargarEstados(const std::set<Estado>& estados) {
  estados_ = estados;
}

/// @brief Carga el alfabeto de la cadena de entrada (Sigma)
/// @param alfabeto_cadena Conjunto de símbolos que componen el alfabeto de entrada
void MaquinaTuring::CargarAlfabetoCadena(const std::set<std::string>& alfabeto_cadena) {
  alfabeto_cadena_ = alfabeto_cadena;
}

/// @brief Carga el alfabeto de la cinta (Gamma)
/// @param alfabeto_cinta Conjunto de símbolos que componen el alfabeto de la cinta
void MaquinaTuring::CargarAlfabetoCinta(const std::set<std::string>& alfabeto_cinta) {
  alfabeto_cinta_ = alfabeto_cinta;
}

/// @brief Establece el estado inicial de la máquina de Turing
/// @param estado_inicial Objeto Estado que representa el estado inicial
void MaquinaTuring::CargarEstadoInicial(const Estado& estado_inicial) {
  estado_inicial_ = estado_inicial;
}

/// @brief Establece el símbolo que representará el espacio en blanco en la cinta
/// @param simbolo_blanco Cadena que representa el símbolo blanco
void MaquinaTuring::CargarSimboloBlanco(const std::string& simbolo_blanco) {
  simbolo_blanco_ = simbolo_blanco;
}

/// @brief Carga el conjunto de estados de aceptación o finales
/// @param estados_aceptacion Conjunto de estados de aceptación
void MaquinaTuring::CargarEstadosAceptacion(const std::set<Estado>& estados_aceptacion) {
  estados_aceptacion_ = estados_aceptacion;
}

/// @brief Añade una transición a la función de transición de la máquina
/// @param estado_origen Nombre del estado desde el cual se evalúa la transición
/// @param simbolos_leidos Símbolos que deben leer los cabezales para que se aplique la transición
/// @param destino Objeto Destino con el nuevo estado, símbolos a escribir y movimientos de los cabezales
void MaquinaTuring::CargarTransicion(const std::string& estado_origen, const std::string& simbolos_leidos, const Destino& destino) {
  funcion_transicion_[estado_origen][simbolos_leidos] = destino;
}

/// @brief Simula la ejecución de la máquina de Turing para una cadena de entrada dada
/// @param cadena_entrada Cadena de texto a procesar en la cinta principal
void MaquinaTuring::Simular(const std::string& cadena_entrada) {
  // Inicializar las cintas y los cabezales
  std::vector<std::vector<char>> cintas(numero_cintas_);
  std::vector<int> cabezales(numero_cintas_, 0);

  // Llenar la primera cinta con la entrada
  if (cadena_entrada.empty()) {
    cintas[0].push_back(simbolo_blanco_[0]);
  } else {
    for (char c : cadena_entrada) {
      cintas[0].push_back(c);
    }
  }

  // Las cintas adicionales empiezan solo con un símbolo en blanco
  for (int i = 1; i < numero_cintas_; ++i) {
    cintas[i].push_back(simbolo_blanco_[0]);
  }

  std::string estado_actual = estado_inicial_.get_estado();

  // Bucle principal de ejecución
  while (true) {
    // Leer los símbolos bajo todos los cabezales
    std::string simbolos_leidos = "";
    for (int i = 0; i < numero_cintas_; ++i) {
      simbolos_leidos += cintas[i][cabezales[i]];
    }

    // Condición de parada: Si no hay transición para este estado y estos símbolos, nos detenemos
    if (funcion_transicion_.find(estado_actual) == funcion_transicion_.end() ||
        funcion_transicion_[estado_actual].find(simbolos_leidos) == funcion_transicion_[estado_actual].end()) {
      break; 
    }

    // Obtener la regla a aplicar
    Destino dest = funcion_transicion_[estado_actual][simbolos_leidos];

    // Aplicar acciones a cada cinta simultáneamente
    for (int i = 0; i < numero_cintas_; ++i) {
      // Escribir
      cintas[i][cabezales[i]] = dest.simbolos_a_escribir_[i];

      // Mover
      char mov = dest.movimientos_[i];
      if (mov == 'R') {
        cabezales[i]++;
        // Cinta infinita por la derecha
        if (cabezales[i] >= (int)cintas[i].size()) {
          cintas[i].push_back(simbolo_blanco_[0]);
        }
      } else if (mov == 'L') {
        // Cinta infinita por la izquierda
        if (cabezales[i] == 0) {
          cintas[i].insert(cintas[i].begin(), simbolo_blanco_[0]);
        } else {
          cabezales[i]--;
        }
      }
    }

    // Cambiar estado
    estado_actual = dest.nuevo_estado_.get_estado();
  }

  // Resultado Final
  Estado estado_final(estado_actual);
  bool es_aceptada = (estados_aceptacion_.find(estado_final) != estados_aceptacion_.end());

  std::cout << "\n--- RESULTADO DE LA SIMULACIÓN ---\n";
  std::cout << "Cadena de entrada : " << cadena_entrada << "\n";
  std::cout << "Estado de parada  : " << estado_actual << "\n";
  std::cout << "Cadena aceptada   : " << (es_aceptada ? "SÍ" : "NO") << "\n";
  
  // Imprimir la primera cinta con el cabezal marcado entre corchetes
  std::cout << "Cinta 1 (Final)   : ";
  for (int j = 0; j < (int)cintas[0].size(); ++j) {
    if (j == cabezales[0]) {
      std::cout << "[" << cintas[0][j] << "]";
    } else {
      std::cout << cintas[0][j];
    }
  }
  std::cout << "\n----------------------------------\n";
}

/// @brief Muestra por consola toda la configuración detallada de la máquina de Turing
void MaquinaTuring::Mostrar() const {
  std::cout << "=== CONFIGURACIÓN DE LA MÁQUINA DE TURING ===\n";
  
  std::cout << "Estados (Q): { ";
  for (const auto& estado : estados_) std::cout << estado.get_estado() << " ";
  std::cout << "}\n";

  std::cout << "Alfabeto Cadena (Sigma): { ";
  for (const auto& sim : alfabeto_cadena_) std::cout << sim << " ";
  std::cout << "}\n";

  std::cout << "Alfabeto Cinta (Gamma): { ";
  for (const auto& sim : alfabeto_cinta_) std::cout << sim << " ";
  std::cout << "}\n";

  std::cout << "Estado inicial (s): " << estado_inicial_.get_estado() << "\n";
  std::cout << "Símbolo blanco (b): " << simbolo_blanco_ << "\n";

  std::cout << "Estados de aceptación (F): { ";
  for (const auto& estado : estados_aceptacion_) std::cout << estado.get_estado() << " ";
  std::cout << "}\n";

  std::cout << "Número de cintas: " << numero_cintas_ << "\n";

  std::cout << "Función de transición (Delta):\n";
  for (const auto& par_origen : funcion_transicion_) {
    std::string estado_origen = par_origen.first;
    for (const auto& par_destino : par_origen.second) {
      std::string leidos = par_destino.first;
      Destino dest = par_destino.second;
      std::cout << "  d(" << estado_origen << ", " << leidos << ") -> ("
                << dest.nuevo_estado_.get_estado() << ", " 
                << dest.simbolos_a_escribir_ << ", " 
                << dest.movimientos_ << ")\n";
    }
  }
  std::cout << "=============================================\n";
}

/// @brief Comprueba si la configuración actual de la máquina cumple con la definición formal
/// @return true si la máquina es válida y cumple todas las restricciones, false en caso contrario
bool MaquinaTuring::ComprobarValidez() const {
  bool es_valida = true;

  // 1. El estado inicial pertenece a Q (s ∈ Q)
  if (estados_.find(estado_inicial_) == estados_.end()) {
    std::cerr << "Error: El estado inicial '" << estado_inicial_.get_estado() << "' no pertenece al conjunto Q.\n";
    es_valida = false;
  }

  // 2. Los estados de aceptación pertenecen a Q (F ⊆ Q)
  for (const auto& estado_acep : estados_aceptacion_) {
    if (estados_.find(estado_acep) == estados_.end()) {
      std::cerr << "Error: El estado de aceptación '" << estado_acep.get_estado() << "' no pertenece al conjunto Q.\n";
      es_valida = false;
    }
  }

  // 3. El símbolo blanco pertenece a Γ y NO pertenece a Σ
  if (alfabeto_cinta_.find(simbolo_blanco_) == alfabeto_cinta_.end()) {
    std::cerr << "Error: El símbolo blanco '" << simbolo_blanco_ << "' no pertenece al alfabeto de cinta Γ.\n";
    es_valida = false;
  }
  if (alfabeto_cadena_.find(simbolo_blanco_) != alfabeto_cadena_.end()) {
    std::cerr << "Error: El símbolo blanco '" << simbolo_blanco_ << "' no puede pertenecer al alfabeto de entrada Σ.\n";
    es_valida = false;
  }

  // 4. El alfabeto de entrada es subconjunto del de cinta (Σ ⊆ Γ)
  for (const auto& sim : alfabeto_cadena_) {
    if (alfabeto_cinta_.find(sim) == alfabeto_cinta_.end()) {
      std::cerr << "Error: El símbolo de entrada '" << sim << "' no está en el alfabeto de cinta Γ.\n";
      es_valida = false;
    }
  }

  // 5. Validar las Transiciones
  for (const auto& par_origen : funcion_transicion_) {
    std::string str_origen = par_origen.first;
    Estado estado_origen(str_origen); 

    if (estados_.find(estado_origen) == estados_.end()) {
      std::cerr << "Error en transición: El estado origen '" << str_origen << "' no existe en Q.\n";
      es_valida = false;
    }

    for (const auto& par_destino : par_origen.second) {
      std::string leidos = par_destino.first;
      const Destino& dest = par_destino.second; // Arreglado el warning de copia

      if (estados_.find(dest.nuevo_estado_) == estados_.end()) {
        std::cerr << "Error en transición: El estado destino '" << dest.nuevo_estado_.get_estado() << "' no existe en Q.\n";
        es_valida = false;
      }

      // Validar longitud respecto al número de cintas (Arreglado el warning de unsigned/signed)
      if (leidos.length() != (size_t)numero_cintas_ || 
          dest.simbolos_a_escribir_.length() != (size_t)numero_cintas_ || 
          dest.movimientos_.length() != (size_t)numero_cintas_) {
        std::cerr << "Error en transición desde '" << str_origen << "': La cantidad de símbolos o movimientos no coincide con el número de cintas (" << numero_cintas_ << ").\n";
        es_valida = false;
      }

      // NUEVO: Validar que los símbolos LEÍDOS pertenezcan al alfabeto de cinta
      for (char c : leidos) {
        std::string sim_str(1, c);
        if (alfabeto_cinta_.find(sim_str) == alfabeto_cinta_.end()) {
            std::cerr << "Error en transición: El símbolo leído '" << c << "' no pertenece al alfabeto de cinta Γ.\n";
            es_valida = false;
        }
      }

      // Validar movimientos permitidos (L, R, S)
      for (char m : dest.movimientos_) {
        if (m != 'L' && m != 'R' && m != 'S') {
          std::cerr << "Error en transición: Movimiento '" << m << "' no reconocido (debe ser L, R o S).\n";
          es_valida = false;
        }
      }
      
      // Validar que los símbolos ESCRITOS pertenezcan al alfabeto de cinta
      for (char s : dest.simbolos_a_escribir_) {
        std::string sim_str(1, s);
        if (alfabeto_cinta_.find(sim_str) == alfabeto_cinta_.end()) {
            std::cerr << "Error en transición: Intenta escribir el símbolo '" << s << "' que no pertenece a Γ.\n";
            es_valida = false;
        }
      }
    }
  }

  return es_valida;
}