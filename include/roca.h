#ifndef ROCA_H
#define ROCA_H

#include "obstaculo.h"

class Roca : public Obstaculo
{
public:
    Roca(float x0, float y0, float vx, float vy, float g, float tInicio, float ySuelo);

    void actualizar(float t) override;
    bool haImpactado() const;
    void aplicarEfecto(Atenea& atenea) override;


private:
    float x0; // de donde sale
    float y0;
    float vx; //velocidad horizontal
    float vy; //velocidad vertical inicial (negativa = hacia arriba
    float g; //gravedad en px/s cuadrado
    float tInicio; //en que momento del nivel fue lanzada
    float ySuelo; // altura a la que se considera que cayo
    bool impacto; // ya cayo o no
};

#endif
