

#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"
#include <cstdio>  // Para printf (C puro, sin STL)

/**
 * @brief Clase concreta para sensores de presion
 * 
 * Hereda de SensorBase e implementa los metodos virtuales puros
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial;  // Lista que guarda todas las lecturas de presion
    
public:
    /**
     * @brief Constructor que crea un sensor de presion
     * @param id Identificador unico del sensor
     */
    SensorPresion(const char* id) : SensorBase(id) {
        // Llamo al constructor de la clase base para inicializar el nombre
        printf("[Sensor Presion] Creado: %s\n", nombre);  // Sin STL
    }
    
    /**
     * @brief Destructor que limpia la memoria del historial
     */
    ~SensorPresion() {
        printf("[Destructor Sensor] %s - Liberando historial de presiones...\n", nombre);
        // El destructor de ListaSensor se encarga de liberar los nodos
    }
    
    /**
     * @brief Agrega una nueva lectura de presion al historial
     * @param valor La presion leida (en unidades)
     */
    void registrarLectura(int valor) {
        // Inserto el nuevo valor en mi lista
        historial.insertarAlFinal(valor);
        printf("[%s] Presion registrada: %d Pa\n", nombre, valor);  // Sin STL
    }
    
    /**
     * @brief Implementacion del procesamiento especifico para presion
     * 
     * Calcula el promedio de todas las lecturas de presion
     */
    void procesarLectura() {
        // override significa que estoy redefiniendo un metodo virtual de la clase base
        
        printf("\n-> Procesando Sensor %s...\n", nombre);  // Sin STL
        
        // Verifico que tenga lecturas para procesar
        if (historial.estaVacia()) {
            printf("[%s] No hay lecturas para procesar.\n", nombre);
            return;
        }
        
        // Calculo el promedio de todas las presiones
        double promedio = historial.calcularPromedio();
        printf("[Sensor Presion] Promedio de presiones: %.2f Pa (sobre %d lecturas)\n",
               promedio, historial.obtenerTamanio());
    }
    
    /**
     * @brief Muestra informacion general del sensor
     */
    void imprimirInfo() const {
        printf("=== Sensor de Presion ===\n");
        printf("ID: %s\n", nombre);
        printf("Lecturas almacenadas: %d\n", historial.obtenerTamanio());
        if (!historial.estaVacia()) {
            printf("Promedio actual: %.2f Pa\n", historial.calcularPromedio());
        }
    }
};

#endif // SENSOR_PRESION_H