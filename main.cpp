#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // verschiedene ideen wie die UI aussehen könnte
    // * ergibnisse fliegen
    // ** unten oder rechts ist eine aufgabe
    // ** ergebnisse fliegen von einer seite zur anderen seite und können
    //    per drag and drop drauf geschoben werden

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}
