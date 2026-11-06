#include "enredadera.h"
#include <cmath>

Enredadera::Enredadera(float x0, float yAnclaje, float longitud, float amplitud, float frecuencia)
    : Obstaculo(x0, yAnclaje + longitud, 30.0f, 30.0f),
      x0(x0), yAnclaje(yAnclaje), amplitud(amplitud), frecuencia(frecuencia)
{
}

void Enredadera::actualizar(float t)
{
    x = x0 + amplitud * std::sin(frecuencia * t);
}

float Enredadera::getX0() const { return x0; }
float Enredadera::getYAnclaje() const { return yAnclaje; }
