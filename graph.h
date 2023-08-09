#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtCharts>
#include <QPixmap>
#include <QSqlTableModel>

namespace Ui {
class Graph;
}

//! Colored graph drawer
class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

    /*! Add temperature data to an existing set */
    void AddSeries(QLineSeries *series);

    /*! Clear dataset and add new temperature data */
    void SetSeries(QLineSeries *series);

private slots:
    
    /*! Save current plot as *.png */
    void on_save_button_clicked();

private:
    QLineSeries *series_;
    QChart *chart_;
    QChartView *chart_view_;
    Ui::Graph *ui;
};

#endif // GRAPH_H
