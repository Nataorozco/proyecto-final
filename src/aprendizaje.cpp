#include "aprendizaje.h"
#include <cmath>
#include <stdexcept>

static const float VELOCIDAD_MINIMA = 50.0f; //px/s: por debajo, se considera quieta
static const float ADELANTO_MAXIMO = 1.5f;

Aprendizaje::Aprendizaje(float adelantoInicial, float tasa, float tiempoCaida)
    : adelanto(adelantoInicial), tasa(tasa), tiempoCaida(tiempoCaida)

{
    if (tasa < 0.0f || tasa > 1.0f)
        throw std::invalid_argument("Aprendizaje: la tasa debe estar entre 0 y 1");
    if (tiempoCaida <= 0.0f)
        throw std::invalid_argument("Aprendizaje: el tiempo de caida debe ser mayor que 0");
    if (adelantoInicial < 0.0f || adelantoInicial > ADELANTO_MAXIMO)
        throw std::invalid_argument("Aprendizaje: el adelanto inicial esta fuera de rango");
}

void Aprendizaje::registrar(const Intento& intento)
{
    historial.push_back(intento);
    corregir(intento);
}

void Aprendizaje::corregir(const Intento& intento)
{
    if (std::fabs(intento.velocidadx) < VELOCIDAD_MINIMA)
        return; // estaba quieta al lanzar: ese intento no dice nada sobre anticipar

    // cuando se movio atenea mientras caia la roca, si se hubiera movido a esa velocidad
    float desplazamiento = intento.velocidadx * tiempoCaida;

    // cuanto se movio la roca (positivo = Atenea quedo a la derecha de donde se apunto)
    float error = intento.xAtenea - intento.xObjetivo;

    // el adelanto que habria sido perfecto para ese intento
    float ideal = intento.adelanto + error / desplazamiento;

    // se acerca a ese ideal, un paso a la vez
    adelanto += tasa * (ideal - adelanto);

    if (adelanto < 0.0f)
        adelanto = 0.0f;
    if (adelanto = ADELANTO_MAXIMO)
        adelanto = ADELANTO_MAXIMO;
}

float Aprendizaje::getAdelanto() const
{
    return adelanto;
}

int Aprendizaje::getNumeroIntentos() const
{
    return static_cast<int>(historial.size());
}
