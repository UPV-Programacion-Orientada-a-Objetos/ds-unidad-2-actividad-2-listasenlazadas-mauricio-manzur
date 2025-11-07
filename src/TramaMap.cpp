/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#include "TramaMap.h"
#include <iostream>

TramaMap::TramaMap(int n) : rotacion(n) {
    // Constructor: almacena el valor de rotación
}

TramaMap::~TramaMap() {
    // Destructor: no hay recursos dinámicos que liberar
}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Rotar el rotor según el valor especificado
    rotor->rotar(rotacion);
    
    // Mostrar información de depuración
    std::cout << "\nTrama recibida: [M," << rotacion << "] -> Procesando... -> ";
    std::cout << "ROTANDO ROTOR " << (rotacion >= 0 ? "+" : "") << rotacion << ".\n" << std::endl;
}