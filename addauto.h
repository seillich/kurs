#ifndef ADDAUTO_H
#define ADDAUTO_H

#include <QDialog>
#include <QtWidgets>
#include <QSqlTableModel>
#include "database.h"

namespace Ui {
class AddAuto;
}

class AddAuto : public QDialog
{
    Q_OBJECT

public:
    explicit AddAuto(QWidget *parent = nullptr);
    ~AddAuto();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddAuto *ui;
    //QSqlTableModel* sq;
    DataBase* db;
};

#endif // ADDAUTO_H
