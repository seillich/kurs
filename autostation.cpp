#include "autostation.h"
#include "ui_autostation.h"

Autostation::Autostation(QString mark, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Autostation)
{
    m_mark = mark;
    ui->setupUi(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    sq = new QSqlTableModel;
    sq->setTable("autostation");
    QString str;
    if(m_mark != "Не выбрано" && m_mark != "")
    {
        str = "markAuto = '" + m_mark + "'";
        sq->setFilter(str);
    }
    sq->setEditStrategy(QSqlTableModel::OnFieldChange);
    sq->select();
    ui->tableView->setModel(sq);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
}

Autostation::~Autostation()
{
    delete ui;
}

void Autostation::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu(this);
    QAction* deleteAuto = new QAction("Удалить", this);

    menu->addAction(deleteAuto);
    connect(deleteAuto, SIGNAL(triggered()), SLOT(removeAutostation()));
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void Autostation::removeAutostation()
{
    int rowAuto = ui->tableView->currentIndex().row();
    qDebug() << rowAuto;
    sq->removeRow(rowAuto);
    sq->submitAll();
    sq->select();
    ui->tableView->setModel(sq);
}

void Autostation::on_pushButton_clicked()
{
    QString dir = QFileDialog :: getSaveFileName( this , tr( "Сохранить файл" ) , "/home" ,
                                                  tr( "CSV(* .csv)" ));
    dir += ".csv";
    qDebug() << dir;
    saveAsCSV(dir);
}

void Autostation::saveAsCSV(QString filename)
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
