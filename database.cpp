#include "database.h"
#include "ui_database.h"

#define myqDebug() qDebug() fixed << qSetRealNumberPrecision(2)

Database::Database(Graph *graph, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database)
{
    ui->setupUi(this);
    graph_=graph;
    db_=QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName("./storage.db");
    if (db_.open()) {
        qDebug("storage open");
    }
    else {
        qDebug("storage closed");
    }
    query_ = new QSqlQuery(db_);
    query_->exec("CREATE TABLE Temperature(N INTEGER, D TEXT, T REAL);"); // id for N
    model_ = new QSqlTableModel(this, db_);
    model_->setTable("Temperature");
    model_->select();
    model_std_ = new QStandardItemModel;
    ui->tableView->setModel(model_);
    n_=0;
    current_range_begin_ = 0;
    current_range_end_ = 20;
    row_ = 0;
}

Database::~Database()
{
    //query_->clear();
    //item_->clearData();
    //model_->clear();
    //model_std_->clear();
    //delete graph_;// the graph object will be removed from the main
    delete ui;
    qDebug("Database deleted\n");
}

void Database::on_add_row_clicked()
{
    model_->insertRow(model_->rowCount()); // manual add
    QDateTime curr_date = QDateTime::currentDateTime();
    QString string_date = "INSERT INTO Temperature(N, D, T)VALUES('0','0','0')";
    query_->exec(string_date);
    ui->tableView->update();
}

void Database::on_delete_row_clicked()
{
    model_->removeRow(row_); // manual delete
    ui->tableView->update();
}

void Database::on_tableView_clicked(const QModelIndex &index)
{
    row_ = index.row();
}

void Database::AddNewValue(float value)
{
    QString s_n = QString::number(n_);  // try int
    QString s_value = QString::number(value); // try float
    QDateTime curr_date = QDateTime::currentDateTime();
    QString s_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    query_->exec("INSERT INTO Temperature(N, D, T)VALUES('" + s_n + "','" + s_date + "','" + s_value + "')");
    n_+=2;
}

QLineSeries* Database::LoadFromDB()
{
    float temp = 0;
    query_->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin_)+" AND N<="+QString::number(current_range_end_)+";");
    if (!query_->exec())
    {
        //qDebug()<<query->lastError();
    }
    QLineSeries *series = new QLineSeries();
    while (query_->next())
    {
        series->append(query_->value(0).toInt(),query_->value(2).toFloat());
        temp = query_->value(2).toFloat();
        QString s = QString::number(temp);
    }
    return series;
}

void Database::SetRange()
{
    model_std_->clear();
    query_->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin_)+" AND N<="+QString::number(current_range_end_)+";");
    if (!query_->exec())
    {
        //qDebug()<<query->lastError();
    }
    int i = 0;
    while (query_->next())
    {
        item_ = new QStandardItem(query_->value(0).toString()); // seconds counter
        model_std_->setItem(i,0,item_);
        item_ = new QStandardItem(query_->value(1).toString()); // timestamp
        model_std_->setItem(i,1,item_);
        item_ = new QStandardItem(query_->value(2).toString()); // temperature
        model_std_->setItem(i,2,item_);
        i++;
    }
    ui->tableView->setModel(model_std_);
}

void Database::on_currrent_range_begin_valueChanged(int arg1)
{
    current_range_begin_ = arg1;
    SetRange();
    graph_->SetSeries(LoadFromDB());
    ui->tableView->update();
}

void Database::on_current_range_end_valueChanged(int arg1)
{
    current_range_end_ = arg1;
    SetRange();
    graph_->SetSeries(LoadFromDB());
    ui->tableView->update();
}

void Database::on_save_csv_clicked()
{
    QFile file("/home/andrew/RaspberryPiTemplate/csv_database.csv");
    if (file.open(QFile::WriteOnly | QIODevice::Append))
    {
        QTextStream output(&file);
        query_->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin_)+" AND N<="+QString::number(current_range_end_)+";");
        if (!query_->exec())
        {
            //qDebug()<<query->lastError();
        }
        while (query_->next())
        {
            output<<query_->value(0).toInt()<<','<<query_->value(1).toString()<<','<<query_->value(2).toFloat()<<'\n';
        }
    } else {
        qDebug()<<"Can't find csv file\n";
    }
    file.close();
}
