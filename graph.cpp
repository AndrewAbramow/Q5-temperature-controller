#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    chart_ = new QChart();
    //chart -> addSeries(series);
    chart_ -> createDefaultAxes();
    chart_ -> setTitle("Temperature");
    chart_ -> legend() -> setVisible(true);
    chart_ -> legend() -> setAlignment(Qt::AlignBottom);
    chart_view_ = new QChartView(chart_);
    chart_view_ -> setRenderHint(QPainter::Antialiasing);
    chart_view_ -> setParent(ui->horizontalFrame);
}

Graph::~Graph()
{
    delete ui;
    qDebug()<<"Graph deleted\n";
}

void Graph::AddSeries(QLineSeries *series)
{
    series_ = series;
    chart_ -> addSeries(series_);
    chart_ -> createDefaultAxes();
    chart_view_->setChart(chart_);
}

void Graph::SetSeries(QLineSeries *series)
{
    series_ = series;
    chart_ -> removeAllSeries();
    chart_ -> addSeries(series_);
    chart_ -> createDefaultAxes();
    chart_view_->setChart(chart_);
}

void Graph::on_save_button_clicked()
{
    QDateTime curr_date = QDateTime::currentDateTime();
    QString s_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    chart_view_->grab().save(s_date+".png");
}
