#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Database {
public:
    static bool connectDatabase();
    static void createTable();
    static bool insertItem(const QString &name, int quantity, double price); // New function
    static bool deleteItem(int id);
};

#endif // DATABASE_H
