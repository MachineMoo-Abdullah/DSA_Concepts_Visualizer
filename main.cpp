#include <QApplication>
#include "mainwindow.h" // Include the MainWindow header

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create an instance of MainWindow
    MainWindow mainWindow;

    // Show the main window
    mainWindow.show();

    // Start the application event loop
    return app.exec();
}
