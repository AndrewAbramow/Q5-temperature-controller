#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtCharts>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QTextStreamManipulator>

#include "graph.h"

namespace Ui {
class Database;
}

class Database : public QWidget
{
    Q_OBJECT

public:
    explicit Database(Graph *graph, QWidget *parent = nullptr);
    ~Database();    
    void AddNewValue(float value);
    QLineSeries* LoadFromDB();
    void SetRange();

private slots:
    void on_add_row_clicked();
    void on_delete_row_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_currrent_range_begin_valueChanged(int arg1);
    void on_current_range_end_valueChanged(int arg1);
    void on_save_csv_clicked();

private:
    Ui::Database *ui;
    QSqlDatabase db_;
    QSqlQuery *query_;
    QSqlTableModel *model_;
    QStandardItemModel *model_std_;
    QStandardItem *item_;
    Graph *graph_;
    int current_range_begin_;
    int current_range_end_;
    int row_;
    int n_;
};

#endif // DATABASE_H
