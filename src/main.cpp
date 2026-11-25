#include <QApplication>
#include "vistajuego.h"
#include "tabladificultad.h"
#include <QInputDialog>
#include <QStringList>
#include <vector>
#include <QMessageBox>
#include <exception>
#include "dificultad.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TablaDificultad tabla;

    // se arma la lista que ve el jugador, en el orden facil, normal, dificil
    QStringList nombres;
    std::vector<Dificultad> claves;
    for (const auto& par : tabla.getTabla())
    {
        nombres << QString::fromStdString(par.second.nombre);
        claves.push_back(par.first);
    }

    bool aceptado = false;
    QString elegido = QInputDialog::getItem(nullptr, "Atenea en El Dorado",
                                            "Elige la dificultad:", nombres,
                                            1, false, &aceptado);

    if (!aceptado)
        return 0;            //el jugador cerro el cuadro: se sale sin jugar

    int indice = nombres.indexOf(elegido);

    try
    {
        VistaJuego vista(tabla.obtener(claves[indice]));
        vista.setWindowTitle("Atenea en El Dorado");
        vista.show();
        return app.exec();
    }
    catch (const std::exception& e)

    {

        QMessageBox::critical(nullptr, "Atenea en El Dorado ",
                              QString("No se pudo iniciar el juego:\n") + e.what());

    return 1;
    }
}

