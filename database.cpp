#include "database.h"

DataBase::DataBase()
{
    if (!createConnection()) {
        qDebug() << "1111";
    }
}

bool DataBase::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setUserName("root");
    db.setHostName("localhost");
    db.setPassword("3170635");
    db.setDatabaseName("1111");
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}

QList<QString> DataBase::getMarks()
{
    QList<QString> marks;
    QSqlQuery q;
    if(!q.exec("SELECT DISTINCT mark FROM auto"))
    {
        qDebug() << "111";
    }
    QSqlRecord rec = q.record();
    while(q.next())
    {
        marks << q.value(rec.indexOf("mark")).toString();
    }
    return marks;
}

QList<QString> DataBase::getModel(QString mark)
{
    QList<QString> models;
    QSqlQuery q;
    QString request = "SELECT DISTINCT model FROM auto WHERE mark = '%1'";
    request = request
            .arg(mark);
    if(!q.exec(request))
    {
        qDebug() << "111";
    }
    QSqlRecord rec = q.record();
    while(q.next())
    {
        models << q.value(rec.indexOf("model")).toString();
    }
    return models;
}

QList<QString> DataBase::getSerie(QString mark, QString model)
{
    QList<QString> serie;
    QSqlQuery q;
    QString request = "SELECT DISTINCT serie FROM auto WHERE mark = '%1' AND model = '%2'";
    request = request
            .arg(mark)
            .arg(model);
    if(!q.exec(request))
    {
        qDebug() << "111";
    }
    QSqlRecord rec = q.record();
    while(q.next())
    {
        serie << q.value(rec.indexOf("serie")).toString();
    }
    return serie;
}

QList<QString> DataBase::getMod(QString mark, QString model, QString serie)
{
    QList<QString> mod;
    QSqlQuery q;
    QString request = "SELECT DISTINCT modification FROM auto WHERE mark = '%1' AND model = '%2' AND serie = '%3'";
        request = request
                .arg(mark)
                .arg(model)
                .arg(serie);
    if(!q.exec(request))
    {
        qDebug() << "111";
    }
    QSqlRecord rec = q.record();
    while(q.next())
    {
        mod << q.value(rec.indexOf("modification")).toString();
    }
    return mod;
}

//QSqlTableModel* DataBase::searchAuto(QString mark, QString model, QString serie, QString mod)
//{
//    QSqlTableModel*  sq = new QSqlTableModel;

//    sq->setTable("auto");
//    QString str;
//    if(mark != "Не выбрано" && mark != "")
//    {
//        str = "mark = '" + mark + "'";
//        if(model != "Не выбрано" && model != "")
//        {
//            str += "AND model = '" + model + "'";
//            if(serie != "Не выбрано" && serie != "")
//            {
//                str += "AND serie = '" + serie + "'";
//                if(mod != "Не выбрано" && mod != "")
//                {
//                    str += "AND modification = '" + mod + "'";
//                }
//            }
//        }
//        sq->setFilter(str);
//    }
//    return sq;
//}

bool DataBase::addAuto(QString mark, QString model, QString serie, QString mod, int start, int end)
{
    QSqlTableModel sq;
    sq.setTable("auto");
    sq.insertRows(0,1);
    sq.setData(sq.index(0,1), mark);
    sq.setData(sq.index(0,2), model);
    sq.setData(sq.index(0,3), serie);
    sq.setData(sq.index(0,4), mod);
    if(start != 0)
    {
        sq.setData(sq.index(0,5), start);
    }
    if(end != 0)
    {
        sq.setData(sq.index(0,6), end);
    }
    if(!sq.submitAll())
    {
        return false;
    } else
    {
        return true;
    }
}

bool DataBase::addAutostation(QString address, QString phone, QString mark)
{
    QSqlTableModel sq;
    sq.setTable("autostation");
    sq.insertRows(0,1);
    sq.setData(sq.index(0,1), address);
    sq.setData(sq.index(0,2), phone);
    sq.setData(sq.index(0,3), mark);
    if(!sq.submitAll())
    {
        return false;
    } else
    {
        return true;
    }
}
