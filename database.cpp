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
    n_= 0;
    current_range_begin_ = 0;
    current_range_end_ = 20;
    row_ = 0;
}

Database::~Database()
{
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

void Database::AddNewValue(QString value)
{
    QDateTime curr_date = QDateTime::currentDateTime();
    QString query = "INSERT INTO Temperature(N, D, T)VALUES('"
            + QString::number(n_) + "','"
            + curr_date.toString("dd.MM.yyyy hh:mm:ss") + "','"
            + value + "')";
    //qDebug()<<query;
    query_->exec(query);
    if (n_+1 > n_) ++n_;
}

QString Database::GetLatestTemp()
{
    QString latest_temp;
    query_->exec("SELECT * FROM Temperature WHERE N=="+QString::number(n_)+";");
    if (!query_->exec())
    {
        //qDebug()<<query->lastError();
    }
    while (query_->next())
    {
        latest_temp = query_->value(2).toString();
    }
    return latest_temp;
}

QLineSeries* Database::LoadFromDB()
{
    query_->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin_)+" AND N<="+QString::number(current_range_end_)+";");
    if (!query_->exec())
    {
        //qDebug()<<query->lastError();
    }
    QLineSeries *series = new QLineSeries();
    while (query_->next())
    {
        series->append(query_->value(0).toInt(),query_->value(2).toFloat());
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
    QFile file("./csv_database.csv");
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
        qDebug()<<"Can't open csv file\n";
    }
    file.close();
}
