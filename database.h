#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QWidget>
#include <QtSql>
#include <QtWidgets>

class DataBase
{
public:
    DataBase();
    QList<QString> getMarks();
    QList<QString> getModel(QString mark);
    QList<QString> getSerie(QString mark, QString model);
    QList<QString> getMod(QString mark, QString model, QString serie);
    //QSqlTableModel* searchAuto(QString mark, QString model, QString serie, QString mod);
    bool addAuto(QString mark, QString model, QString serie, QString mod, int start, int end);
    bool addAutostation(QString address, QString phone, QString mark);
private:
    bool createConnection();
};

#endif // DATABASE_H
