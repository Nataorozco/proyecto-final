#include "atenea.h"

// Valores de prueba. Se ajustan al probar el juego.
static const float GRAVEDAD = 0.5f;      // cuanto aumenta la velocidad hacia abajo en cada vuelta
static const float FUERZA_SALTO = -10.0f; // negativo = hacia arriba (en pantalla y crece hacia abajo)
static const float SUELO_Y = 400.0f;// altura del suelo (temporal, luego la dara el nivel)
static const float DURACION_ORO = 5.0f;
static const float FACTOR_LENTO = 0.5f;

Atenea::Atenea(float x, float y)
    : x(x), y(y), velocidad(5.0f), velocidadY(0.0f),
    estado(Estado::DePie), oroRecogido(0), tieneLlave(false),tiempoOro(0.0f),
    tiempoLento(0.0f)
{
}

void Atenea::mover(Direccion direccion)
{
    float v = (tiempoLento > 0.0f) ? velocidad * FACTOR_LENTO : velocidad;
    // ...luego: x += v;  o  x -= v;
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
    tiempoOro = DURACION_ORO;
}

void Atenea::recogerLlave()
{
    tieneLlave = true;
}

void Atenea::limitarX(float minimo, float maximo)
{
    if (x < minimo)
        x = minimo;
    if (x > maximo)
        x = maximo;
}

void Atenea::ralentizar(float segundos)
{
    tiempoLento = segundos;
}

void Atenea::empujar(float dx)
{
    x += dx;
}


void Atenea::actualizar(float dt)
{
    if (tiempoOro > 0.0f)   tiempoOro   -= dt;
    if (tiempoLento > 0.0f) tiempoLento -= dt;
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
