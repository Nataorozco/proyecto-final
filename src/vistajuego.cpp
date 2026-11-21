#include "vistajuego.h"
#include <QTransform>
#include <QTransform>
#include "nivel.h"
#include "nivel2.h"
#include "roca.h"
#include <algorithm>
#include "dificultad.h"

static const int ANCHO_NIVEL = 3000;

VistaJuego::VistaJuego(const ConfiguracionDificultad& config, QWidget *parent)
    : QGraphicsView(parent)
{
    escena = new QGraphicsScene(this);
    setScene(escena);

    setFixedSize(800, 450);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap fondo(QString(RUTA_ASSETS) + "/sprites/nivel-1/fondo.png");
    fondo = fondo.scaledToHeight(450);
    QPixmap fondoEspejo = fondo.transformed(QTransform().scale(-1, 1));

    int copias = ANCHO_NIVEL / fondo.width() + 1;
    for (int i = 0; i < copias; i++)
    {
        QGraphicsPixmapItem *trozo = escena->addPixmap(i % 2 == 0 ? fondo : fondoEspejo);
        trozo->setPos(i * fondo.width(), 0);
    }
    escena->setSceneRect(0, 0, ANCHO_NIVEL, 450);
    juego = new Juego(config);
    atenea = juego->getAtenea();
    nivel = juego->getNivelActual();
    Nivel1 *nivel1 = dynamic_cast<Nivel1*>(nivel);

    // objetos del nivel1 (temporal: luego los creara Nivel1)

    const std::vector<Objeto*>& objetos = nivel->getObjetos();

    for (Objeto *objeto : objetos)
    {
        QPixmap dibujo;
        if (objeto->getTipo() == TipoObjeto::Llave)
            dibujo = QPixmap(QString(RUTA_ASSETS) + "/sprites/nivel-1/llave.png").scaledToHeight(100);
        else
            dibujo = QPixmap(QString(RUTA_ASSETS) + "/sprites/nivel-1/oro.png").scaledToHeight(80);

        QGraphicsPixmapItem *item = escena->addPixmap(dibujo);
        item->setPos(objeto->getX() - dibujo.width() / 2,
                     objeto->getY() -dibujo.height());
        dibujosObjetos.push_back(item);
    }



    QPixmap original(QString(RUTA_ASSETS) + "/sprites/nivel-1/atenea_de_pie.png");
    escalaSprites = 120.0 / original.height();

    spriteDePie = cargarSprite("atenea_de_pie.png");
    spriteCaminar1 = cargarSprite("atenea_caminar_1.png");
    spriteCaminar2 = cargarSprite("atenea_caminar_2.png");
    spriteAgachada = cargarSprite("atenea_agachada.png");
    spriteSaltar = cargarSprite("atenea_saltar.png");

    //Arbol decorativo y enredadera (temporal: luego los creara Nivel1)
    QPixmap arbol = cargarSprite("arbol.png");
    QGraphicsPixmapItem *dibujoArbol = escena->addPixmap(arbol);
    dibujoArbol->setPos(1500 - arbol.width() / 2, 400 - arbol.height());
    dibujoArbol->setZValue(0.2);

   //constructor
    Nivel1 *nivelUno = dynamic_cast<Nivel1*>(nivel1);
    if (nivelUno != nullptr)
    {
        liana = nivelUno->getLiana();
    }

    QPixmap spriteLiana = cargarSprite("liana.png");
    spriteLiana = spriteLiana.scaledToHeight(310, Qt::SmoothTransformation);
    dibujoLiana = escena->addPixmap(spriteLiana);
    dibujoLiana->setTransformOriginPoint(spriteLiana.width() / 2.0f, 0);
    dibujoLiana->setPos(liana->getX0() - spriteLiana.width() / 2.0f, liana->getYAnclaje());
    dibujoLiana->setZValue(0.3);

    dibujoAtenea = escena->addPixmap(spriteDePie);
    dibujoAtenea->setZValue(1);
    dibujoAtenea->setPos(atenea->getX() - spriteDePie.width() / 2,
                         atenea->getY() - spriteDePie.height());

    izquierdaPulsada = false;
    derechaPulsada = false;
    contadorAnimacion = 0;
    mirandoDerecha = true;

    // crea el reloj del juego
    temporalizador = new QTimer(this);
    // cada vez que el reloj suena, llama a actualizar el juego
    connect(temporalizador,&QTimer::timeout, this, &VistaJuego::actualizarJuego);
    // el reloj suena cada 16 milisegundos (unas 60 veces por segundo
    temporalizador->start(16);
    // pide el foco para recibir el teclado

    sonidoOro = new QSoundEffect(this);
    sonidoOro->setSource(QUrl::fromLocalFile(QString(RUTA_ASSETS) + "/sounds/oro.wav"));
    sonidoOro->setVolume(0.8f);
    sonidoGolpe = new QSoundEffect(this);
    sonidoGolpe->setSource(QUrl::fromLocalFile(QString(RUTA_ASSETS) + "/sounds/golpe.wav"));
    sonidoGolpe->setVolume(0.8f);
    enfriamientoGolpe = 0;

    salidaAudio = new QAudioOutput(this);
    salidaAudio->setVolume(0.4f);
    musica = new QMediaPlayer(this);
    musica->setAudioOutput(salidaAudio);
    musica->setSource(QUrl::fromLocalFile(QString(RUTA_ASSETS) + "/sounds/fondo.wav"));
    musica->setLoops(QMediaPlayer::Infinite);
    musica->play();

    oroAnterior = 0;


    setFocus();
}

VistaJuego::~VistaJuego()
{
    delete juego; //juego d
}
// se ejecuta cada 16ms
void VistaJuego::actualizarJuego()
{
    if (derechaPulsada)
        atenea->mover(Direccion::Derecha);
    else if (izquierdaPulsada)
        atenea->mover(Direccion::Izquierda);
    else if (atenea->getEstado() == Estado::Caminando)
        atenea->levantarse();
    //avanza el salto y los temporalizadores (0.16 s = 16 ms)
    atenea->actualizar(0.016f);
    nivel->actualizar(0.016f);

    if (atenea->getOroRecogido() > oroAnterior)
        sonidoOro->play();
    oroAnterior = atenea->getOroRecogido();

    if (nivel->huboGolpe() && enfriamientoGolpe == 0)
    {
        sonidoGolpe->play();
        enfriamientoGolpe = 20; // 30 vueltas = unos 0.5 s sin volver a sonar
    }
    if (enfriamientoGolpe > 0)
        enfriamientoGolpe --;


    const std::vector<Objeto*>& objetos = nivel->getObjetos();
    for (size_t i = 0; i < objetos.size(); i++)
    {
        if (objetos[i]->estaRecogido())
            dibujosObjetos[i]->hide();
    }
    setWindowTitle(QString("Atenea en El Dorado - Oro: %1 Llave: %2")
                .arg(atenea->getOroRecogido())
               .arg(QString(atenea->getTieneLlave() ? "si" : "no")));

    Nivel2 *nivelDos = dynamic_cast<Nivel2*>(nivel);
    if (nivelDos != nullptr)
    {
        setWindowTitle(windowTitle() + QString(" Tiempo: %1").arg(static_cast<int>(nivelDos->getTiempoRestante())));
        if (nivelDos->tiempoAgotado())
        {
            temporalizador->stop();
            musica->stop();
            QGraphicsTextItem *mensaje = escena->addText("Tiempo agotado", QFont("Arial", 44, QFont::Bold));
            mensaje->setDefaultTextColor(Qt::black);
            mensaje->setPos(nivel->getScrollX() + 400 - mensaje->boundingRect().width()/ 2,
                225 - mensaje->boundingRect().height()/2);
            mensaje->setZValue(30);
            return;
        }
    }

    if (liana != nullptr)
    {

        float dx = liana->getX() - liana->getX0();
        float largo = liana->getY() - liana->getYAnclaje();
        float angulo = std::asin(dx / largo) * 180.0f / 3.14159f;
        dibujoLiana->setRotation(-angulo);
    }

    if (liana == nullptr)   //el nivel1 dibuja su liana aparte
        sincronizarObstaculos();

    contadorAnimacion++;

    actualizarSprite();
    dibujoAtenea->setPos(atenea->getX() - dibujoAtenea->pixmap().width() / 2,
                         atenea->getY() - dibujoAtenea->pixmap().height());
    centerOn(nivel->getScrollX() + 400,225);

    if (nivel->estaCompletado())
    {
        if (juego->hayNivelSiguiente())
        {
            juego->siguienteNivel(); //juego nivel actual ++ y rehubica a Atenea
            cargarNivel2();          // la vista dibuja el nivel nuevo
            return;
        }
        temporalizador->stop(); // congela el juego
        musica->stop();
        QGraphicsTextItem *mensaje = escena->addText("¡Juego completado!", QFont("Arial", 28));
        mensaje->setDefaultTextColor(Qt::black);
        mensaje->setPos(nivel->getScrollX() + 210, 190); // en el centro de lo que se ve
        mensaje->setZValue(30);                          //por encima de todo
    }

}
// cuando se presiona una tecla
void VistaJuego::keyPressEvent(QKeyEvent *evento)
{
    if (evento->isAutoRepeat()) //ignora la repeticion automatica
        return;
    if (evento->key() == Qt::Key_Left)
    {
        izquierdaPulsada = true;
        mirandoDerecha = false;
    }
    else if (evento->key() == Qt::Key_Right)
        {
        derechaPulsada = true;
        mirandoDerecha = true;
        }
    else if (evento->key() == Qt::Key_Space)
        atenea->saltar();
    else if (evento->key() == Qt::Key_Down)
        atenea->agacharse();
}
// cuando se suelta la tecla
void VistaJuego::keyReleaseEvent(QKeyEvent *evento)
{
    if (evento->isAutoRepeat()) //ignora la repeticion automatica
        return;
    if (evento->key() == Qt::Key_Left)
        izquierdaPulsada = false;
    else if (evento->key() == Qt::Key_Right)
        derechaPulsada = false;
    else if (evento->key() == Qt::Key_Down)
        atenea->levantarse();
}
QPixmap VistaJuego::cargarSprite(const QString &nombre)
{
    QPixmap original(QString(RUTA_ASSETS) + "/sprites/nivel-1/" + nombre);
    return original.scaled(static_cast<int>(original.width() * escalaSprites),
                           static_cast<int>(original.height() * escalaSprites));
}

void VistaJuego::actualizarSprite()
{
    QPixmap dibujo;

    switch (atenea->getEstado())
    {
    case Estado::DePie:
        dibujo = spriteDePie;
        break;
    case Estado::Caminando:
        // alterna entre los dos dibujos cada 10 vueltas (unos 0.16 s)
        if ((contadorAnimacion / 10) % 2 == 0)
            dibujo = spriteCaminar1;
        else
            dibujo = spriteCaminar2;
        break;
    case Estado::Agachada:
        dibujo = spriteAgachada;
        break;
    case Estado::Saltando:
        dibujo = spriteSaltar;
        break;
    }

    if (!mirandoDerecha)
        dibujo = dibujo.transformed(QTransform().scale(-1, 1));   // voltea de izquierda a derecha

    dibujoAtenea->setPixmap(dibujo);
}

void VistaJuego::cargarNivel2()
{
    escena->clear();          //borra todos los dibujos del nivel 1
    dibujosObjetos.clear();//esos punteros ya no existen
    dibujosObstaculos.clear();
    dibujoLiana = nullptr;
    liana = nullptr;         //el nivel 2 no tiene liana

    nivel = juego->getNivelActual(); // ahora apunta al nivel 2

    QPixmap fondo(QString(RUTA_ASSETS) + "/sprites/nivel-2/fondo.png");
    fondo = fondo.scaled(800, 450);
    escena->addPixmap(fondo);
    escena->setSceneRect(0, 0, 800, 450);
    //aqui agrego el cambio de tamaño de la escena del nivel 2
    fitInView(escena->sceneRect(), Qt::KeepAspectRatio);

    //objetos (oro == pato, llave): misma logica que el nivel1, otra carpeta
    const std::vector<Objeto*>& objetos = nivel->getObjetos();
    for (Objeto *objeto : objetos)
    {
        QPixmap dibujo;
        if (objeto->getTipo() == TipoObjeto::Llave)
            dibujo = QPixmap(QString(RUTA_ASSETS) + "/sprites/nivel-2/llave.png").scaledToHeight(100);
        else
            dibujo = QPixmap(QString(RUTA_ASSETS) + "/sprites/nivel-2/oro.png").scaledToHeight(80);
        QGraphicsPixmapItem *item = escena->addPixmap(dibujo);
        item->setPos(objeto->getX() - dibujo.width()/ 2,
                     objeto->getY() - dibujo.height());
        dibujosObjetos.push_back(item);
    }
    // Obstaculos (el remolino) NOTA BLOQUE DE AQUI ELIMINADO

    dibujoAtenea = escena->addPixmap(spriteDePie);
    dibujoAtenea->setZValue(1);
}

QPixmap VistaJuego::crearDibujo(const Obstaculo *obstaculo) const
{
    if (dynamic_cast<const Roca*>(obstaculo) != nullptr)
        return QPixmap(QString(RUTA_ASSETS) + "/sprites/nivel-2/roca.png").scaledToHeight(40);
    return QPixmap(QString(RUTA_ASSETS) + "/sprites/nivel-2/remolino.png").scaledToHeight(50);
}
void VistaJuego::sincronizarObstaculos()
{
    const std::vector<Obstaculo*>& obstaculos = nivel->getObstaculos();

    //crear el dibujo de los obstaculos nuevos y mover todos
    for (Obstaculo *obstaculo : obstaculos)
    {
        QGraphicsPixmapItem *item;
        auto it = dibujosObstaculos.find(obstaculo);
        if (it == dibujosObstaculos.end())
        {
            item = escena->addPixmap(crearDibujo(obstaculo));
            item->setZValue(0.5);
            dibujosObstaculos[obstaculo] = item;
        }
        else
            item = it->second;

        item->setPos(obstaculo->getX() - item->pixmap().width()/2,
                     obstaculo->getY() - item->pixmap().height()/2);
    }

    // quitar los dibujos de los obstaculos que ya no existen
    for (auto it = dibujosObstaculos.begin(); it != dibujosObstaculos.end();)
    {
        bool existe = std::find(obstaculos.begin(), obstaculos.end(), it->first) != obstaculos.end();
        if (!existe)
        {
            escena->removeItem(it->second);
            delete it->second;
            it = dibujosObstaculos.erase(it);
        }
        else
            ++it;
    }
}
