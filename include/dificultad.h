#pragma once
#include <string>

enum class Dificultad { Facil, Normal, Dificil };

//Todo lo que cambia entre una dificultad y otra, agrupado en un solo objeto
struct ConfiguracionDificultad
{
    std::string nombre;
    float intervaloRocas = 2.5f; //segundo entre las rocas
    float velocidadRocas = 150.0f; //px/s de avance lateral
    float adelantoInicial = 0.0f; //cuanto anticipa el agente al empezar
    float tasaAprendizaje = 0.0f; // 0 = no aprende
    float omegaRemolino = 1.5f;   // rad/s
};
