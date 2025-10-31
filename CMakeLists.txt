# Version minima de CMake que necesito
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje que uso
project(SistemaIoTSensores CXX)

# Uso el estandar C++11 porque necesito algunas caracteristicas modernas
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Le digo a CMake donde estan mis archivos de cabecera (.h)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Lista de todos los archivos fuente que tengo
set(SOURCES
    src/main.cpp
)

# Creo el ejecutable con el nombre del proyecto y los archivos fuente
add_executable(${PROJECT_NAME} ${SOURCES})

# Mensaje para confirmar que la configuracion esta lista
message(STATUS "Configuracion completada para ${PROJECT_NAME}")
message(STATUS "Archivos de cabecera en: ${PROJECT_SOURCE_DIR}/include")
message(STATUS "Archivos fuente en: ${PROJECT_SOURCE_DIR}/src")
```

---

### 📄 **Doxyfile**
```
# Archivo de configuracion de Doxygen para el proyecto
# Version: Doxygen 1.15.0

PROJECT_NAME           = "Sistema IoT de Sensores"
PROJECT_NUMBER         = "1.0"
PROJECT_BRIEF          = "Sistema de gestion polimorfica de sensores SIN STL"
OUTPUT_DIRECTORY       = docs

INPUT                  = include src README.md
FILE_PATTERNS          = *.h *.cpp *.md
RECURSIVE              = YES

GENERATE_HTML          = YES
HTML_OUTPUT            = html
GENERATE_LATEX         = NO

EXTRACT_ALL            = YES
EXTRACT_PRIVATE        = YES
EXTRACT_STATIC         = YES
CLASS_DIAGRAMS         = YES
DIRECTORY_GRAPH        = YES

WARNINGS               = YES
WARN_IF_UNDOCUMENTED   = YES
WARN_IF_DOC_ERROR      = YES