#include "objeto.h"
#include "atenea.h"
#include <cmath>

static const float MARGEN_X = 40.0f; // que tan cerca  debe estar en el horizontal
static const float MARGEN_Y = 60.0f; // que tan cerca debe estar en vertical

Objeto::Objeto(float x, float y, TipoObjeto tipo)
    : x(x), y(y), tipo(tipo), recogido(false)
{
}

void Objeto::recoger() { recogido = true; }
bool Objeto::estaRecogido() const { return recogido; }
TipoObjeto Objeto::getTipo() const { return tipo; }
float Objeto::getX() const { return x; }
float Objeto::getY() const { return y; }

bool Objeto::colisionaCon(const Atenea &atenea) const
{
    return std::abs(x - atenea.getX()) <MARGEN_X &&
           std::abs(y - atenea.getY()) <MARGEN_Y;
}
