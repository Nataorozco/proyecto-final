#pragma once

enum class TipoObjeto { Llave, Oro };

class Objeto
{
private:
    float x;
    float y;
    TipoObjeto tipo;
    bool recogido;

public:
    Objeto(float x, float y, TipoObjeto tipo);

    void recoger();
    bool estaRecogido() const;
    TipoObjeto getTipo() const;
    float getX() const;
    float getY() const;
};
