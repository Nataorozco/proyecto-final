#include "atenea.h"

// Valores de prueba. Se ajustan al probar el juego.
static const float GRAVEDAD = 0.5f;      // cuanto aumenta la velocidad hacia abajo en cada vuelta
static const float FUERZA_SALTO = -10.0f; // negativo = hacia arriba (en pantalla y crece hacia abajo)
static const float SUELO_Y = 400.0f;// altura del suelo (temporal, luego la dara el nivel)
static const float DURACION_ORO = 5.0f;
static const float FACTOR_LENTO = 0.1f;
static const float FACTOR_QUIETA = 1.5f; //segundos quieta para ganar el impulso
static const float DURACION_IMPULSO = 2.0f; //cuanto dura el impulso
static const float FACTOR_IMPULSO = 1.5f; //multiplica la velocidad


Atenea::Atenea(float x, float y)
    : x(x), y(y), velocidad(5.0f), velocidadY(0.0f),
    estado(Estado::DePie), oroRecogido(0), tieneLlave(false),tiempoOro(0.0f),
    tiempoLento(0.0f), tiempoQuieta(0.0f), tiempoImpulso(0.0f)
{
}

void Atenea::mover(Direccion direccion)
{
    if  (tiempoQuieta >= FACTOR_QUIETA)// estrategica espero antes de moverse
    {
        tiempoImpulso = DURACION_IMPULSO;
        tiempoQuieta = 0.0f;
    }
    float v = velocidad;
    if (tiempoImpulso > 0.0f)
        v *= FACTOR_IMPULSO;
    if (tiempoLento > 0.0f || tiempoOro > 0.0f) //lento por el golpe o por el oro (justa)
        v *= FACTOR_LENTO;

    if (direccion == Direccion::Derecha)
        x += v;
    else
        x -= v;

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
    if (tiempoImpulso > 0.0f) tiempoImpulso -= dt;
    if (estado == Estado::DePie) tiempoQuieta += dt;
    else tiempoQuieta = 0.0f;

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

void Atenea::prepararParaNivel(float nuevaX, float nuevaY)
{
    x = nuevaX;
    y = nuevaY;
    velocidadY = 0.0f;
    estado = Estado::DePie;
    tieneLlave = false; //la llave se uso en el nivel anterior
    tiempoLento = 0.0f;
    tiempoQuieta = 0.0f;
    tiempoImpulso = 0.0f;
}

float Atenea::getX() const { return x; }
float Atenea::getY() const { return y; }
Estado Atenea::getEstado() const { return estado; }
int Atenea::getOroRecogido() const { return oroRecogido; }
bool Atenea::getTieneLlave() const { return tieneLlave; }
