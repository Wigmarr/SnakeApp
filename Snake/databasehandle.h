#ifndef DATABASEHANDLE_H
#define DATABASEHANDLE_H

#include <QObject>
#include <QtSql>
#include <QString>
class DataBaseHandle : public QObject
{
    Q_OBJECT
    QSqlDatabase dataBase;

public:
    explicit DataBaseHandle(QObject *parent = nullptr);
    void addToDataBase(QString id, QString sizeOfMap, QString map,
                       QString numberOfSnakes, QString sizeOfSnakes,
                       QString x, QString y);

signals:

public slots:
};

#endif // DATABASEHANDLE_H
