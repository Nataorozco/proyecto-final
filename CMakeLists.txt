cmake_minimum_required(VERSION 3.16)

project(AteneaEnElDorado LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

include_directories(include)

add_executable(AteneaEnElDorado
    src/main.cpp
    src/atenea.cpp
    include/atenea.h
    src/vistajuego.cpp
    include/vistajuego.h
    src/objeto.cpp
    include/objeto.h
    src/obstaculo.cpp
    include/obstaculo.h
    src/enredadera.cpp
    include/enredadera.h
    src/nivel.cpp
    include/nivel.h
    src/nivel1.cpp
    include/nivel1.h
    src/roca.cpp
    include/roca.h
    src/remolino.cpp
    include/remolino.h
    src/nivel2.cpp
    include/nivel2.h
    src/juego.cpp
    include/juego.h
    include/observacion.h
    include/intento.h
    include/percepcion.h
    src/percepcion.cpp
    include/razonamiento.h
    src/razonamiento.cpp
    include/accion
    src/accion.cpp
    include/aprendizaje.h
    src/aprendizaje.cpp
    include/agenterocas.h
    src/agenterocas.cpp
    include/dificultad.h
    include/tabladificultad.h
    src/tabladificultad.cpp

)

target_link_libraries(AteneaEnElDorado PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
target_compile_definitions(AteneaEnElDorado PRIVATE RUTA_ASSETS="${CMAKE_SOURCE_DIR}/assets")
