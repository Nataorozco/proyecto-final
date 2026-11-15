#include "roca.h"
#include "atenea.h"

Roca::Roca(float x0, float y0, float vx, float vy, float g, float tInicio, float ySuelo)
    : Obstaculo(x0, y0, 40.0f, 40.0f),
    x0(x0), y0(y0), vx(vx), vy(vy), g(g), tInicio(tInicio), ySuelo(ySuelo), impacto(false)
{

}

void Roca::actualizar(float t)
{
    if (impacto)
        return;                 //si cayo se mueve mas

    float tiempoDeVuelo = t - tInicio;   // tiempo desde el lanzamiento
    x = x0 + vx * tiempoDeVuelo;         // horizontal: velocidad constante
    y = y0 + vy * tiempoDeVuelo + 0.5f * g * tiempoDeVuelo* tiempoDeVuelo; // vertical: la gravedad acelera

    if (y >= ySuelo)
    {
        y = ySuelo;                     // se queda donde se cayo
        impacto = true;
    }
}

void Roca::aplicarEfecto(Atenea& atenea)
{
    atenea.ralentizar(2.0f);
}

//getter
bool Roca::haImpactado() const { return impacto; }


// esta nota la dejo aqui para mi: x e y (sin x0) no los declaro:
//vienen de Obstaculo y son protected, justo para que la hija los modifique.
//El 0.5f y el f final: son literales float, para que no haya conversión a double.
//if (impacto) return;: sin esa línea, la roca seguiría calculando y atravesaría el suelo.
