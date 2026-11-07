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

    float getX() const;
    float getY() const;

    bool colisionaCon(const Atenea& atenea) const;
};
