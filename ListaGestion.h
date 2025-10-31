
#ifndef LISTA_GESTION_H
#define LISTA_GESTION_H

#include "SensorBase.h"
#include <cstdio>   // Para printf (C puro, sin STL)
#include <cstring>  // Para strcmp (C puro)

/**
 * @brief Estructura de nodo para la lista de gestion
 * 
 * Guarda un puntero a la clase base SensorBase para permitir polimorfismo
 */
struct NodoGestion {
    SensorBase* sensor;         // Apuntador a cualquier tipo de sensor
    NodoGestion* siguiente;     // Apuntador al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param s Puntero al sensor que quiero guardar
     */
    NodoGestion(SensorBase* s) : sensor(s), siguiente(NULL) {}
};

/**
 * @brief Clase que maneja la lista de todos los sensores del sistema
 * 
 * Esta lista NO es generica porque solo guarda punteros a SensorBase
 */
class ListaGestion {
private:
    NodoGestion* cabeza;  // Primer nodo de la lista
    int tamanio;          // Cantidad de sensores registrados
    
public:
    /**
     * @brief Constructor que crea una lista vacia
     */
    ListaGestion() : cabeza(NULL), tamanio(0) {
        printf("[Sistema] Lista de gestion inicializada.\n");  // Sin STL
    }
    
    /**
     * @brief Destructor que libera todos los sensores
     */
    ~ListaGestion() {
        printf("\n--- Liberacion de Memoria en Cascada ---\n");  // Sin STL
        
        // Recorro todos los nodos y los voy borrando
        NodoGestion* actual = cabeza;
        while (actual != NULL) {
            NodoGestion* siguiente = actual->siguiente;
            
            printf("[Destructor General] Liberando Nodo: %s\n", 
                   actual->sensor->obtenerNombre());
            
            // Borro el sensor (esto llamara al destructor correcto por polimorfismo)
            delete actual->sensor;
            
            // Borro el nodo de la lista
            delete actual;
            
            actual = siguiente;
        }
        
        printf("Sistema cerrado. Memoria limpia.\n");
    }
    
    /**
     * @brief Agrega un nuevo sensor a la lista de gestion
     * @param sensor Puntero al sensor que quiero agregar
     */
    void agregarSensor(SensorBase* sensor) {
        // Creo un nuevo nodo para este sensor
        NodoGestion* nuevoNodo = new NodoGestion(sensor);
        
        // Si la lista esta vacia, este es el primer nodo
        if (cabeza == NULL) {
            cabeza = nuevoNodo;
        } else {
            // Si no, busco el final y lo agrego ahi
            NodoGestion* actual = cabeza;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        
        tamanio++;
        printf("[Sistema] Sensor '%s' agregado a la lista de gestion.\n", 
               sensor->obtenerNombre());
    }
    
    /**
     * @brief Busca un sensor por su ID
     * @param id Identificador del sensor
     * @return Puntero al sensor si lo encuentra, nullptr si no
     */
    SensorBase* buscarSensor(const char* id) {
        // Recorro la lista comparando nombres
        NodoGestion* actual = cabeza;
        while (actual != NULL) {
            if (strcmp(actual->sensor->obtenerNombre(), id) == 0) {
                return actual->sensor;  // Lo encontre
            }
            actual = actual->siguiente;
        }
        return NULL;  // No lo encontre
    }
    
    /**
     * @brief Ejecuta el procesamiento polimorfico de todos los sensores
     * 
     * Aqui es donde ocurre la magia del polimorfismo: cada sensor
     * ejecutara su propia version de procesarLectura()
     */
    void procesarTodos() {
        printf("\n--- Ejecutando Polimorfismo ---\n");  // Sin STL
        
        // Recorro todos los sensores
        NodoGestion* actual = cabeza;
        while (actual != NULL) {
            // Llamo al metodo procesarLectura() usando el puntero de la clase base
            // Pero gracias al polimorfismo, se ejecutara el metodo correcto
            // segun el tipo real del sensor (Temperatura o Presion)
            actual->sensor->procesarLectura();
            
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Muestra informacion de todos los sensores
     */
    void imprimirTodos() const {
        printf("\n=== Sensores Registrados ===\n");  // Sin STL
        
        NodoGestion* actual = cabeza;
        int contador = 1;
        while (actual != NULL) {
            printf("\n--- Sensor %d ---\n", contador);
            actual->sensor->imprimirInfo();
            
            contador++;
            actual = actual->siguiente;
        }
        
        printf("\nTotal de sensores: %d\n", tamanio);
    }
    
    /**
     * @brief Obtiene la cantidad de sensores registrados
     * @return Numero de sensores
     */
    int obtenerTamanio() const {
        return tamanio;
    }
};

#endif // LISTA_GESTION_H