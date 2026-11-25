#ifndef NIVEL2_H
#define NIVEL2_H

#include "nivel.h"
#include "remolino.h"

struct ConfiguracionDificultad; //nueva

class AgenteRocas;
class Nivel2 : public Nivel
{
public:
    Nivel2(Atenea *atenea, const ConfiguracionDificultad& config);  //linea nueva hoy desde const

    void actualizar(float dt) override;
    bool tiempoAgotado() const;
    float getTiempoRestante() const;
    ~Nivel2() override;

private:
    float tiempo; // tiempo transcurrido, para mover los obstaculos
    float tiempoRestante; // cuenta regresiva
    AgenteRocas *agente;
};


#endif
