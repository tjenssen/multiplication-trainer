#include "mainwindow.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // verschiedene ideen wie die UI aussehen k�nnte
    // * ergibnisse fliegen
    // ** unten oder rechts ist eine aufgabe
    // ** ergebnisse fliegen von einer seite zur anderen seite und k�nnen
    //    per drag and drop drauf geschoben werden

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}
