#include "addauto.h"
#include "ui_addauto.h"

AddAuto::AddAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAuto)
{
    ui->setupUi(this);
    disconnect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    db = new DataBase;
}

AddAuto::~AddAuto()
{
    delete ui;
}

void AddAuto::on_buttonBox_accepted()
{
    qDebug() << ui->spinBox->specialValueText();
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "" || ui->lineEdit_4->text() == "")
    {
        QMessageBox::warning(this, "ERROR" ,"Нужно заполнить все поля обозначенные *");

    } else if (ui->spinBox->value() > ui->spinBox_2->value() || (ui->spinBox->value() == 0 && ui->spinBox_2->value() != 0))
    {
        QMessageBox::warning(this, "ERROR" ,"Проверьте годы выпуска!!!");
    } else
    {
        bool check = db->addAuto(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(), ui->spinBox->value(), ui->spinBox_2->value());
        if(!check)
        {
            QMessageBox::information(this, "infor", "Problem with db");
            qDebug() << "Error";
        } else
        {
            this->accept();
        }
    }
}
