

#ifndef SIMULADOR_ARDUINO_H
#define SIMULADOR_ARDUINO_H

#include <cstdio>   // Para printf (C puro, sin STL)
#include <cstdlib>  // Para rand, srand (C puro)
#include <ctime>    // Para time (C puro)

/**
 * @brief Clase que simula la recepcion de datos desde un Arduino
 * 
 * En un proyecto real, aqui se usaria una libreria como libserial
 * para comunicarse con el puerto serial, pero para este caso
 * voy a simular los datos de forma aleatoria
 */
class SimuladorArduino {
private:
    bool inicializado;  // Bandera para saber si ya inicialice el generador
    
public:
    /**
     * @brief Constructor que inicializa el simulador
     */
    SimuladorArduino() : inicializado(false) {
        // Inicializo el generador de numeros aleatorios
        srand(time(NULL));
        printf("[Arduino] Simulador inicializado.\n");  // Sin STL
    }
    
    /**
     * @brief Simula la lectura de un valor de temperatura
     * @return Temperatura simulada entre 15.0 y 45.0 grados
     */
    float leerTemperatura() {
        // Genero un numero aleatorio entre 15 y 45 grados
        float temp = 15.0f + (rand() % 300) / 10.0f;
        printf("[Arduino] Lectura de temperatura: %.2f C\n", temp);  // Sin STL
        return temp;
    }
    
    /**
     * @brief Simula la lectura de un valor de presion
     * @return Presion simulada entre 70 y 110 Pa
     */
    int leerPresion() {
        // Genero un numero aleatorio entre 70 y 110 Pa
        int presion = 70 + (rand() % 41);
        printf("[Arduino] Lectura de presion: %d Pa\n", presion);  // Sin STL
        return presion;
    }
    
    /**
     * @brief Simula multiples lecturas de temperatura
     * @param cantidad Cuantas lecturas quiero simular
     */
    void simularLecturasTemperatura(int cantidad) {
        printf("\n[Arduino] Simulando %d lecturas de temperatura...\n", cantidad);
        for (int i = 0; i < cantidad; i++) {
            leerTemperatura();
        }
    }
    
    /**
     * @brief Simula multiples lecturas de presion
     * @param cantidad Cuantas lecturas quiero simular
     */
    void simularLecturasPresion(int cantidad) {
        printf("\n[Arduino] Simulando %d lecturas de presion...\n", cantidad);
        for (int i = 0; i < cantidad; i++) {
            leerPresion();
        }
    }
    
    /**
     * @brief Muestra informacion del puerto serial (simulado)
     */
    void mostrarInfoPuerto() {
        printf("\n=== Informacion del Puerto Serial ===\n");
        printf("Puerto: /dev/ttyUSB0 (Simulado)\n");
        printf("Baudrate: 9600 bps\n");
        printf("Estado: Conectado\n");
    }
};

#endif // SIMULADOR_ARDUINO_H