#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtCharts>
#include <QPixmap>
#include <QSqlTableModel>

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
    void AddSeries(QLineSeries *series);
    void SetSeries(QLineSeries *series);

private slots:
    void on_save_button_clicked();

private:
    QLineSeries *series_;
    QChart *chart;
    QChartView *chart_view;
    Ui::Graph *ui;
};

#endif // GRAPH_H
