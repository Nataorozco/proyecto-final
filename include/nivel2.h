#ifndef NIVEL2_H
#define NIVEL2_H

#include "nivel.h"
#include "remolino.h"

class Nivel2 : public Nivel
{
public:
    Nivel2(Atenea *atenea);

    void actualizar(float dt) override;
    bool tiempoAgotado() const;
    float getTiempoRestante() const;

private:
    float tiempo; // tiempo transcurrido, para mover los obstaculos
    float tiempoRestante; // cuenta regresiva
};


#endif
