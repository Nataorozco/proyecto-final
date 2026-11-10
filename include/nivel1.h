#ifndef NIVEL1_H
#define NIVEL1_H

#include "nivel.h"
#include "enredadera.h"

class Nivel1 : public Nivel
{
public:
    Nivel1(Atenea *atenea);

    void actualizar(float dt) override;
    Enredadera* getLiana() const;
    void avanzarScroll();
    float getScrollX() const;

private:
    Enredadera *liana;
    float tiempo;
    float scrollX;
};

#endif
