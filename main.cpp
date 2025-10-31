/**
 * 
 * Este programa demuestra el uso de polimorfismo, listas enlazadas genericas
 * y gestion de memoria dinamica para un sistema de monitoreo de sensores
 * SIN USAR LA STL (solo C puro con clases de C++)
 */

#include <cstdio>   // Para scanf, printf (C puro)
#include <cstring>  // Para strcmp (C puro)
#include "ListaGestion.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "SimuladorArduino.h"

/**
 * @brief Limpia el buffer de entrada para evitar problemas con scanf
 */
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Limpio hasta encontrar newline
}

/**
 * @brief Muestra el menu principal del sistema
 */
void mostrarMenu() {
    printf("\n========================================\n");
    printf("   Sistema IoT - Gestion de Sensores   \n");
    printf("========================================\n");
    printf("1. Crear Sensor de Temperatura\n");
    printf("2. Crear Sensor de Presion\n");
    printf("3. Registrar Lectura Manual\n");
    printf("4. Simular Lecturas desde Arduino\n");
    printf("5. Procesar Todos los Sensores (Polimorfismo)\n");
    printf("6. Mostrar Info de Todos los Sensores\n");
    printf("7. Info del Puerto Serial\n");
    printf("0. Salir (Liberar Memoria)\n");
    printf("========================================\n");
    printf("Opcion: ");
}

/**
 * @brief Funcion principal del programa
 * @return 0 si todo sale bien
 */
int main() {
    // Creo la lista principal que manejara todos los sensores
    // Esta usa polimorfismo para guardar diferentes tipos de sensores
    ListaGestion* sistema = new ListaGestion();
    
    // Creo el simulador de Arduino
    SimuladorArduino arduino;
    
    printf("\n--- Sistema IoT de Monitoreo Polimorfico ---\n\n");
    
    int opcion;
    bool salir = false;
    
    // Loop principal del programa
    while (!salir) {
        mostrarMenu();
        
        // Leo la opcion usando scanf (C puro, sin cin)
        if (scanf("%d", &opcion) != 1) {
            printf("\n[Error] Opcion invalida. Intenta de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();
        
        // Proceso la opcion seleccionada
        switch (opcion) {
            case 1: {
                // Crear sensor de temperatura
                char id[50];
                printf("\nIngresa el ID del sensor (ej: T-001): ");
                scanf("%49s", id);  // Leo sin espacios
                limpiarBuffer();
                
                // Creo el sensor usando new (memoria dinamica)
                SensorTemperatura* nuevoSensor = new SensorTemperatura(id);
                
                // Lo agrego a la lista de gestion usando polimorfismo
                // Guardo el puntero como SensorBase* aunque sea SensorTemperatura*
                sistema->agregarSensor(nuevoSensor);
                
                printf("Sensor creado exitosamente!\n");
                break;
            }
            
            case 2: {
                // Crear sensor de presion
                char id[50];
                printf("\nIngresa el ID del sensor (ej: P-105): ");
                scanf("%49s", id);
                limpiarBuffer();
                
                // Creo el sensor usando new (memoria dinamica)
                SensorPresion* nuevoSensor = new SensorPresion(id);
                
                // Lo agrego a la lista de gestion usando polimorfismo
                sistema->agregarSensor(nuevoSensor);
                
                printf("Sensor creado exitosamente!\n");
                break;
            }
            
            case 3: {
                // Registrar lectura manual
                if (sistema->obtenerTamanio() == 0) {
                    printf("\n[Aviso] No hay sensores creados. Crea uno primero.\n");
                    break;
                }
                
                char id[50];
                printf("\nIngresa el ID del sensor: ");
                scanf("%49s", id);
                limpiarBuffer();
                
                // Busco el sensor en la lista
                SensorBase* sensor = sistema->buscarSensor(id);
                
                if (sensor == NULL) {
                    printf("[Error] Sensor no encontrado.\n");
                    break;
                }
                
                // Ahora necesito saber de que tipo es el sensor para registrar correctamente
                // Uso dynamic_cast para hacer downcasting seguro
                
                SensorTemperatura* tempSensor = dynamic_cast<SensorTemperatura*>(sensor);
                if (tempSensor != NULL) {
                    // Es un sensor de temperatura
                    float valor;
                    printf("Ingresa la temperatura (float): ");
                    if (scanf("%f", &valor) != 1) {
                        printf("[Error] Valor invalido.\n");
                        limpiarBuffer();
                        break;
                    }
                    limpiarBuffer();
                    
                    tempSensor->registrarLectura(valor);
                    break;
                }
                
                SensorPresion* presSensor = dynamic_cast<SensorPresion*>(sensor);
                if (presSensor != NULL) {
                    // Es un sensor de presion
                    int valor;
                    printf("Ingresa la presion (int): ");
                    if (scanf("%d", &valor) != 1) {
                        printf("[Error] Valor invalido.\n");
                        limpiarBuffer();
                        break;
                    }
                    limpiarBuffer();
                    
                    presSensor->registrarLectura(valor);
                    break;
                }
                
                printf("[Error] Tipo de sensor desconocido.\n");
                break;
            }
            case 4: {
                // Simular lecturas desde Arduino
                if (sistema->obtenerTamanio() == 0) {
                    printf("\n[Aviso] No hay sensores creados. Crea uno primero.\n");
                    break;
                }
                
                char id[50];
                int cantidad;
                
                printf("\nIngresa el ID del sensor: ");
                scanf("%49s", id);
                limpiarBuffer();
                
                // Busco el sensor
                SensorBase* sensor = sistema->buscarSensor(id);
                
                if (sensor == NULL) {
                    printf("[Error] Sensor no encontrado.\n");
                    break;
                }
                
                printf("Cuantas lecturas quieres simular? ");
                if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                    printf("[Error] Cantidad invalida.\n");
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();
                
                // Verifico el tipo y simulo las lecturas
                SensorTemperatura* tempSensor = dynamic_cast<SensorTemperatura*>(sensor);
                if (tempSensor != NULL) {
                    printf("\n[Simulacion] Generando %d lecturas de temperatura...\n", cantidad);
                    for (int i = 0; i < cantidad; i++) {
                        float temp = arduino.leerTemperatura();
                        tempSensor->registrarLectura(temp);
                    }
                    break;
                }
                
                SensorPresion* presSensor = dynamic_cast<SensorPresion*>(sensor);
                if (presSensor != NULL) {
                    printf("\n[Simulacion] Generando %d lecturas de presion...\n", cantidad);
                    for (int i = 0; i < cantidad; i++) {
                        int pres = arduino.leerPresion();
                        presSensor->registrarLectura(pres);
                    }
                    break;
                }
                
                printf("[Error] Tipo de sensor desconocido.\n");
                break;
            }
            
            case 5: {
                // Procesar todos los sensores (aqui ocurre el polimorfismo)
                if (sistema->obtenerTamanio() == 0) {
                    printf("\n[Aviso] No hay sensores para procesar.\n");
                    break;
                }
                
                // Este metodo llamara a procesarLectura() de cada sensor
                // y cada uno ejecutara su propia version del metodo
                sistema->procesarTodos();
                break;
            }
            
            case 6: {
                // Mostrar informacion de todos los sensores
                if (sistema->obtenerTamanio() == 0) {
                    printf("\n[Aviso] No hay sensores registrados.\n");
                    break;
                }
                
                sistema->imprimirTodos();
                break;
            }
            
            case 7: {
                // Mostrar info del puerto serial
                arduino.mostrarInfoPuerto();
                break;
            }
            
            case 0: {
                // Salir del programa
                printf("\n[Sistema] Cerrando y liberando memoria...\n");
                salir = true;
                break;
            }
            
            default:
                printf("\n[Error] Opcion no valida. Intenta de nuevo.\n");
                break;
        }
    }
    
    // Libero la memoria del sistema
    // Esto automaticamente liberara todos los sensores gracias al destructor
    delete sistema;
    
    printf("\nGracias por usar el Sistema IoT!\n");
    
    return 0;  // Termino el programa exitosamente
}