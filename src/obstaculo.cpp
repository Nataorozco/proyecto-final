#include "obstaculo.h"

Obstaculo::Obstaculo(float x, float y, float ancho, float alto)
    : x(x), y(y), ancho(ancho), alto(alto)
{
}

Obstaculo::~Obstaculo()
{
}

float Obstaculo::getX() const { return x; }
float Obstaculo::getY() const { return y; }
