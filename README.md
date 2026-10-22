# Simulador de Máquina de Turing (MT)

Este proyecto implementa un simulador de **Máquinas de Turing** en C++. Es capaz de procesar y simular el comportamiento de máquinas de Turing deterministas, con soporte para **múltiples cintas**. Permite cargar la definición formal de la máquina desde un archivo, validar matemáticamente su estructura y evaluar cadenas de entrada paso a paso.

## Estructura del Directorio y Entregables

Para esta práctica, que resuelve dos problemas propuestos, los archivos clave se encuentran distribuidos de la siguiente manera:

*   **Ficheros de Configuración:** Ubicados en la carpeta `docs/`, donde se definen formalmente las máquinas.
    *   `docs/MT1.txt` (Máquina para el Problema 1)
    *   `docs/MT2.txt` (Máquina para el Problema 2)
*   **Imágenes de los Grafos:** Ubicadas en la carpeta `grafos/`, que contienen las representaciones visuales (diagramas de transiciones) de ambas máquinas.
*   **Código Fuente:** Organizado en las carpetas `src/`, `include/`, y `obj/`.

## Compilación y Ejecución

Para compilar el proyecto, asegúrate de estar en el directorio raíz y ejecuta:

```bash
make
```

### Uso

El simulador se ejecuta por línea de comandos y requiere un fichero de configuración.

```bash
./build/simulador_mt -config <ruta_al_fichero>
```

**Ejemplo de ejecución con los problemas propuestos:**
```bash
./build/simulador_mt -config docs/MT1.txt
```

Una vez ejecutado, el programa cargará la máquina, validará sus componentes (conjuntos, alfabetos y transiciones) y mostrará su configuración por pantalla. Posteriormente, entrará en un **modo interactivo** pidiendo cadenas de entrada para simular:
- Escribe la cadena que deseas probar.
- Escribe `salir` para terminar la ejecución.

---

## Estructura del Código y Clases

El proyecto está dividido de forma modular, aplicando principios de Programación Orientada a Objetos:

### 1. Clase `MaquinaTuring` (`MaquinaTuring.h` / `MaquinaTuring.cc`)
Es el **motor principal** del simulador. Representa la tupla matemática de la máquina $M = (Q, \Sigma, \Gamma, s, b, F, \delta)$.
- **Almacena:** Estados, alfabeto de la cadena, alfabeto de la cinta, estado inicial, símbolo blanco, estados de aceptación, número de cintas y la función de transición.
- **Función de Transición:** Implementada mediante un mapa anidado que asocia un estado de origen y los símbolos leídos en las cintas con un objeto `Destino` (que contiene el nuevo estado, los símbolos a escribir y los movimientos de los cabezales).
- **`Simular()`:** Lógica central que inicializa las cintas, coloca la cadena de entrada en la primera cinta (dejando las demás con el símbolo blanco) y ejecuta el bucle de transiciones hasta que la máquina se detiene, mostrando el estado final y el contenido de la cinta principal.
- **`ComprobarValidez()`:** Analiza la coherencia matemática de la máquina, validando que todos los estados y símbolos utilizados pertenezcan a los conjuntos declarados, y que las transiciones tengan la longitud correcta respecto al número de cintas.

### 2. Clase `Estado` (`Estado.h` / `Estado.cc`)
Representa un estado individual dentro de la máquina.
- Almacena el nombre del estado (ej: `q0`, `q1`) y las banderas lógicas que indican si es inicial o final.
- Sobrecarga el operador `<` para poder insertarse en estructuras ordenadas como `std::set`.

### 3. Módulo de Funciones Auxiliares (`funciones.h` / `funciones.cc`)
Contiene la lógica de inicialización para mantener el archivo principal limpio.
- **`CargarMaquinaTuring()`:** Analiza (parsea) secuencialmente el archivo de configuración `.txt`, ignorando las líneas de comentarios (`#`), e invoca los métodos correspondientes en el objeto `MaquinaTuring` para construirlo en memoria.

---

## Formato del Archivo de Configuración

El archivo de configuración que define la máquina debe ser un archivo de texto con un orden estrictamente posicional. Las líneas que empiezan por `#` son ignoradas (comentarios). 

El orden esperado de los parámetros es:

1. **Estados de la máquina (Q):** Separados por espacios (Ej: `q0 q1 q2 q3`)
2. **Alfabeto de la cadena ($\Sigma$):** Símbolos válidos de entrada (Ej: `0 1`)
3. **Alfabeto de la cinta ($\Gamma$):** Símbolos válidos en la cinta, incluye $\Sigma$ y el símbolo blanco (Ej: `0 1 .`)
4. **Estado inicial ($s$):** Un único estado (Ej: `q0`)
5. **Símbolo blanco ($b$):** Carácter que representa una celda vacía (Ej: `.`)
6. **Estados finales (F):** Separados por espacios (Ej: `q3`)
7. **Número de cintas:** Un número entero (Ej: `2`)
8. **Transiciones ($\delta$):** A partir de aquí, cada línea representa una transición. Debe incluir los siguientes elementos separados por espacios, adaptados al número de cintas:
   * `[Estado_Origen] [Simbolos_Leidos] [Estado_Destino] [Simbolos_Escritos] [Movimientos_Cabezales]`
   
