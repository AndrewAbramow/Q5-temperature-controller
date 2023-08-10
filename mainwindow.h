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
#include "dialog.h"

/*! \mainpage Qt5 temperature control app
 * 
 * Here is the UML diagramm of this application:
 * \image html UML.png
 * 
 * \section Mainwindow
 * 
 * The main window shows the current temperature
 * \image html mainwindow.png
 *
 * \section Database
 * 
 * The database window shows the history of temperature changes
 * in the selected range
 * \image html database.png
 * 
 * \section Graph
 * 
 * The graph window shows the graph of temperature changes
 * in the selected range
 * \image html graph.png
 * 
 * \section Server
 * 
 * The server window shows the current connection settings
 * \image html server.png
 * 
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//! Main control panel
/*!
 *  Represents the control panel for the entire application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int t = 0;

private slots:

    /*! Temperature data comes through serial */
    void serial_receive();

    /*! graph button handler */
    void on_chart_button_clicked();

    /*! database button handler */
    void on_db_button_clicked();

    /*! start server button handler */
    void on_pushButton_clicked(); 

private:
    Ui::MainWindow *ui;

    /*! pointer to graph object */
    Graph *graph_;

    /*! pointer to database object */
    Database *database_;

    /*! pointer to serial object */
    QSerialPort *serial_;

    /*! pointer to server object */
    Dialog *dialog_;
    
    /*! ON command */
    QByteArray on;
    
    /*! OFF command */
    QByteArray off;
};
#endif // MAINWINDOW_H
