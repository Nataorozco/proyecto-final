#pragma once
#include "observacion.h"

class Atenea; // basta con declararla aqui solo se usa como referencia

class Percepcion
{
private:
    float xAnterior;  //posicion de atenea en la vuelta anterior
    bool primeraVez;  //para no calcular velocidad con un dato vacio
    Observacion ultima;  // lo ultimo que se percibio
public:
    Percepcion();
    void percibir(const Atenea& atenea, float dt); // se llama en cada vuelta
    Observacion getObservacion() const;    // lo consulta el razonamiento
};
