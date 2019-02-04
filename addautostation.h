#ifndef ADDAUTOSTATION_H
#define ADDAUTOSTATION_H

#include <QDialog>
#include <QtWidgets>
#include <QSqlTableModel>
#include "database.h"

namespace Ui {
class AddAutostation;
}

class AddAutostation : public QDialog
{
    Q_OBJECT

public:
    explicit AddAutostation(QWidget *parent = nullptr);
    ~AddAutostation();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddAutostation *ui;
    DataBase* db;
};

#endif // ADDAUTOSTATION_H
