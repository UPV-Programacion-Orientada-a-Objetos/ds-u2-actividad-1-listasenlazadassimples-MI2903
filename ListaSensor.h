
#ifndef LISTA_SENSOR_H
#define LISTA_SENSOR_H

#include <cstdio>   // Para printf (C puro, no STL)
#include <cstdlib>  // Para NULL

/**
 * @brief Estructura que representa un nodo de la lista
 * @tparam T Tipo de dato que guardara el nodo (int, float, etc)
 */
template <typename T>
struct Nodo {
    T dato;              // Aqui guardo el valor de la lectura
    Nodo<T>* siguiente;  // Apuntador al siguiente nodo de la lista
    
    /**
     * @brief Constructor que inicializa el nodo con un valor
     * @param valor El dato que quiero guardar en este nodo
     */
    Nodo(T valor) : dato(valor), siguiente(NULL) {}
};

/**
 * @brief Clase que maneja una lista enlazada simple generica
 * @tparam T Tipo de dato que guardaran los nodos
 */
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;  // Apuntador al primer nodo de mi lista
    int tamanio;      // Contador de cuantos nodos tengo
    
public:
    /**
     * @brief Constructor que crea una lista vacia
     */
    ListaSensor() : cabeza(NULL), tamanio(0) {
        // Inicio la lista sin nodos
    }
    
    /**
     * @brief Destructor que libera toda la memoria de los nodos
     */
    ~ListaSensor() {
        // Tengo que borrar cada nodo para no dejar basura en memoria
        Nodo<T>* actual = cabeza;  // Empiezo desde el primer nodo
        while (actual != NULL) {
            Nodo<T>* siguiente = actual->siguiente;  // Guardo la referencia al siguiente
            printf("[Log] Liberando Nodo\n");  // Mensaje sin STL
            delete actual;  // Borro el nodo actual
            actual = siguiente;  // Avanzo al siguiente nodo
        }
    }
    
    /**
     * @brief Constructor de copia para hacer copias profundas
     * @param otra La lista que quiero copiar
     */
    ListaSensor(const ListaSensor& otra) : cabeza(NULL), tamanio(0) {
        // Copio cada nodo de la otra lista para tener mi propia copia
        Nodo<T>* actual = otra.cabeza;
        while (actual != NULL) {
            insertarAlFinal(actual->dato);  // Inserto cada dato en mi nueva lista
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Operador de asignacion para copiar una lista en otra
     * @param otra La lista fuente
     * @return Referencia a esta lista
     */
    ListaSensor& operator=(const ListaSensor& otra) {
        // Evito copiarme a mi mismo
        if (this != &otra) {
            // Primero borro mi contenido actual
            this->~ListaSensor();
            cabeza = NULL;
            tamanio = 0;
            
            // Ahora copio los nodos de la otra lista
            Nodo<T>* actual = otra.cabeza;
            while (actual != NULL) {
                insertarAlFinal(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;  // Regreso una referencia a mi mismo
    }
    
    /**
     * @brief Inserta un nuevo dato al final de la lista
     * @param valor El dato que quiero agregar
     */
    void insertarAlFinal(T valor) {
        // Creo un nuevo nodo con el valor
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        
        // Si la lista esta vacia, el nuevo nodo es la cabeza
        if (cabeza == NULL) {
            cabeza = nuevoNodo;
        } else {
            // Si no, busco el ultimo nodo y lo engancho ahi
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;  // Avanzo hasta el final
            }
            actual->siguiente = nuevoNodo;  // Engancho el nuevo nodo al final
        }
        
        tamanio++;  // Incremento el contador
        printf("[Log] Insertando Nodo\n");  // Mensaje sin STL
    }
    
    /**
     * @brief Busca un valor en la lista
     * @param valor El dato que estoy buscando
     * @return true si lo encuentra, false si no
     */
    bool buscar(T valor) const {
        // Recorro toda la lista buscando el valor
        Nodo<T>* actual = cabeza;
        while (actual != NULL) {
            if (actual->dato == valor) {
                return true;  // Lo encontre
            }
            actual = actual->siguiente;
        }
        return false;  // No lo encontre
    }
    
    /**
     * @brief Calcula el promedio de todos los valores
     * @return El promedio como double
     */
    double calcularPromedio() const {
        // Si no hay nodos regreso cero
        if (tamanio == 0) return 0.0;
        
        // Sumo todos los valores
        double suma = 0.0;
        Nodo<T>* actual = cabeza;
        while (actual != NULL) {
            suma += actual->dato;  // Voy sumando cada valor
            actual = actual->siguiente;
        }
        
        return suma / tamanio;  // Divido entre la cantidad de nodos
    }
    
    /**
     * @brief Encuentra y elimina el valor mas bajo
     * @return El valor eliminado
     */
    T eliminarMasBajo() {
        // Si no hay nodos, regreso cero
        if (cabeza == NULL) return T(0);
        
        // Busco el nodo con el valor mas pequenio
        Nodo<T>* actual = cabeza;
        Nodo<T>* minNodo = cabeza;
        Nodo<T>* prevMin = NULL;
        Nodo<T>* prev = NULL;
        
        // Recorro la lista para encontrar el minimo
        while (actual != NULL) {
            if (actual->dato < minNodo->dato) {
                minNodo = actual;      // Guardo el nodo minimo
                prevMin = prev;        // Y su nodo anterior
            }
            prev = actual;
            actual = actual->siguiente;
        }
        
        // Guardo el valor antes de borrar el nodo
        T valorMin = minNodo->dato;
        
        // Si el minimo es la cabeza, actualizo la cabeza
        if (minNodo == cabeza) {
            cabeza = cabeza->siguiente;
        } else {
            // Si no, desconecto el nodo de la lista
            prevMin->siguiente = minNodo->siguiente;
        }
        
        delete minNodo;  // Borro el nodo
        tamanio--;       // Decremento el contador
        
        return valorMin;  // Regreso el valor eliminado
    }
    
    /**
     * @brief Obtiene la cantidad de nodos en la lista
     * @return Numero de elementos
     */
    int obtenerTamanio() const {
        return tamanio;  // Regreso cuantos nodos tengo
    }
    
    /**
     * @brief Verifica si la lista esta vacia
     * @return true si no tiene nodos
     */
    bool estaVacia() const {
        return cabeza == NULL;  // Si la cabeza es null, esta vacia
    }
};

#endif // LISTA_SENSOR_H