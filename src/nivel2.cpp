#include "nivel2.h"
#include "atenea.h"
#include "agenterocas.h"
#include "roca.h"
#include "dificultad.h"
//el constructor llama al de la base con el ancho 800 y crea lo que hay en el nivel

Nivel2::Nivel2(Atenea *atenea, const ConfiguracionDificultad& config)
    : Nivel(atenea, 800.0f), tiempo(0.0f), tiempoRestante(60.0f),
    agente(new AgenteRocas(config.intervaloRocas, config.velocidadRocas,
                           config.adelantoInicial, config.tasaAprendizaje))

{
    objetos.push_back(new Objeto(150.0f, 400.0f, TipoObjeto::Oro));
    objetos.push_back(new Objeto(700.0f, 400.0f, TipoObjeto::Llave));

    obstaculos.push_back(new Remolino(400.0f, 300.0f, 100.0f, config.omegaRemolino));
}

Nivel2::~Nivel2()
{
    delete agente;
}

void Nivel2::actualizar(float dt)
{
    tiempo += dt;
    tiempoRestante -= dt;
    if (tiempoRestante < 0.0f)
        tiempoRestante = 0.0f;

    for (size_t i = 0; i < obstaculos.size(); i++)
        obstaculos[i]->actualizar(tiempo);

    Roca* nueva = agente->actualizar(*atenea, dt, tiempo);
    if (nueva != nullptr)
        obstaculos.push_back(nueva); // upcast: Roca* entra como Obstaculo*

    atenea->limitarX(40.0f, ancho - 40.0f);
    revisarObjetos();
    revisarColisiones();
    retirarInactivos();

    if (atenea->getTieneLlave())
        completado = true;
}

//getters
bool Nivel2::tiempoAgotado() const { return tiempoRestante <= 0.0f; }
float Nivel2::getTiempoRestante() const { return tiempoRestante; }
