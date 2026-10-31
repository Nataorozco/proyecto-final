#include "atenea.h"

// Valores de prueba. Se ajustan al probar el juego.
static const float GRAVEDAD = 0.5f;      // cuanto aumenta la velocidad hacia abajo en cada vuelta
static const float FUERZA_SALTO = -10.0f; // negativo = hacia arriba (en pantalla y crece hacia abajo)
static const float SUELO_Y = 300.0f;     // altura del suelo (temporal, luego la dara el nivel)

Atenea::Atenea(float x, float y)
    : x(x), y(y), velocidad(5.0f), velocidadY(0.0f),
    estado(Estado::DePie), oroRecogido(0), tieneLlave(false)
{
}

void Atenea::mover(Direccion direccion)
{
    if (direccion == Direccion::Derecha)
        x += velocidad;
    else
        x -= velocidad;

    if (estado == Estado::DePie)
        estado = Estado::Caminando;
}

void Atenea::saltar()
{
    if (estado == Estado::Saltando || estado == Estado::Agachada)
        return;

    estado = Estado::Saltando;
    velocidadY = FUERZA_SALTO;
}

void Atenea::agacharse()
{
    if (estado != Estado::Saltando)
        estado = Estado::Agachada;
}

void Atenea::levantarse()
{
    if (estado == Estado::Agachada || estado == Estado::Caminando)
        estado = Estado::DePie;
}

void Atenea::recogerOro()
{
    oroRecogido++;
}

void Atenea::recogerLlave()
{
    tieneLlave = true;
}


void Atenea::actualizar()
{
    if (estado != Estado::Saltando)
        return;

    velocidadY += GRAVEDAD;
    y += velocidadY;

    if (y >= SUELO_Y)
    {
        y = SUELO_Y;
        velocidadY = 0.0f;
        estado = Estado::DePie;
    }
}

float Atenea::getX() const { return x; }
float Atenea::getY() const { return y; }
Estado Atenea::getEstado() const { return estado; }
int Atenea::getOroRecogido() const { return oroRecogido; }
bool Atenea::getTieneLlave() const { return tieneLlave; }
