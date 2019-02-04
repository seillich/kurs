#include "addautostation.h"
#include "ui_addautostation.h"

AddAutostation::AddAutostation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAutostation)
{
    ui->setupUi(this);
    disconnect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    db = new DataBase;
    const QString Phone = "^((\\+?(\\d{2}))\\s?)?((\\d{2})|(\\((\\d{2})\\))\\s?)?(\\d{3,15})(\\-(\\d{3,15}))?$";
    QRegularExpression rx(Phone);
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_2->setValidator(validator);
}

AddAutostation::~AddAutostation()
{
    delete ui;
}

void AddAutostation::on_buttonBox_accepted()
{
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "")
    {
        QMessageBox::warning(this, "ERROR" ,"Нужно заполнить все поля обозначенные *");
    } else
    {
        bool check = db->addAutostation(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());
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
