#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    //series = new QLineSeries();
    //series->append(0,6);
    //series->append(2,4);
    //series->append(3,8);
    //series->append(7,4);
    //series->append(10,5);
    //*series<<QPoint(11,1)<<QPoint(13,3)<<QPoint(17,6)<<QPoint(18,3)<<QPoint(20,2);

    chart = new QChart();
    //chart -> addSeries(series);
    chart -> createDefaultAxes();
    chart -> setTitle("Temperature");
    chart -> legend() -> setVisible(true);
    chart -> legend() -> setAlignment(Qt::AlignBottom);

    chart_view = new QChartView(chart);
    chart_view -> setRenderHint(QPainter::Antialiasing);
    chart_view -> setParent(ui->horizontalFrame);
}

Graph::~Graph()
{
    delete ui;
}

void Graph::AddPoint(QLineSeries* series)
{
    //series->append(QDateTime::currentDateTime().toSecsSinceEpoch(),val);
    //series->append(33,44);
    chart -> addSeries(series);
    chart -> createDefaultAxes();
    chart -> setTitle("Temperature");
    chart -> legend() -> setVisible(true);
    chart -> legend() -> setAlignment(Qt::AlignBottom);
    chart_view = new QChartView(chart);
    chart_view -> setRenderHint(QPainter::Antialiasing);
    chart_view -> setParent(ui->horizontalFrame);
}

void Graph::on_update_clicked()
{

}
