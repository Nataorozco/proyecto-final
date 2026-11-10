#include "nivel.h"
#include "atenea.h"

Nivel::Nivel(Atenea *atenea, float ancho)
    : atenea(atenea), ancho(ancho), completado(false)
{
}

Nivel::~Nivel()
{
    for (size_t i = 0; i < obstaculos.size(); i++)
        delete obstaculos[i];
    for (size_t i = 0; i < objetos.size(); i++)
        delete objetos[i];
}

void Nivel::revisarObjetos()
{
    for (size_t i = 0; i < objetos.size(); i++)
    {
        Objeto *objeto = objetos[i];
        if (!objeto->estaRecogido() && objeto->colisionaCon(*atenea))
        {
            objeto->recoger();
            if (objeto->getTipo() == TipoObjeto::Oro)
                atenea->recogerOro();
            else
                atenea->recogerLlave();
        }
    }
}

void Nivel::revisarColisiones()
{
    for (size_t i = 0; i < obstaculos.size(); i++)
    {
        if (obstaculos[i]->colisionaCon(*atenea))
        {
            if (atenea->getX() < obstaculos[i]->getX())
                atenea->empujar(-8.0f);
            else
                atenea->empujar(8.0f);
        }
    }
}

bool Nivel::estaCompletado() const { return completado; }
float Nivel::getAncho() const { return ancho; }
const std::vector<Objeto*>& Nivel::getObjetos() const { return objetos; }
const std::vector<Obstaculo*>& Nivel::getObstaculos() const { return obstaculos; }
