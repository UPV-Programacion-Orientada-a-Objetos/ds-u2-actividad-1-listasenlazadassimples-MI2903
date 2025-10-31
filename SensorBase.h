

#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <cstring>  // Para strncpy (C puro)
#include <cstdio>   // Para printf (C puro)

/**
 * @brief Clase abstracta que define la interfaz comun para todos los sensores
 * 
 * Esta clase no se puede instanciar directamente, solo sirve como base
 * para crear sensores especificos
 */
class SensorBase {
protected:
    char nombre[50];  // Identificador unico del sensor (ej: "T-001")
    
public:
    /**
     * @brief Constructor que inicializa el nombre del sensor
     * @param id Cadena con el identificador del sensor
     */
    SensorBase(const char* id) {
        // Copio el nombre de forma segura para evitar desbordamientos
        strncpy(nombre, id, 49);
        nombre[49] = '\0';  // Me aseguro de que termine en null
    }
    
    /**
     * @brief Destructor virtual para permitir limpieza correcta en clases derivadas
     * 
     * Es virtual porque cuando borro un SensorBase* que apunta a una clase derivada,
     * necesito que se llame al destructor correcto de esa clase
     */
    virtual ~SensorBase() {
        printf("[Destructor Base] Liberando sensor: %s\n", nombre);  // Sin STL
    }
    
    /**
     * @brief Metodo virtual puro que debe implementar cada sensor especifico
     * 
     * Cada tipo de sensor procesara sus lecturas de manera diferente
     */
    virtual void procesarLectura() = 0;
    
    /**
     * @brief Metodo virtual puro para mostrar informacion del sensor
     */
    virtual void imprimirInfo() const = 0;
    
    /**
     * @brief Obtiene el nombre del sensor
     * @return Puntero al nombre
     */
    const char* obtenerNombre() const {
        return nombre;  // Regreso el identificador
    }
};

#endif // SENSOR_BASE_H