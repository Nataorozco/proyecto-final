#include "razonamiento.h"
#include <cmath>
#include <stdexcept>

Razonamiento::Razonamiento(float gravedad, float yLanzamiento, float ySuelo, float xMin, float xMax)
    : gravedad(gravedad), yLanzamiento(yLanzamiento), ySuelo(ySuelo),
    xMin(xMin), xMax(xMax), tiempoCaida(0.0f)
{
    if (gravedad <= 0.0f)
        throw std::invalid_argument("Razonamiento: La gravedad debe ser mayor que 0");
    if (ySuelo <= yLanzamiento)
        throw std::invalid_argument("Razonamiento: el suelo debe estar mas abajo que el punto de lanzamiento");
    if (xMin >= xMax)
        throw std::invalid_argument("Razonamiento: xMin debe ser menor que xMax");

//y = yLanzamiento + 1/2 * g * t ^ 2  -> t= raiz (2* (ySuelo - yLanzamiento) / g)
    tiempoCaida = std::sqrt(2.0f * (ySuelo - yLanzamiento) / gravedad);
}

float Razonamiento::calcularObjetivo(const Observacion& obs, float adelanto) const
{
    // donde estara atenea cuando la roca llegue: posicion + velocidad * tiempo
    float objetivo = obs.xAtenea + obs.velocidadx * tiempoCaida * adelanto;

    if (objetivo < xMin)
        objetivo = xMin;
    if (objetivo > xMax)
        objetivo = xMax;

    return objetivo;
}

float Razonamiento::getTiempoCaida() const
{
    return tiempoCaida;
}
