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

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"Text written\n";
    ui->label->setText("Text written");
    QFile file("/home/andrew/DHT/log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<"Temperature is "<<t<<"\n";
    }
    else
    {
        qDebug()<<"Can't find this file\n";
    }
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"20 degrees\n";
    ui->label->setText("20 degrees");
}


