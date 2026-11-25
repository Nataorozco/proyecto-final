#pragma once

class Atenea;

class Obstaculo
{
protected:
    float x;
    float y;
    float ancho;
    float alto;

public:
    Obstaculo(float x, float y, float ancho, float alto);
    virtual ~Obstaculo();

    virtual void actualizar(float t) = 0;
    virtual void aplicarEfecto(Atenea& atenea) = 0;
    virtual bool estaActivo() const { return true; } // por defecto un obstaculo siempre esta cativo

    float getX() const;
    float getY() const;

    bool colisionaCon(const Atenea& atenea) const;
};
