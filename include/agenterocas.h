#pragma once
#include "percepcion.h"
#include "razonamiento.h"
#include "accion.h"
#include "aprendizaje.h"
#include "intento.h"

class Atenea;
class Roca;

class AgenteRocas
{
private:
    Percepcion percepcion;
    Razonamiento razonamiento;
    Accion accion;
    Aprendizaje aprendizaje;

    float intervalo;  //segundo entre un lanzamiento y el siguiente
    float espera;     // tiempo acumulado desde el ultimo lanzamiento
    const Roca* rocaEnVuelo;//la roca que lanzo y todavia no cae  (No es suya, es del nivel)
    Intento lanzamiento; // datos del lanzamiento en curso

public:
    AgenteRocas(float intervalo, float velocidadHorizontal, float adelantoInicial, float tasa);

    Roca* actualizar(const Atenea& atenea, float dt, float tiempoNivel);
    float getAdelanto() const;
};
