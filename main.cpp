#include <QApplication>
#include "classgeneratorwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ClassGeneratorWindow program;

    program.show();

    return app.exec();
}
