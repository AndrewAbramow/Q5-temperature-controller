#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtCharts>
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

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
