#include "agenterocas.h"
#include "atenea.h"
#include "roca.h"
#include <cmath>
#include <stdexcept>

// El entorno fisico del nivel, definido una sola vez para todas las partes
static const float GRAVEDAD_ROCA = 800.0f; //px/ s ^ 2
static const float Y_LANZAMIENTO = -50.0f; // arriba de la pantalla
static const float Y_SUELO = 380.0f;       // centro de la roca al tocar el suelo (400 - 40/2)
static const float X_MIN = 40.0f;
static const float X_MAX = 760.0f;
static const float TOLERANCIA = 50.0f;    // si cae a menos de esto de Atenea, acerto

AgenteRocas::AgenteRocas(float intervalo, float velocidadHorizontal, float adelantoInicial, float tasa)
    : razonamiento(GRAVEDAD_ROCA, Y_LANZAMIENTO, Y_SUELO, X_MIN, X_MAX),
    accion(GRAVEDAD_ROCA, Y_LANZAMIENTO, Y_SUELO, velocidadHorizontal),
    aprendizaje(adelantoInicial, tasa, razonamiento.getTiempoCaida()),
    intervalo(intervalo), espera(0.0f), rocaEnVuelo(nullptr)
{
    if (velocidadHorizontal < 0.0f)
        throw std::invalid_argument("AgenteRocas: la velocidad horizontal no puede ser negativa");
    if (intervalo <= razonamiento.getTiempoCaida())
        throw std::invalid_argument("AgenteRocas: el intervalo debe ser mayor que el tiempo de caida");

}

Roca* AgenteRocas::actualizar(const Atenea& atenea, float dt, float tiempoNivel)
{
    // PERCEPCION: se mira a Atenea en cada vuelta
    percepcion.percibir(atenea, dt);

    // APRENDIZAJE: si la roca lanzada ya cayo, se revisa si acerto
    if (rocaEnVuelo != nullptr && rocaEnVuelo->haImpactado())
    {
        lanzamiento.xAtenea = atenea.getX();
        lanzamiento.acerto = std::fabs(lanzamiento.xAtenea - lanzamiento.xObjetivo) < TOLERANCIA;
        aprendizaje.registrar(lanzamiento);
        rocaEnVuelo = nullptr;
    }

    // se espera en intervalo, y no se lanza otra mientras una esta en el aire
    espera += dt;
    if (espera < intervalo || rocaEnVuelo != nullptr)
        return nullptr;
    espera = 0.0f;

    //RAZONAMIENTO: a donde apuntar
    Observacion obs = percepcion.getObservacion();
    float adelanto = aprendizaje.getAdelanto();
    float objetivo = razonamiento.calcularObjetivo(obs, adelanto);

    // se anota lo que hizo, para aprender cuando la roca caiga
    lanzamiento.xObjetivo = objetivo;
    lanzamiento.velocidadx = obs.velocidadx;
    lanzamiento.adelanto = adelanto;

    // ACCION: se crea la roca
    Roca* roca = accion.lanzar(objetivo, razonamiento.getTiempoCaida(), tiempoNivel);
    rocaEnVuelo = roca;
    return roca;
}
float AgenteRocas::getAdelanto() const
{
    return aprendizaje.getAdelanto();
}
