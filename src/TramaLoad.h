/**
 * @file TramaLoad.h
 * @brief Declaración de la clase TramaLoad
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaLoad
 * @brief Representa una trama de tipo LOAD del protocolo PRT-7
 * @details Una trama LOAD contiene un carácter que debe ser decodificado
 *          utilizando el estado actual del rotor de mapeo y luego
 *          almacenado en la lista de carga.
 */
class TramaLoad : public TramaBase {
private:
    char dato; ///< Carácter a decodificar
    
public:
    /**
     * @brief Constructor de TramaLoad
     * @param c Carácter que contiene esta trama
     */
    explicit TramaLoad(char c);
    
    /**
     * @brief Destructor
     */
    ~TramaLoad();
    
    /**
     * @brief Procesa la trama LOAD
     * @param carga Puntero a la lista donde se almacenará el carácter decodificado
     * @param rotor Puntero al rotor que realizará el mapeo del carácter
     * @details Toma el carácter almacenado, lo decodifica mediante el rotor
     *          y lo inserta al final de la lista de carga
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H