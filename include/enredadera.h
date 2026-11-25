#pragma once
#include "obstaculo.h"

class Enredadera : public Obstaculo
{
private:
    float x0;
    float yAnclaje;
    float amplitud;
    float frecuencia;

public:
    Enredadera(float x0, float yAnclaje, float longitud, float amplitud, float frecuencia);

    void actualizar(float t) override;
    void aplicarEfecto(Atenea& atenea) override;

    float getX0() const;
    float getYAnclaje() const;
};
