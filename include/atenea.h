#pragma once

enum class Estado { DePie, Caminando, Agachada, Saltando };
enum class Direccion { Izquierda, Derecha };

class Atenea
{
public:
    Atenea(float x, float y);

    void mover(Direccion direccion);
    void saltar();
    void agacharse();
    void levantarse();
    void recogerObjeto();
    void actualizar();

    float getX() const;
    float getY() const;
    Estado getEstado() const;
    int getObjetosRecogidos() const;

private:
    float x;
    float y;
    float velocidad;
    float velocidadY;
    Estado estado;
    int objetosRecogidos;
};
