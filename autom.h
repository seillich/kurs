#ifndef AUTOM_H
#define AUTOM_H

#include <QDialog>
#include <QtSql>
#include <QtWidgets>
#include "database.h"

namespace Ui {
class Autom;
}

class Autom : public QDialog
{
    Q_OBJECT

public:
    explicit Autom(QString mark = "", QString model = "", QString serie = "", QString mod = "", QWidget *parent = nullptr);
    ~Autom();
private slots:
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void removeAuto();
    void on_pushButton_clicked();

private:
    Ui::Autom *ui;
    QSqlTableModel* sq;
    QString m_mark;
    //int m_idmark;
    QString m_model;
    //int m_idmodel;
    QString m_serie;
    //int m_idserie;
    QString m_mod;
    //int m_idmod;
    void saveAsCSV(QString filename);
};

#endif // AUTOM_H
