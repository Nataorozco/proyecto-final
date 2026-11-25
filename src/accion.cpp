#include "accion.h"
#include "roca.h"

Accion::Accion(float gravedad, float yLanzamiento, float ySuelo, float velocidadHorizontal)
    : gravedad(gravedad), yLanzamiento(yLanzamiento), ySuelo(ySuelo),
    velocidadHorizontal(velocidadHorizontal), desdeIzquierda(true)
{

}

Roca* Accion::lanzar(float xObjetivo, float tiempoCaida, float tiempoNivel)
{
    // alterna el lado: una roca viene de la izquierda, la siguiente de la derecha
    float vx = desdeIzquierda ? velocidadHorizontal : -velocidadHorizontal;
    desdeIzquierda = !desdeIzquierda;

    // la roca avanza vx * tiempoCaida de lado mientras cae,
    // asi que sale desplazada para llegar justo a xObjetivo
    float x0 = xObjetivo - vx * tiempoCaida;

    return new Roca(x0, yLanzamiento, vx, 0.0f, gravedad, tiempoNivel, ySuelo);
}
