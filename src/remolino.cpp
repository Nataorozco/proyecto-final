#include "remolino.h"
#include <cmath>
#include "atenea.h"
//aqui uso <cmath> para cos y sin

Remolino::Remolino(float cx, float cy, float radio, float omega)
    :Obstaculo(cx + radio, cy, 60.0f, 60.0f),
    cx(cx), cy(cy), radio(radio), omega(omega)
{

}
//la fisica
void Remolino::actualizar(float t)
{
    x = cx + radio * std::cos(omega * t);
    y = cy + radio * std::sin(omega * t);
}

void Remolino::aplicarEfecto(Atenea& atenea)
{
    atenea.ralentizar(2.0f);
}
// omega * t es un angulo de radianes std::cos y std::sin reciben radianes, no grados.
// en pantalla y crece hacia abajo, asi que el remolino gira en sentido horario
// al verse. No cambia nada para el choque.
// Es el tercer hijo de obstaculo. con esta ya estan las 3 fisicas: Enredadera, (pendulo),
// Roca(parabolico) y remolino (circular).
