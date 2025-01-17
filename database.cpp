#include "database.h"

bool Database::connectDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // Change to "QMYSQL" if needed
    db.setDatabaseName("pos.db"); // SQLite file (for MySQL, use db.setHostName, etc.)

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    }
    qDebug() << "Database connected!";
    return true;
}

void Database::createTable() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS items ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "quantity INTEGER, "
                    "price REAL)")) {
        qDebug() << "Table creation failed:" << query.lastError().text();
    } else {
        qDebug() << "Table created (or already exists).";
    }
}

bool Database::insertItem(const QString &name, int quantity, double price) {
    QSqlQuery query;
    query.prepare("INSERT INTO items (name, quantity, price) VALUES (:name, :quantity, :price)");
    query.bindValue(":name", name);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Item inserted successfully!";
    return true;
}

bool Database::deleteItem(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM items WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Delete failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Item deleted successfully!";
    return true;
}
