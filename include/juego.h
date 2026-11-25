#ifndef JUEGO_H
#define JUEGO_H

#include <vector>

class Atenea;
class Nivel;
struct ConfiguracionDificultad;

class Juego
{
public:
    Juego(const ConfiguracionDificultad& config);
    ~Juego();

    void actualizar(float dt);
    bool hayNivelSiguiente() const;
    void siguienteNivel();

    Atenea* getAtenea() const;
    Nivel* getNivelActual() const;
    int getNumeroNivel() const;  //1 o 2

private:
    Atenea *atenea;
    std::vector<Nivel*> niveles;
    int nivelActual;     //posicion en el vector: 0 o 1
};

#endif
