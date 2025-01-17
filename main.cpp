#include "mainwindow.h"
#include "database.h" // Include the new database header
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if (!Database::connectDatabase()) {
        return -1; // Stop if database fails to connect
    }

    Database::createTable(); // Ensure the table exists

    MainWindow w;
    w.show(); // Show the main window

    return a.exec();
}
