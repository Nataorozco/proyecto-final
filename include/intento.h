#pragma once
// El registro de una roca lanzada, para que el agente aprenda de ella
struct Intento
{
    float xObjetivo = 0.0f; // donde apunto
    float xAtenea = 0.0f;   // donde estaba atenea cuando la roca cayo
    float velocidadx = 0.0f;// velocidad de atenea cuando se lanzo
    float adelanto = 0.0f;  // adelanto que se uso al apuntar
    bool acerto = false;    // la roca cayo cerca de atenea?
};
