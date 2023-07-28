#include "database.h"
#include "ui_database.h"

#define myqDebug() qDebug() fixed << qSetRealNumberPrecision(2)

Database::Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database)
{
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./storage.db");
    if (db.open()) {
        qDebug("storage open");
    }
    else {
        qDebug("storage closed");
    }
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Temperature(N INTEGER, D TEXT, T REAL);");
    model = new QSqlTableModel(this, db);
    model->setTable("Temperature");
    model->select();
    ui->tableView->setModel(model);
    this->setAttribute(Qt::WA_DeleteOnClose);
    n=0;
    range_list<<"0"<<"2"<<"4"<<"6"<<"8";
    ui->db_begin_box->addItems(range_list);
    ui->db_end_box->addItems(range_list);
    current_range_begin = "0";
    current_range_end = "10";
}

Database::~Database()
{
    //QSqlDatabase::removeDatabase("QSQLITE");
    //db.close();
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

void Database::addNewValue(float value)
{
    QString s_n = QString::number(n);
    QString s_value = QString::number(value);
    QDateTime curr_date = QDateTime::currentDateTime();
    QString s_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    query->exec("INSERT INTO Temperature(N, D, T)VALUES('" + s_n + "','" + s_date + "','" + s_value + "')");
    n+=2;
}

QLineSeries* Database::load()
{
    float temp = 0;
    query->exec("SELECT * FROM Temperature WHERE N>="+current_range_begin+" AND N<="+current_range_end+";");
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

void Database::on_db_begin_box_currentIndexChanged(const QString &arg1)
{
    current_range_begin = arg1;
}

void Database::on_db_end_box_currentIndexChanged(const QString &arg2)
{
    current_range_end = arg2;
}
