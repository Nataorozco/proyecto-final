#pragma once
#include <map>
#include "dificultad.h"

class TablaDificultad
{
private:
    std::map<Dificultad, ConfiguracionDificultad> tabla;

public:
    TablaDificultad();

    const ConfiguracionDificultad& obtener(Dificultad dificultad) const;
    const std::map<Dificultad, ConfiguracionDificultad>& getTabla() const;
};
