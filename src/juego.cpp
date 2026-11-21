#include "juego.h"
#include "atenea.h"
#include "nivel1.h"
#include "nivel2.h"
#include "dificultad.h"

//constructor crea a Atenea y a los dos niveles. El vector guarda Nivel* asi que Nivel1*
//y Nivel2* entran como Nivel*

Juego::Juego(const ConfiguracionDificultad& config)
    : atenea(new Atenea(100.0f, 400.0f)), nivelActual(0)
{
    niveles.push_back(new Nivel1(atenea));
    niveles.push_back(new Nivel2(atenea, config));
}

//destructor quien destruye primero los niveles luego a Atenea:

Juego::~Juego()
{
    for (size_t i = 0; i < niveles.size(); i++)
        delete niveles[i];
    delete atenea;
}

//actualizar y cambiar de nivel

void Juego::actualizar(float dt)
{
    atenea->actualizar(dt);
    niveles[nivelActual]->actualizar(dt);
}

bool Juego::hayNivelSiguiente() const
{
    return nivelActual + 1 < static_cast<int>(niveles.size());
}

void Juego::siguienteNivel()
{
    if (!hayNivelSiguiente())
        return;

    nivelActual++;
    atenea->prepararParaNivel(100.0f, 400.0f);
}
 //getters
Atenea* Juego::getAtenea() const { return atenea; }
Nivel* Juego::getNivelActual() const { return niveles[nivelActual]; }
int Juego::getNumeroNivel() const { return nivelActual + 1; }




