#include "database.h"
#include "ui_database.h"

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
    query->exec("CREATE TABLE Temperature(date TEXT, Temperature INT);");
    model = new QSqlTableModel(this, db);
    model->setTable("Temperature");
    model->select();
    ui->tableView->setModel(model);
    this->setAttribute(Qt::WA_DeleteOnClose);
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
    int t = 25;
    QString s_t = QString::number(t);
    //model->insertRow(model->rowCount()); // manual add
    QDateTime curr_date = QDateTime::currentDateTime();
    QString string_date = curr_date.toString("dd.MM.yyyy hh:mm:ss");
    query->exec("INSERT INTO Temperature(date, Temperature)VALUES('" + string_date + "','" + s_t + "')");
}

void Database::on_delete_row_clicked()
{
    model->removeRow(row); // manual delete
}

void Database::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}
