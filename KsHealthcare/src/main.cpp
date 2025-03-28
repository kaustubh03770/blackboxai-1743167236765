#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Ks'Healthcare");
    app.setApplicationVersion("1.0");
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}