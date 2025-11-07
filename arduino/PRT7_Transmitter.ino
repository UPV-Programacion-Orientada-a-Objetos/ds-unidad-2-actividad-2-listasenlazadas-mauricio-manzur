/**
 * @file PRT7_Transmitter.ino
 * @brief Transmisor de protocolo PRT-7 para Arduino
 * @details Este sketch simula un sensor industrial que transmite datos
 *          codificados mediante el protocolo PRT-7, enviando tramas LOAD y MAP
 * @author Mauricio Manzur
 * @date 2025-11-07
 */

// Configuración de comunicación serial
#define BAUD_RATE 9600
#define DELAY_BETWEEN_FRAMES 1000 // 1 segundo entre tramas

/**
 * @brief Configuración inicial del Arduino
 * @details Inicializa la comunicación serial a 9600 baudios
 */
void setup() {
  Serial.begin(BAUD_RATE);
  delay(2000); // Espera para estabilizar la conexión
  Serial.println("PRT7-TRANSMITTER-READY");
}

/**
 * @brief Bucle principal de transmisión
 * @details Envía la secuencia de tramas del protocolo PRT-7
 *          que formarán el mensaje oculto "HELLO WORLD"
 */
void loop() {
  // Secuencia de tramas para formar "HELLO WORLD"
  
  // Tramas LOAD iniciales (sin rotación)
  enviarTrama("L,H");
  enviarTrama("L,E");
  enviarTrama("L,L");
  enviarTrama("L,L");
  enviarTrama("L,O");
  
  // Trama MAP: Rotar el rotor +0 (sin cambios) para espacio
  enviarTrama("M,0");
  enviarTrama("L, "); // Espacio
  
  // Continuar con "WORLD"
  enviarTrama("L,W");
  enviarTrama("L,O");
  enviarTrama("L,R");
  enviarTrama("L,L");
  enviarTrama("L,D");
  
  // Señal de fin de transmisión
  delay(DELAY_BETWEEN_FRAMES);
  Serial.println("END");
  
  // Detener transmisión (bucle infinito sin hacer nada)
  while(true) {
    delay(10000);
  }
}

/**
 * @brief Envía una trama por el puerto serial
 * @param trama Cadena de caracteres con el formato "TIPO,DATO"
 * @details Envía la trama y espera el tiempo configurado entre transmisiones
 */
void enviarTrama(const char* trama) {
  Serial.println(trama);
  delay(DELAY_BETWEEN_FRAMES);
}