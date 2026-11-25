#include "obstaculo.h"
#include "atenea.h"
#include <cmath>

Obstaculo::Obstaculo(float x, float y, float ancho, float alto)
    : x(x), y(y), ancho(ancho), alto(alto)
{
}

Obstaculo::~Obstaculo()
{
}

float Obstaculo::getX() const { return x; }
float Obstaculo::getY() const { return y; }

// Medidas aproximadas de Atenea (las mismas del sprite: 120 px de alto)
static const float ALTURA_ATENEA = 120.0f;
static const float MEDIO_ANCHO_ATENEA = 20.0F;

bool Obstaculo::colisionaCon(const Atenea& atenea) const
{
    // agachada pasa por debajo: no hay choque
    if (atenea.getEstado() == Estado::Agachada)
        return false;

    bool choqueX = std::abs(x - atenea.getX()) < ancho / 2 + MEDIO_ANCHO_ATENEA;
    bool choqueY = (y + alto / 2 > atenea.getY() - ALTURA_ATENEA)
                   && (y - alto / 2 < atenea.getY());

    return choqueX && choqueY;
}
