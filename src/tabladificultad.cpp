#include "tabladificultad.h"

TablaDificultad::TablaDificultad()
{
    //                         NOMBRE    INTERVALO  VEL  ADELANTO  TASA  OMEGA
    tabla[Dificultad::Facil] = {"Facil",  3.5f,    80.0f,  0.0f,   0.0f,  1.0f};
    tabla[Dificultad::Normal] = {"Normal", 2.5f,    150.0f, 0.5f,   0.1f,  1.5f};
    tabla[Dificultad::Dificil] = {"Dificil", 1.8f,   220.0f, 0.8f,   0.5f,  2.2f};
}

const ConfiguracionDificultad& TablaDificultad::obtener(Dificultad dificultad) const
{
    return tabla.at(dificultad); // lanza std::out_of_range si la clave no existe
}

const std::map<Dificultad, ConfiguracionDificultad>& TablaDificultad::getTabla() const
{
    return tabla;
}
