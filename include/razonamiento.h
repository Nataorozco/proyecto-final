#pragma once
#include "observacion.h"

class Razonamiento
{
private:
    float gravedad; //  px/s^2, la misma que usara la roca
    float yLanzamiento; // altura desde la que sale (arriba de la pantalla)
    float ySuelo;   //altura donde la roca toca el suelo
    float xMin; //limites a los que puede apuntar
    float xMax;
    float tiempoCaida; //segundos que tarda la roca en caer (se calcula una vez)

public:
    Razonamiento(float gravedad, float yLanzamiento, float ySuelo, float xMin, float xMax);

    float calcularObjetivo(const Observacion& obs, float adelanto) const;
    float getTiempoCaida() const;
};
