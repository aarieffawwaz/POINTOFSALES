#include "mainwindow.h"
#include "ui_mainwindow.h" // Include auto-generated UI header
#include "database.h"
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to their respective slots
    connect(ui->btn_insert, &QPushButton::clicked, this, &MainWindow::onInsertItem);
    connect(ui->btn_refresh, &QPushButton::clicked, this, &MainWindow::loadItems);
    connect(ui->btn_delete, &QPushButton::clicked, this, &MainWindow::onDeleteItem);

    loadItems(); // Load data when the app starts
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onInsertItem() {
    QString name = ui->lineEdit_name->text();
    int quantity = ui->lineEdit_quantity->text().toInt();
    double price = ui->lineEdit_price->text().toDouble();

    if (name.isEmpty()) {
        qDebug() << "Error: Name cannot be empty!";
        return;
    }

    if (Database::insertItem(name, quantity, price)) {
        qDebug() << "New item inserted!";
        loadItems(); // Refresh table after insertion
    }
}

void MainWindow::loadItems() {
    ui->tableWidget_items->clear();
    ui->tableWidget_items->setColumnCount(4);
    ui->tableWidget_items->setHorizontalHeaderLabels({"ID", "Name", "Quantity", "Price"});
    ui->tableWidget_items->setRowCount(0);

    QSqlQuery query("SELECT * FROM items");
    int row = 0;

    while (query.next()) {
        ui->tableWidget_items->insertRow(row);
        ui->tableWidget_items->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->tableWidget_items->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        ui->tableWidget_items->setItem(row, 2, new QTableWidgetItem(query.value("quantity").toString()));
        ui->tableWidget_items->setItem(row, 3, new QTableWidgetItem(query.value("price").toString()));
        row++;
    }
}

void MainWindow::onDeleteItem() {
    int id = ui->lineEdit_id->text().toInt(); // Assuming you have a QLineEdit for ID input

    if (id == 0) {
        qDebug() << "Error: Invalid ID!";
        return;
    }

    if (Database::deleteItem(id)) {
        qDebug() << "Item deleted!";
        loadItems(); // Refresh the table after deletion
    }
}
