#pragma once

class Roca; // basta con declararla: aqui solo se devuelve un puntero

class Accion
{
private:
    float gravedad; // la misma que usa el razonamiento
    float yLanzamiento; // desde donde sale la roca (arriba de la pantalla)
    float ySuelo; // donde cae
    float velocidadHorizontal; // px/s con la que la roca avanza de lado
    bool desdeIzquierda;       // alterna el lado de donde viene cada roca

public:
    Accion(float gravedad, float yLanzamiento, float ySuelo, float velocidadHorizontal);

    Roca* lanzar(float xObjetivo, float tiempoCaida, float tiempoNivel);
};
