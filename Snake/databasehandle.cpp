#include "databasehandle.h"

DataBaseHandle::DataBaseHandle(QObject *parent) : QObject(parent)
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("snake.sqlite");
    QSqlQuery query;
    QString queryStr = "CREATE TABLE snake_table("
                  "ID integer PRIMARY KEY, "
                  "size_of_map integer, "
                  "map TEXT, "
                  "number_of_snakes integer, "
                  "size_of_snakes TEXT, "
                  "x TEXT, "
                  "y TEXT"
                  ");";

    if (!dataBase.open()) {
            qDebug() << "Что-то пошло не так!";
            return;
        }
    bool check = query.exec(queryStr);
    if (!check) {
        qDebug()<<"couldn't create table";
    }
}

void DataBaseHandle::addToDataBase(QString id, QString sizeOfMap, QString map,
                                   QString numberOfSnakes, QString sizeOfSnakes,
                                   QString x, QString y)
{
    QSqlQuery query;
    QString queryStr = "INSERT INTO snake_table(ID, size_of_map, map,"
                       " number_of_snakes,"
                       " size_of_snakes, x, y) "
                       "VALUES (%1, %2, '%3', %4, '%5', '%6', '%7');";
    QString final = queryStr.arg(id).arg(sizeOfMap).
            arg(map).arg(numberOfSnakes).arg(sizeOfSnakes).arg(x).arg(y);
    bool check = query.exec(final);
    if (!check) {
        qDebug()<<"couldn't insert data";
    }

}
