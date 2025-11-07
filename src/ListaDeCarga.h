/**
 * @file ListaDeCarga.h
 * @brief Declaración de la clase ListaDeCarga (Lista Doblemente Enlazada)
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada de carga
 * @details Almacena un carácter decodificado y punteros al nodo anterior y siguiente
 */
struct NodoCarga {
    char dato;           ///< Carácter decodificado
    NodoCarga* siguiente; ///< Puntero al siguiente nodo
    NodoCarga* previo;    ///< Puntero al nodo anterior
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    explicit NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados
 * @details Mantiene el orden de llegada de los caracteres decodificados
 *          que formarán el mensaje final
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza; ///< Primer nodo de la lista
    NodoCarga* cola;   ///< Último nodo de la lista
    int tamanio;       ///< Número de elementos en la lista
    
public:
    /**
     * @brief Constructor
     * @details Inicializa una lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor
     * @details Libera toda la memoria de los nodos
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     * @details Mantiene el orden de llegada de los datos
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo almacenado
     * @details Recorre la lista e imprime todos los caracteres
     *          en el orden correcto, formando el mensaje decodificado
     */
    void imprimirMensaje() const;
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
};

#endif // LISTA_DE_CARGA_H