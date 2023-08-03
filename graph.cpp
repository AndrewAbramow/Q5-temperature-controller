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

void Graph::AddSeries(QLineSeries *series)
{
    series_ = series;
    chart -> addSeries(series_);
    chart -> createDefaultAxes();
    chart_view->setChart(chart);
}

void Graph::SetSeries(QLineSeries *series)
{
    series_ = series;
    chart -> removeAllSeries();
    chart -> addSeries(series_);
    chart -> createDefaultAxes();
    chart_view->setChart(chart);
}

void Graph::on_save_button_clicked()
{
    //date-time format naming later
    chart_view->grab().save("graph.png");
}
