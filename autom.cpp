#include "autom.h"
#include "ui_autom.h"

Autom::Autom(QString mark, QString model, QString serie, QString mod, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Autom)
{
    ui->setupUi(this);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_mark = mark;
    m_model = model;
    m_serie = serie;
    m_mod = mod;

    sq = new QSqlTableModel;
    sq->setTable("auto");
    QString str;
    if(m_mark != "Не выбрано" && m_mark != "")
    {
        str = "mark = '" + m_mark + "'";
        if(m_model != "Не выбрано" && m_model != "")
        {
            str += "AND model = '" + m_model + "'";
            if(m_serie != "Не выбрано" && m_serie != "")
            {
                str += "AND serie = '" + m_serie + "'";
                if(m_mod != "Не выбрано" && m_mod != "")
                {
                    str += "AND modification = '" + m_mod + "'";
                }
            }
        }
        sq->setFilter(str);
    }
    sq->setEditStrategy(QSqlTableModel::OnFieldChange);
    sq->select();
    ui->tableView->setModel(sq);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->hideColumn(0);
}

Autom::~Autom()
{
    delete ui;
}

void Autom::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu(this);
    QAction* deleteAuto = new QAction("Удалить", this);

    menu->addAction(deleteAuto);
    connect(deleteAuto, SIGNAL(triggered()), SLOT(removeAuto()));
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void Autom::removeAuto()
{
    int rowAuto = ui->tableView->currentIndex().row();
    qDebug() << rowAuto;
    sq->removeRow(rowAuto);
    sq->submitAll();
    sq->select();
    ui->tableView->setModel(sq);
}


void Autom::on_pushButton_clicked()
{
    QString dir = QFileDialog :: getSaveFileName( this , tr( "Сохранить файл" ) , "/home" ,
                                                  tr( "CSV(* .csv)" ));
    dir += ".csv";
    qDebug() << dir;
    saveAsCSV(dir);
}

void Autom::saveAsCSV(QString filename)
{
    QFile f(filename);

    if( f.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &f );
        QStringList strList;

        strList << "\" \"";
        for( int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c )
            strList << "\""+ui->tableView->model()->headerData(c, Qt::Horizontal).toString()+"\"";
        ts << strList.join( ";" )+"\n";

        for( int r = 0; r < ui->tableView->verticalHeader()->count(); ++r )
        {
            strList.clear();
            strList << "\""+ui->tableView->model()->headerData(r, Qt::Vertical).toString()+"\"";
            for( int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c )
            {
                strList << "\""+ui->tableView->model()->data(ui->tableView->model()->index(r, c), Qt::DisplayRole).toString()+"\"";
            }
            ts << strList.join( ";" )+"\n";
        }
        f.close();
    }
}
