/**
 * @file SerialReader.cpp
 * @brief Implementación de la clase SerialReader
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

#include "SerialReader.h"
#include <iostream>
#include <cstring>

SerialReader::SerialReader(const char* puerto, int baudRate) : conectado(false) {
#ifdef _WIN32
    // Configuración para Windows
    hSerial = CreateFileA(puerto,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          nullptr,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          nullptr);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return;
    }
    
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al obtener estado del puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al configurar puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    
    conectado = true;
#else
    // Configuración para Linux
    fd = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return;
    }
    
    struct termios opciones;
    tcgetattr(fd, &opciones);
    
    cfsetispeed(&opciones, B9600);
    cfsetospeed(&opciones, B9600);
    
    opciones.c_cflag |= (CLOCAL | CREAD);
    opciones.c_cflag &= ~PARENB;
    opciones.c_cflag &= ~CSTOPB;
    opciones.c_cflag &= ~CSIZE;
    opciones.c_cflag |= CS8;
    
    tcsetattr(fd, TCSANOW, &opciones);
    
    conectado = true;
#endif
    
    std::cout << "Conexión establecida con " << puerto << " a " << baudRate << " baudios." << std::endl;
}

SerialReader::~SerialReader() {
#ifdef _WIN32
    if (conectado) {
        CloseHandle(hSerial);
    }
#else
    if (conectado) {
        close(fd);
    }
#endif
}

bool SerialReader::leerLinea(char* buffer, int maxLength) {
    if (!conectado) return false;
    
    int pos = 0;
    char c;
    
    while (pos < maxLength - 1) {
#ifdef _WIN32
        DWORD bytesLeidos;
        if (!ReadFile(hSerial, &c, 1, &bytesLeidos, nullptr)) {
            return false;
        }
        if (bytesLeidos == 0) continue;
#else
        int n = read(fd, &c, 1);
        if (n < 0) return false;
        if (n == 0) continue;
#endif
        
        if (c == '\n') {
            buffer[pos] = '\0';
            return true;
        }
        
        if (c != '\r') { // Ignorar retorno de carro
            buffer[pos++] = c;
        }
    }
    
    buffer[pos] = '\0';
    return true;
}

bool SerialReader::estaConectado() const {
    return conectado;
}