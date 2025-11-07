/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations para evitar dependencias circulares
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta que define la interfaz para todas las tramas
 * @details Implementa el patrón Template Method mediante polimorfismo.
 *          Todas las tramas derivadas deben implementar el método procesar().
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual
     * @details CRÍTICO: Debe ser virtual para permitir la limpieza correcta
     *          de memoria al eliminar objetos derivados mediante punteros base
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista de carga donde se almacenan caracteres decodificados
     * @param rotor Puntero al rotor de mapeo que realiza la transformación de caracteres
     * @details Este método debe ser implementado por todas las clases derivadas.
     *          Define el comportamiento específico de cada tipo de trama.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H