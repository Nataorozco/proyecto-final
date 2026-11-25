#ifndef REMOLINO_H
#define REMOLINO_H
#include "obstaculo.h"

//la fisica
//x = cx + R·cos(ω·t)
//y = cy + R·sen(ω·t)

class Remolino : public Obstaculo
{
public:
    Remolino(float cx, float cy, float radio, float omega);

    void actualizar(float t) override;
    void aplicarEfecto(Atenea& atenea) override;

private:
    float cx; // centro del giro
    float cy;
    float radio;
    float omega; // velocidad angular en rad/s
};

#endif
