#include "objeto.h"

Objeto::Objeto(float x, float y, TipoObjeto tipo)
    : x(x), y(y), tipo(tipo), recogido(false)
{
}

void Objeto::recoger() { recogido = true; }
bool Objeto::estaRecogido() const { return recogido; }
TipoObjeto Objeto::getTipo() const { return tipo; }
float Objeto::getX() const { return x; }
float Objeto::getY() const { return y; }
