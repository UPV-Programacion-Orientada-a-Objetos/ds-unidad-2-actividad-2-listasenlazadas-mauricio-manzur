/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#include "ListaDeCarga.h"
#include <iostream>

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {
    // Constructor: inicializa una lista vacía
}

ListaDeCarga::~ListaDeCarga() {
    // Liberar todos los nodos
    NodoCarga* actual = cabeza;
    while (actual) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (!cabeza) {
        // Lista vacía
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // Insertar al final
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
    
    tamanio++;
}

void ListaDeCarga::imprimirMensaje() const {
    std::cout << "[";
    NodoCarga* actual = cabeza;
    while (actual) {
        std::cout << actual->dato;
        if (actual->siguiente) {
            std::cout << "][";
        }
        actual = actual->siguiente;
    }
    std::cout << "]";
}

bool ListaDeCarga::estaVacia() const {
    return cabeza == nullptr;
}