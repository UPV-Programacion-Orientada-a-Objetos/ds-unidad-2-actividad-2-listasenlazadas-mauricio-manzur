/**
 * @file TramaMap.h
 * @brief Declaración de la clase TramaMap
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaMap
 * @brief Representa una trama de tipo MAP del protocolo PRT-7
 * @details Una trama MAP contiene un valor entero que indica cuántas
 *          posiciones debe rotar el rotor de mapeo. Puede ser positivo
 *          (rotación hacia adelante) o negativo (rotación hacia atrás).
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Número de posiciones a rotar (positivo o negativo)
    
public:
    /**
     * @brief Constructor de TramaMap
     * @param n Número de posiciones a rotar el rotor
     */
    explicit TramaMap(int n);
    
    /**
     * @brief Destructor
     */
    ~TramaMap();
    
    /**
     * @brief Procesa la trama MAP
     * @param carga Puntero a la lista de carga (no se utiliza en MAP)
     * @param rotor Puntero al rotor que será rotado
     * @details Aplica la rotación especificada al rotor de mapeo,
     *          cambiando su estado para futuras decodificaciones
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H