#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtCharts>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
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

private slots:
    void on_add_row_clicked();

    void on_delete_row_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_db_begin_box_currentIndexChanged(const QString &arg1);

    void on_db_end_box_currentIndexChanged(const QString &arg2);

private:
    Ui::Database *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    QStringList range_list;
    QString current_range_begin;
    QString current_range_end;
    int row;
    int n;
};

#endif // DATABASE_H
