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

//! SQLite database controller
class Database : public QWidget
{
    Q_OBJECT

public:
    explicit Database(Graph *graph, QWidget *parent = nullptr);
    ~Database();

    //! Add new value to database
    /*!
     *  Table structure: \n
     *  N(-um) INTEGER,\n
     *  D(-ate) TEXT (date format: dd.MM.yyyy hh:mm:ss),\n
     *  T(-emperature) REAL 
     */    
    void AddNewValue(QString value);

    /*! Get temperature data for charting */
    QLineSeries* LoadFromDB();

    /*! Sets min and max N for database output */
    void SetRange();

    /*! Get the last measured temperature */
    QString GetLatestTemp();

private slots:

    /*! Add new row to database */
    void on_add_row_clicked();

    /*! Delete selected row from database */
    void on_delete_row_clicked();

    /*! Get the number of the selected row*/
    void on_tableView_clicked(const QModelIndex &index);

    /*! Min range value change handler */
    void on_currrent_range_begin_valueChanged(int arg1);

    /*! Max range value change handler */
    void on_current_range_end_valueChanged(int arg1);

    /*! Save current table as *.csv */
    void on_save_csv_clicked();

private:
    Ui::Database *ui;
    QSqlDatabase db_;
    QSqlQuery *query_;
    QSqlTableModel *model_;
    QStandardItemModel *model_std_;
    QStandardItem *item_;
    Graph *graph_;

    /*! Min range value */
    int current_range_begin_;

    /*! Max range value */
    int current_range_end_;

    /*! Selected row number */
    int row_;

    /*! Current measure number */
    unsigned int n_;
};

#endif // DATABASE_H
