#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtCharts>
#include <QSqlTableModel>

#include "database.h"

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
    void AddPoint(QLineSeries* series);
    void RemoveSeries();

private slots:

private:
    QLineSeries *series;
    QChart *chart;
    QChartView *chart_view;
    Ui::Graph *ui;
};

#endif // GRAPH_H
