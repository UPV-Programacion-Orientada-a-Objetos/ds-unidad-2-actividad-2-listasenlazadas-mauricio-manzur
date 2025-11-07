/**
 * @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#include "TramaLoad.h"
#include <iostream>

TramaLoad::TramaLoad(char c) : dato(c) {
    // Constructor: almacena el carácter recibido
}

TramaLoad::~TramaLoad() {
    // Destructor: no hay recursos dinámicos que liberar
}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Obtener el carácter decodificado mediante el rotor
    char decodificado = rotor->getMapeo(dato);
    
    // Insertar el carácter decodificado en la lista de carga
    carga->insertarAlFinal(decodificado);
    
    // Mostrar información de depuración
    std::cout << "Trama recibida: [L," << dato << "] -> Procesando... -> ";
    std::cout << "Fragmento '" << dato << "' decodificado como '" << decodificado << "'. ";
    std::cout << "Mensaje: ";
    carga->imprimirMensaje();
    std::cout << std::endl;
}