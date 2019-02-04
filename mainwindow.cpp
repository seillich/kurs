#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Не выбрано");
    ui->comboBox_2->addItem("Не выбрано");
    ui->comboBox_4->addItem("Не выбрано");
    ui->comboBox_5->addItem("Не выбрано");
    db = new DataBase;
    QList<QString> marks = db->getMarks();
    foreach(QString str, marks)
    {
        ui->comboBox->addItem(str);
    }

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), SLOT(changeMark()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), SLOT(changeModel()));
    connect(ui->comboBox_4, SIGNAL(currentIndexChanged(int)), SLOT(changeSerie()));
    connect(ui->comboBox_5, SIGNAL(currentIndexChanged(int)), SLOT(changeMod()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Autom hel(m_mark, m_model, m_serie, m_mod);
    hel.exec();
}

void MainWindow::changeMark()
{
    m_mark = ui->comboBox->currentText();
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("Не выбрано");
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("Не выбрано");
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("Не выбрано");
    QList<QString> models = db->getModel(m_mark);
    foreach(QString str, models)
    {
        ui->comboBox_2->addItem(str);
    }
}

void MainWindow::changeModel()
{
    m_model = ui->comboBox_2->currentText();
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("Не выбрано");
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("Не выбрано");
    QList<QString> serie = db->getSerie(m_mark, m_model);
    foreach(QString str, serie)
    {
        ui->comboBox_4->addItem(str);
    }
}

void MainWindow::changeSerie()
{
    m_serie = ui->comboBox_4->currentText();
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("Не выбрано");
    QList<QString> mod = db->getMod(m_mark, m_model, m_serie);
    foreach(QString str, mod)
    {
        ui->comboBox_5->addItem(str);
    }
}

void MainWindow::changeMod()
{
    m_mod = ui->comboBox_5->currentText();

}


void MainWindow::on_pushButton_3_clicked()
{
    Autom hel;
    hel.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    AddAuto aut;
    aut.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    Autostation aut;
    aut.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    Autostation aut(m_mark);
    aut.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    AddAutostation aut;
    aut.exec();
}
