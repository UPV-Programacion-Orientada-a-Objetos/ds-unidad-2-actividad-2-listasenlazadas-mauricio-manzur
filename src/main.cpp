/**
 * @file main.cpp
 * @brief Programa principal del Decodificador PRT-7
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "SerialReader.h"

/**
 * @brief Parsea una línea de texto y crea la trama correspondiente
 * @param linea Cadena de texto en formato "TIPO,DATO"
 * @return Puntero a TramaBase (TramaLoad o TramaMap), nullptr si hay error
 * @details Utiliza funciones C-style (strtok, atoi) para parsear
 */
TramaBase* parsearTrama(char* linea) {
    // Eliminar espacios al inicio y final
    while (*linea == ' ' || *linea == '\t') linea++;
    
    int len = strlen(linea);
    while (len > 0 && (linea[len-1] == ' ' || linea[len-1] == '\t' || linea[len-1] == '\n' || linea[len-1] == '\r')) {
        linea[--len] = '\0';
    }
    
    if (len == 0) return nullptr;
    
    // Buscar la coma
    char* coma = strchr(linea, ',');
    if (!coma) return nullptr;
    
    char tipo = linea[0];
    char* dato = coma + 1;
    
    // Eliminar espacios del dato
    while (*dato == ' ' || *dato == '\t') dato++;
    
    if (tipo == 'L' || tipo == 'l') {
        // Trama LOAD
        if (strlen(dato) > 0) {
            return new TramaLoad(dato[0]);
        }
    } else if (tipo == 'M' || tipo == 'm') {
        // Trama MAP
        int rotacion = atoi(dato);
        return new TramaMap(rotacion);
    }
    
    return nullptr;
}

/**
 * @brief Función principal
 * @return 0 si la ejecución fue exitosa
 * @details Inicializa las estructuras de datos, lee del puerto serial,
 *          procesa las tramas y muestra el mensaje decodificado
 */
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  DECODIFICADOR DE PROTOCOLO PRT-7" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto COM..." << std::endl;
    
    // Configurar el puerto serial (cambiar según tu sistema)

    const char* puerto = "/dev/ttyUSB0";
    
    SerialReader serial(puerto, 9600);
    
    if (!serial.estaConectado()) {
        std::cerr << "No se pudo conectar al puerto serial. Abortando." << std::endl;
        return 1;
    }
    
    std::cout << "Esperando tramas..." << std::endl << std::endl;
    
    // Inicializar estructuras de datos
    ListaDeCarga listaCarga;
    RotorDeMapeo rotorMapeo;
    
    char buffer[256];
    bool transmisionActiva = true;
    
    // Bucle principal de recepción
    while (transmisionActiva) {
        if (serial.leerLinea(buffer, sizeof(buffer))) {
            // Verificar señal de fin
            if (strcmp(buffer, "END") == 0 || strcmp(buffer, "PRT7-TRANSMITTER-READY") == 0) {
                if (strcmp(buffer, "END") == 0) {
                    transmisionActiva = false;
                }
                continue;
            }
            
            // Parsear y procesar la trama
            TramaBase* trama = parsearTrama(buffer);
            
            if (trama) {
                // Polimorfismo en acción
                trama->procesar(&listaCarga, &rotorMapeo);
                
                // Liberar memoria
                delete trama;
            } else {
                std::cerr << "Advertencia: Trama malformada ignorada: [" << buffer << "]" << std::endl;
            }
        }
    }
    
    // Mostrar resultado final
    std::cout << "\n========================================" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    listaCarga.imprimirMensaje();
    std::cout << "\n========================================" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}