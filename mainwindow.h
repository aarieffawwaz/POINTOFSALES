#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onInsertItem();  // Function to insert a new item
    void loadItems();      // Function to load data into QTableWidget
    void onDeleteItem();   // Function to delete a selected item

private:
    Ui::MainWindow *ui;

    // Pointers to UI components (found using findChild)
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_quantity;
    QLineEdit *lineEdit_price;
    QPushButton *btn_insert;
    QPushButton *btn_refresh;
    QPushButton *btn_delete;
    QTableWidget *tableWidget_items;
};

#endif // MAINWINDOW_H
