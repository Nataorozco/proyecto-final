#pragma once
#include<vector>
#include "intento.h"

class Aprendizaje
{
private:
    std::vector<Intento> historial; // todos los intentos, en orden
    float adelanto;                 // cuanto anticipa: 0 = apunta a donde estara
    float tasa;                     // 0 = no aprende; 1 = corrige tood el error de una vez
    float tiempoCaida;              // lo da razonamiento

    void corregir(const Intento& intento);

public:
    Aprendizaje(float adelantoInicial, float tasa, float tiempoCaida);

    void registrar(const Intento& intento);
    float getAdelanto() const;
    int getNumeroIntentos() const;
};
