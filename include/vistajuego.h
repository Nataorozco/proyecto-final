#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H
#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "atenea.h"

class VistaJuego :public QGraphicsView
{
public:
    VistaJuego();
    ~VistaJuego();
private:
    QGraphicsScene *escena;
    QGraphicsPixmapItem *dibujoAtenea;
    Atenea *atenea;
};

#endif // VISTAJUEGO_H
