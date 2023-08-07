#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setup serial
    serial_ = new QSerialPort(this);
    serial_->setPortName("ttyUSB0");
    serial_->setBaudRate(QSerialPort::Baud9600);
    serial_->setParity(QSerialPort::NoParity);
    serial_->setStopBits(QSerialPort::OneStop);
    serial_->setFlowControl(QSerialPort::NoFlowControl);
    serial_->open((QIODevice::ReadOnly));
    connect(serial_, SIGNAL(readyRead()), this, SLOT(serial_receive()));
    qDebug()<<"Serial port: "<<serial_->isOpen();
    // setup graph & database
    graph_ = new Graph();
    database_ = new Database(graph_);
    //this->setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;
    serial_->close();
    delete serial_;
    delete graph_;
    delete database_;
    qDebug("Main window deleted\n");
}

void MainWindow::serial_receive()
{
    QByteArray ba;
    ba = serial_->readAll();
    ui->label->setText("Temperature: " + ba);
    //database->AddNewValue(ba.toFloat()); // FOR NOW
    qDebug()<<ba;
}

void MainWindow::on_chart_button_clicked()
{
    graph_->SetSeries(database_->LoadFromDB());
    graph_->show();
}

void MainWindow::on_db_button_clicked()
{
    database_->show();
}

void MainWindow::on_pushButton_clicked()
{
    database_->LoadFromDB();
}
