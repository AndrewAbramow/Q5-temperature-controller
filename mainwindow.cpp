#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setup serial
    serial = new QSerialPort(this);
    serial->setPortName("ttyUSB0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open((QIODevice::ReadOnly));
    connect(serial, SIGNAL(readyRead()), this, SLOT(serial_receive()));
    qDebug()<<serial->isOpen();
    // setup graph & database
    graph = new Graph();
    database = new Database();
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}

void MainWindow::serial_receive()
{
    QByteArray ba;
    ba = serial->readAll();
    ui->label->setText("Temperature: " + ba);
    //database->addNewValue(ba.toFloat()); // FOR NOW
    //float t = ba.toFloat();
    //graph->AddPoint(t);
    qDebug()<<ba;
}

void MainWindow::on_chart_button_clicked()
{
    graph->RemoveSeries();
    graph->AddPoint(database->load());
    graph->show();
}

void MainWindow::on_db_button_clicked()
{
    database->show();
}

/*
void MainWindow::on_read_temperature_button_clicked()
{
    qDebug()<<"20 degrees\n";
    //ui->label->setText("20 degrees");

    //database = new Database();
    //database->show();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug()<<"Port name: "<<info.portName()<<"\n";
    }
}
*/
/*
void MainWindow::on_graph_button_clicked()
{
    //graph = new Graph();
    graph->show();
}
*/
/*
void MainWindow::on_write_button_clicked()
{
    qDebug()<<"Text written\n";
    ui->label->setText("Text written");
    QFile file("/home/andrew/RaspberryPiTemplate/log.txt");
    QDateTime curr_date = QDateTime::currentDateTime();
    QString string_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<string_date<<": temperature is "<<t<<"\n";
    }
    else
    {
        qDebug()<<"Can't find this file\n";
    }
    file.close();
}*/

void MainWindow::on_pushButton_clicked()
{
    database->load();
}
