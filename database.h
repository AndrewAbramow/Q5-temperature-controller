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

namespace Ui {
class Database;
}

class Database : public QWidget
{
    Q_OBJECT

public:
    explicit Database(QWidget *parent = nullptr);
    ~Database();    
    void addNewValue(float value);
    QLineSeries* load();
    void SetRange();

private slots:
    void on_add_row_clicked();

    void on_delete_row_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    //void on_db_end_box_currentIndexChanged(int index);

    //void on_db_begin_box_currentIndexChanged(int index);

    void on_currrent_range_begin_valueChanged(int arg1);

    void on_current_range_end_valueChanged(int arg1);

private:
    Ui::Database *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QStandardItem *item;
    QStandardItemModel *model_std;
    QSqlTableModel *model;
    QStringList range_list;
    int current_range_begin;
    int current_range_end;
    int row;
    int n;
};

#endif // DATABASE_H
