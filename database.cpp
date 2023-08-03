#include "database.h"
#include "ui_database.h"

#define myqDebug() qDebug() fixed << qSetRealNumberPrecision(2)

Database::Database(Graph *graph, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database)
{
    ui->setupUi(this);
    graph_=graph;
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./storage.db");
    if (db.open()) {
        qDebug("storage open");
    }
    else {
        qDebug("storage closed");
    }
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Temperature(N INTEGER, D TEXT, T REAL);"); // id for N
    model = new QSqlTableModel(this, db);
    model->setTable("Temperature");
    model->select();
    model_std = new QStandardItemModel;
    ui->tableView->setModel(model);
    this->setAttribute(Qt::WA_DeleteOnClose);
    n=0;
    range_list<<"0"<<"2"<<"4"<<"6"<<"8"<<"10"<<"12"<<"14"<<"16"<<"18";
    current_range_begin = 0;
    current_range_end = 20;
}

Database::~Database()
{
    qDebug("database deleted");
    delete ui;
}

void Database::on_add_row_clicked()
{
    /*
    int t = 25;
    QString s_t = QString::number(t);
    //model->insertRow(model->rowCount()); // manual add
    QDateTime curr_date = QDateTime::currentDateTime();
    QString string_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    query->exec("INSERT INTO Temperature(date, Temperature)VALUES('" + string_date + "','" + s_t + "')");
    */
}

void Database::on_delete_row_clicked()
{
    model->removeRow(row); // manual delete
}

void Database::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void Database::AddNewValue(float value)
{
    QString s_n = QString::number(n);
    QString s_value = QString::number(value);
    QDateTime curr_date = QDateTime::currentDateTime();
    QString s_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    query->exec("INSERT INTO Temperature(N, D, T)VALUES('" + s_n + "','" + s_date + "','" + s_value + "')");
    n+=2;
}

QLineSeries* Database::LoadFromDB()
{
    float temp = 0;
    query->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin)+" AND N<="+QString::number(current_range_end)+";");
    if (!query->exec())
    {
        //qDebug()<<query->lastError();
    }
    QLineSeries *series = new QLineSeries();
    while (query->next())
    {
        series->append(query->value(0).toInt(),query->value(2).toFloat());
        temp = query->value(2).toFloat();
        QString s = QString::number(temp);
        qDebug()<<temp<<" - FROM DATABASE\n";
    }
    return series;
}

void Database::SetRange()
{
    model_std->clear();
    query->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin)+" AND N<="+QString::number(current_range_end)+";");
    if (!query->exec())
    {
        //qDebug()<<query->lastError();
    }
    int i = 0;
    while (query->next())
    {
        item = new QStandardItem(query->value(0).toString()); // second counter
        model_std->setItem(i,0,item);
        item = new QStandardItem(query->value(2).toString()); // temperature
        model_std->setItem(i,1,item);
        i++;
    }
    ui->tableView->setModel(model_std);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void Database::on_currrent_range_begin_valueChanged(int arg1)
{
    current_range_begin = arg1;
    SetRange();
    graph_->SetSeries(LoadFromDB());
    ui->tableView->update();
}

void Database::on_current_range_end_valueChanged(int arg1)
{
    current_range_end = arg1;
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
        query->exec("SELECT * FROM Temperature WHERE N>="+QString::number(current_range_begin)+" AND N<="+QString::number(current_range_end)+";");
        if (!query->exec())
        {
            //qDebug()<<query->lastError();
        }
        while (query->next())
        {
            output<<query->value(0).toInt()<<','<<query->value(1).toString()<<','<<query->value(2).toFloat()<<'\n';
        }
    } else {
        qDebug()<<"Can't find csv file\n";
    }
    file.close();
}
