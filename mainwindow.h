#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtWidgets>
#include "autom.h"
#include "addauto.h"
#include "autostation.h"
#include "addautostation.h"
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void changeMark();
    void changeModel();
    void changeSerie();
    void changeMod();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    DataBase* db;
    bool createConnection();
    QSqlTableModel* model;
    QString m_mark;
    // m_idmark;
    QString m_model;
    //int m_idmodel;
    QString m_serie;
    //int m_idserie;
    QString m_mod;
    //int m_idmod;

};

#endif // MAINWINDOW_H
