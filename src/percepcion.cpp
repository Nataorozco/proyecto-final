#include "percepcion.h"
#include "atenea.h"

Percepcion::Percepcion ()
    : xAnterior(0.0f), primeraVez(true)
{

}

void Percepcion::percibir(const Atenea& atenea, float dt)
{
    if (dt <= 0.0f)
        return;        //sin tiempo no se puede calcular una velocidad

    float x = atenea.getX();

    if (primeraVez)
    {
        xAnterior = x;   //en la primera vuelta no hay antes
        primeraVez = false;
    }

    ultima.xAtenea = x;
    ultima.velocidadx = (x - xAnterior) / dt; // distancia / tiempo
    xAnterior = x;
}

Observacion Percepcion::getObservacion() const
{
    return ultima;
}
