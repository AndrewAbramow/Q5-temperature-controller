#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtSql/QSqlDatabase>

#include "graph.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int t = 0;

private slots:
    void on_read_temperature_button_clicked();
    void on_graph_button_clicked();
    void on_write_button_clicked();

private:
    Ui::MainWindow *ui;
    Graph *graph;
    Database *database;
};
#endif // MAINWINDOW_H
