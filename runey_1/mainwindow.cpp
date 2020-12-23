#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _urlString("https://secure.runescape.com/m=itemdb_oldschool/api/catalogue/detail.json?item="),
    _rsJsonFile(":/json/items/sources/json/Objects_87.json"),
    _osBuddyJsonFile(":/json/items/sources/json/summary.json")
{
    ui->setupUi(this);
//    this->window()->setFixedSize(this->window()->size());

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
    Item itemInfo = _itemMap[ item->text() ];
    _resultString = "Name:\n ";
    _resultString += item->text() + "\n";
    _resultString += "ID:\n ";
    _resultString += QString::number( itemInfo.id ) + "\n";
    _resultString += "Members Item:\n ";
    _resultString += QString( itemInfo.members ) + "\n";

    ui->plainTextEdit->setPlainText( _resultString );

//    _request.setUrl( QUrl( _urlString + QString::number( id ) ) );
//    _networkManager.get(_request);

}

void MainWindow::onResult( QNetworkReply *reply )
{
    QString replyString = reply->readAll();

    // qDebug() << "Received data:" << replyString;

    try
    {
        json doc = json::parse(replyString.toStdString().c_str());

//        qDebug() << doc.dump(4).c_str();
        _resultString += "Price:\n ";
        _resultString += QString::fromStdString(doc["item"]["current"]["price"]);
        ui->plainTextEdit->setPlainText( _resultString );
    }
    catch (...)
    {
        _resultString += "Error Decoding Json:\n ";
        _resultString += reply->readAll().length() == 0 ? "{}" : reply->readAll();
        ui->plainTextEdit->setPlainText( _resultString );
    }
}
