
#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"
#include <cstdio>  // Para printf (C puro, sin STL)

/**
 * @brief Clase concreta para sensores de temperatura
 * 
 * Hereda de SensorBase e implementa los metodos virtuales puros
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;  // Lista que guarda todas las lecturas de temperatura
    
public:
    /**
     * @brief Constructor que crea un sensor de temperatura
     * @param id Identificador unico del sensor
     */
    SensorTemperatura(const char* id) : SensorBase(id) {
        // Llamo al constructor de la clase base para inicializar el nombre
        printf("[Sensor Temperatura] Creado: %s\n", nombre);  // Sin STL
    }
    
    /**
     * @brief Destructor que limpia la memoria del historial
     */
    ~SensorTemperatura() {
        printf("[Destructor Sensor] %s - Liberando historial de temperaturas...\n", nombre);
        // El destructor de ListaSensor se encarga de liberar los nodos
    }
    
    /**
     * @brief Agrega una nueva lectura de temperatura al historial
     * @param valor La temperatura leida (en grados)
     */
    void registrarLectura(float valor) {
        // Inserto el nuevo valor en mi lista
        historial.insertarAlFinal(valor);
        printf("[%s] Temperatura registrada: %.2f C\n", nombre, valor);  // Sin STL
    }
    
    /**
     * @brief Implementacion del procesamiento especifico para temperatura
     * 
     * Elimina la lectura mas baja y calcula el promedio de las restantes
     */
    void procesarLectura() {
        // override significa que estoy redefiniendo un metodo virtual de la clase base
        
        printf("\n-> Procesando Sensor %s...\n", nombre);  // Sin STL
        
        // Verifico que tenga lecturas para procesar
        if (historial.estaVacia()) {
            printf("[%s] No hay lecturas para procesar.\n", nombre);
            return;
        }
        
        // Elimino la temperatura mas baja
        float minTemp = historial.eliminarMasBajo();
        printf("[Sensor Temp] Lectura mas baja eliminada: %.2f C\n", minTemp);
        
        // Calculo el promedio de las temperaturas restantes
        if (!historial.estaVacia()) {
            double promedio = historial.calcularPromedio();
            printf("[Sensor Temp] Promedio de temperaturas restantes: %.2f C (sobre %d lecturas)\n", 
                   promedio, historial.obtenerTamanio());
        } else {
            printf("[Sensor Temp] No quedan lecturas despues de eliminar el minimo.\n");
        }
    }
    
    /**
     * @brief Muestra informacion general del sensor
     */
    void imprimirInfo() const {
        printf("=== Sensor de Temperatura ===\n");
        printf("ID: %s\n", nombre);
        printf("Lecturas almacenadas: %d\n", historial.obtenerTamanio());
        if (!historial.estaVacia()) {
            printf("Promedio actual: %.2f C\n", historial.calcularPromedio());
        }
    }
};

#endif // SENSOR_TEMPERATURA_H