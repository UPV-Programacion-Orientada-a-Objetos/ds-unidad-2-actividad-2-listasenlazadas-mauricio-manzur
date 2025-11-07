/**
 * @file RotorDeMapeo.h
 * @brief Declaración de la clase RotorDeMapeo (Lista Circular Doblemente Enlazada)
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular doblemente enlazada del rotor
 * @details Cada nodo contiene un carácter y punteros al nodo anterior y siguiente
 */
struct NodoRotor {
    char dato;           ///< Carácter almacenado en este nodo
    NodoRotor* siguiente; ///< Puntero al siguiente nodo (circular)
    NodoRotor* previo;    ///< Puntero al nodo anterior (circular)
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    explicit NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Implementa el "disco de cifrado" como una lista circular doblemente enlazada
 * @details Contiene el alfabeto A-Z y un espacio. Permite rotaciones que cambian
 *          el mapeo de caracteres de entrada a salida, simulando una Rueda de César dinámica.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza; ///< Puntero a la posición "cero" actual del rotor
    int tamanio;       ///< Número de elementos en el rotor (27: A-Z + espacio)
    
    /**
     * @brief Inicializa el rotor con el alfabeto A-Z y espacio
     * @details Crea una lista circular con 27 nodos
     */
    void inicializarAlfabeto();
    
public:
    /**
     * @brief Constructor
     * @details Inicializa el rotor con el alfabeto completo
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor
     * @details Libera toda la memoria de los nodos del rotor
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Número de posiciones a rotar (+ adelante, - atrás)
     * @details Mueve el puntero cabeza circularmente sin mover datos
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el mapeo de un carácter según la rotación actual
     * @param in Carácter de entrada
     * @return Carácter mapeado según la posición actual del rotor
     * @details Encuentra el carácter en el rotor y devuelve su equivalente
     *          basado en la rotación actual de la cabeza
     */
    char getMapeo(char in);
};

#endif // ROTOR_DE_MAPEO_H