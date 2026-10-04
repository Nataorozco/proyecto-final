#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget ventana;
    ventana.setWindowTitle("Atenea en El Dorado");
    ventana.resize(800, 450);
    ventana.show();

    return app.exec();
}
