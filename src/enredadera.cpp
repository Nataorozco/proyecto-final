#include "enredadera.h"
#include <cmath>
#include "atenea.h"

Enredadera::Enredadera(float x0, float yAnclaje, float longitud, float amplitud, float frecuencia)
    : Obstaculo(x0, yAnclaje + longitud, 30.0f, 30.0f),
      x0(x0), yAnclaje(yAnclaje), amplitud(amplitud), frecuencia(frecuencia)
{
}

void Enredadera::actualizar(float t)
{
    x = x0 + amplitud * std::sin(frecuencia * t);
}

void Enredadera::aplicarEfecto(Atenea& atenea)
{
    if (atenea.getX() < x)
        atenea.empujar(-8.0f);
    else
        atenea.empujar(8.0f);
}

float Enredadera::getX0() const { return x0; }
float Enredadera::getYAnclaje() const { return yAnclaje; }
