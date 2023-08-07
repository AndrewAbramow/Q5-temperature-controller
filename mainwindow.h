#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    void serial_receive();
    void on_chart_button_clicked();
    void on_db_button_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Graph *graph_;
    Database *database_;
    QSerialPort *serial_;
};
#endif // MAINWINDOW_H
