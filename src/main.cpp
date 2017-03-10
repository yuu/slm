#include "slm.h"

#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    slm slm;
    QObject::connect(&slm, &slm::notify_surface, &slm, &slm::change_layout);
    slm.start();

    return app.exec();
}
