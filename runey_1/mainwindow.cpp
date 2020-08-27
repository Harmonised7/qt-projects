#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _urlString("https://secure.runescape.com/m=itemdb_oldschool/api/catalogue/detail.json?item="),
    _itemCode(0),
    _jsonFile(":/json/items/sources/json/Objects_87.json")
{
    ui->setupUi(this);
    this->window()->setFixedSize(this->window()->size());

    // Init
    init();

    // Connections
    connect(&_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onResult(QNetworkReply *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_pushButton_clicked()
//{
//    _request.setUrl(QUrl(_urlString + QString::number(_itemCode)));
//    _networkManager.get(_request);  // GET
//}

//void MainWindow::on_spinBox_valueChanged(int arg1)
//{
//    _itemCode = arg1;
//}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QList<QListWidgetItem *> item = ui->listWidget->findItems(arg1, Qt::MatchExactly);

    if( item.size() == 1 )
    {
        ui->listWidget->setCurrentItem( item[0] );
    }
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    int id = idMap.lowerBound( item->text() ).value();
    _resultString = "Name:\n ";
    _resultString += item->text() + "\n";
    _resultString += "ID:\n ";
    _resultString += QString::number( id );
    ui->plainTextEdit->setPlainText( _resultString );
}
