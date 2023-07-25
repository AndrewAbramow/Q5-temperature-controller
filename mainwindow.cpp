#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_read_temperature_button_clicked()
{
    qDebug()<<"20 degrees\n";
    ui->label->setText("20 degrees");

    database = new Database();
    database->show();
}

void MainWindow::on_graph_button_clicked()
{
    graph = new Graph();
    graph->show();
}

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
}
