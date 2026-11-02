#include "vistajuego.h"

VistaJuego::VistaJuego()
{
    escena = new QGraphicsScene(this);
    setScene(escena);

    setFixedSize(800, 450);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap fondo(QString(RUTA_ASSETS) + "/sprites/nivel-1/fondo.png");
    fondo = fondo.scaledToHeight(450);
    escena->addPixmap(fondo);
    escena->setSceneRect(0, 0, fondo.width(), 450);

    atenea = new Atenea(100.0f, 400.0f);

    QPixmap sprite(QString(RUTA_ASSETS) + "/sprites/nivel-1/atenea_de_pie.png");
    sprite = sprite.scaledToHeight(120);
    dibujoAtenea = escena->addPixmap(sprite);
    dibujoAtenea->setPos(atenea->getX() - sprite.width() / 2,
                         atenea->getY() - sprite.height());
}

VistaJuego::~VistaJuego()
{
    delete atenea;
}
