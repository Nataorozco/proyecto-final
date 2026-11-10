#include "nivel1.h"
#include "atenea.h"

Nivel1::Nivel1(Atenea *atenea)
    : Nivel(atenea, 3000.0f), liana(nullptr), tiempo(0.0f), scrollX(0.0f)
{
    objetos.push_back(new Objeto(700.0f, 400.0f, TipoObjeto::Oro));
    objetos.push_back(new Objeto(2800.0f, 400.0f, TipoObjeto::Llave));

    // USA LOS MISMOS NUMEROS que tiene ahora linea new Enredadera(...) de VistaJuego
    liana = new Enredadera(1900.0f, 0.0f, 300.0f, 120.0f, 2.0f);
    obstaculos.push_back(liana);
}

void Nivel1::actualizar(float dt)
{
    tiempo += dt;

    for (size_t i = 0; i < obstaculos.size(); i++)
        obstaculos[i]->actualizar(tiempo);

    atenea->limitarX(40.0f, ancho - 40.0f);
    revisarObjetos();
    revisarColisiones();

    if (atenea->getTieneLlave())
        completado = true;
    avanzarScroll();
}

Enredadera* Nivel1::getLiana() const { return liana; }

void Nivel1::avanzarScroll()
{
    const float ANCHO_VENTANA = 800.0f;
    scrollX = atenea->getX() - ANCHO_VENTANA / 2; // ATENEA QUEDA EN EL CENTRO
    if (scrollX < 0)
        scrollX = 0;
    if(scrollX > ancho - ANCHO_VENTANA)
        scrollX = ancho - ANCHO_VENTANA;
}
float Nivel1::getScrollX() const { return scrollX; }
