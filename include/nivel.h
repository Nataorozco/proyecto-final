#ifndef NIVEL_H
#define NIVEL_H

#include <vector>
#include "objeto.h"
#include "obstaculo.h"

class Atenea;

class Nivel
{
public:
    Nivel(Atenea *atenea, float ancho);
    virtual ~Nivel();

    virtual void actualizar(float dt) = 0;

    bool estaCompletado() const;
    float getAncho() const;
    const std::vector<Objeto*>& getObjetos() const;
    const std::vector<Obstaculo*>& getObstaculos() const;

protected:
    void revisarObjetos();
    void revisarColisiones();

    std::vector<Obstaculo*> obstaculos;
    std::vector<Objeto*> objetos;
    Atenea *atenea;
    float ancho;
    bool completado;
};

#endif
