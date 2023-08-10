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
    serial_->open((QIODevice::ReadWrite));
    connect(serial_, SIGNAL(readyRead()), this, SLOT(serial_receive()));
    qDebug()<<"Serial port: "<<serial_->isOpen();
    // setup graph & database
    graph_ = new Graph();
    database_ = new Database(graph_);
    dialog_ = new Dialog(database_->GetLatestTemp());
    on.append('1');
    off.append('2');
    ui->label->setText("Wait temperature\n from serial");
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
    QString s_t = QString(ba);
    ui->label->setText("Temperature: " + s_t);
    database_->AddNewValue(s_t);
    dialog_->UpdateServerData(s_t);
    float t = ba.toFloat();
    qDebug()<<t<<" "<<(t > 30.0f);
    t > 30.0f ? serial_->write(on) : serial_->write(off);
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
    dialog_->show();
}
