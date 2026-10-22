#ifndef MAQUINATURING_H_
#define MAQUINATURING_H_

#include "Estado.h"

#include <set>
#include <map>
#include <string>

struct Destino {
  Estado nuevo_estado_; // Nuevo estado al que transita          c1  c2 c3
  std::string simbolos_a_escribir_; // Simobolos a escribir ej:  [a, b, b]
  std::string movimientos_; // Movimientos a realizar ej:        [L, R, L]
};


class MaquinaTuring {
  public:
    MaquinaTuring() {};
    void CargarEstados(const std::set<Estado>& estados);
    void CargarAlfabetoCadena(const std::set<std::string>& alfabeto_cadena);
    void CargarAlfabetoCinta(const std::set<std::string>& alfabeto_cinta);
    void CargarEstadoInicial(const Estado& estado_inicial);
    void CargarSimboloBlanco(const std::string& simbolo_blanco);
    void CargarEstadosAceptacion(const std::set<Estado>& estados_aceptacion);

    void CargarNumeroCintas(int numero) { numero_cintas_ = numero; }
    int GetNumeroCintas() const { return numero_cintas_; }

    void CargarTransicion(const std::string& estado_origen, const std::string& simbolos_leidos, const Destino& destino);

    void Mostrar() const;
    bool ComprobarValidez() const;

    void Simular(const std::string& cadena_entrada);
    
  private:
    using MapaDestinos = std::map<std::string, Destino>;
    using FuncionTransicion = std::map<std::string, MapaDestinos>;
    //conjunto de estados
    std::set<Estado> estados_;
    //alfabeto cadena
    std::set<std::string> alfabeto_cadena_;
    // alfabeto cinta
    std::set<std::string> alfabeto_cinta_;
    //estado inicial
    Estado estado_inicial_;
    //simbolo en blanco
    std::string simbolo_blanco_;
    //conjunto de estados de aceptacion
    std::set<Estado> estados_aceptacion_;
    //funcion de transicion
    FuncionTransicion funcion_transicion_;
    //numero de cintas
    int numero_cintas_{1};
};


#endif //MAQUINATURING_H_