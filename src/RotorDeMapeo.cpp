/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#include "RotorDeMapeo.h"
#include <iostream>

RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamanio(27) {
    inicializarAlfabeto();
}

RotorDeMapeo::~RotorDeMapeo() {
    if (!cabeza) return;
    
    // Romper el círculo para poder eliminar
    NodoRotor* ultimo = cabeza->previo;
    ultimo->siguiente = nullptr;
    
    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void RotorDeMapeo::inicializarAlfabeto() {
    // Crear el alfabeto A-Z más el espacio (27 caracteres)
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    
    NodoRotor* primero = nullptr;
    NodoRotor* anterior = nullptr;
    
    for (int i = 0; i < tamanio; i++) {
        NodoRotor* nuevo = new NodoRotor(alfabeto[i]);
        
        if (!primero) {
            primero = nuevo;
            cabeza = nuevo;
        } else {
            anterior->siguiente = nuevo;
            nuevo->previo = anterior;
        }
        
        anterior = nuevo;
    }
    
    // Cerrar el círculo
    anterior->siguiente = primero;
    primero->previo = anterior;
}

void RotorDeMapeo::rotar(int n) {
    if (!cabeza) return;
    
    // Normalizar n para evitar rotaciones excesivas
    n = n % tamanio;
    
    if (n > 0) {
        // Rotación hacia adelante
        for (int i = 0; i < n; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (n < 0) {
        // Rotación hacia atrás
        for (int i = 0; i > n; i--) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    if (!cabeza) return in;
    
    // Convertir a mayúscula si es necesario
    if (in >= 'a' && in <= 'z') {
        in = in - 'a' + 'A';
    }
    
    // Buscar el carácter en el rotor
    NodoRotor* actual = cabeza;
    int posicion = 0;
    
    do {
        if (actual->dato == in) {
            // Encontrado: calcular el mapeo
            // El carácter mapeado está en la misma posición relativa desde cabeza
            NodoRotor* mapeado = cabeza;
            for (int i = 0; i < posicion; i++) {
                mapeado = mapeado->siguiente;
            }
            return mapeado->dato;
        }
        actual = actual->siguiente;
        posicion++;
    } while (actual != cabeza);
    
    // Si no se encuentra, devolver el carácter original
    return in;
}