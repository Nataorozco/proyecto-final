#include "nivel2.h"
#include "atenea.h"

//el constructor llama al de la base con el ancho 800 y crea lo que hay en el nivel

Nivel2::Nivel2(Atenea *atenea)
    : Nivel(atenea, 800.0f), tiempo(0.0f), tiempoRestante(60.0f)
{
    objetos.push_back(new Objeto(150.0f, 400.0f, TipoObjeto::Oro));
    objetos.push_back(new Objeto(700.0f, 400.0f, TipoObjeto::Llave));

    obstaculos.push_back(new Remolino(400.0f, 300.0f, 100.0f, 1.5f));
}

void Nivel2::actualizar(float dt)
{
    tiempo += dt;
    tiempoRestante -= dt;
    if (tiempoRestante < 0.0f)
        tiempoRestante = 0.0f;

    for (size_t i = 0; i < obstaculos.size(); i++)
        obstaculos[i]->actualizar(tiempo);

    atenea->limitarX(40.0f, ancho - 40.0f);
    revisarObjetos();
    revisarColisiones();

    if (atenea->getTieneLlave())
        completado = true;
}

//getters
bool Nivel2::tiempoAgotado() const { return tiempoRestante <= 0.0f; }
float Nivel2::getTiempoRestante() const { return tiempoRestante; }
