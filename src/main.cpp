#include <QApplication>
#include "vistajuego.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    VistaJuego vista;
    vista.setWindowTitle("Atenea en El Dorado");
    vista.show();

    return app.exec();
}

