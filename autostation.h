#ifndef AUTOSTATION_H
#define AUTOSTATION_H

#include <QDialog>
#include <QSqlTableModel>
#include <QtSql>
#include <QtWidgets>

namespace Ui {
class Autostation;
}

class Autostation : public QDialog
{
    Q_OBJECT

public:
    explicit Autostation(QString mark = "", QWidget *parent = nullptr);
    ~Autostation();

private slots:
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void removeAutostation();

    void on_pushButton_clicked();

private:
    QSqlTableModel* sq;
    QString m_mark;
    Ui::Autostation *ui;
    void saveAsCSV(QString filename);
};

#endif // AUTOSTATION_H
