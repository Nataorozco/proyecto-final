#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H
#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "atenea.h"
#include <QTimer>
#include <QKeyEvent>

class VistaJuego :public QGraphicsView
{
    Q_OBJECT

public:
    VistaJuego();
    ~VistaJuego();
private:
    QGraphicsScene *escena;
    QGraphicsPixmapItem *dibujoAtenea;
    Atenea *atenea;
    QTimer *temporalizador;
    bool izquierdaPulsada;
    bool derechaPulsada;
    QPixmap cargarSprite(const QString &nombre);
    void actualizarSprite();
    QPixmap spriteDePie;
    QPixmap spriteCaminar1;
    QPixmap spriteCaminar2;
    QPixmap spriteAgachada;
    QPixmap spriteSaltar;
    float escalaSprites;
    int contadorAnimacion;
    bool mirandoDerecha;

protected:
    void keyPressEvent(QKeyEvent *evento) override;
    void keyReleaseEvent(QKeyEvent *evento) override;

private slots:
    void actualizarJuego();

};

#endif // VISTAJUEGO_H
