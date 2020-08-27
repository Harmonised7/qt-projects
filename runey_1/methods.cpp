#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    qDebug() << "Init...";

    if( _jsonFile.open( QFile::ReadOnly ) )
    {
        qDebug() << "File Exists";

        _json = json::parse( _jsonFile.readAll().toStdString().c_str() );

        if( !_json.empty() )
        {
            for( json::iterator it = _json.begin(); it != _json.end(); ++it )
            {
                _itemStringList << QString::fromStdString( it.value()[ "name" ] );
                idMap.insert( QString::fromStdString( it.value()[ "name" ] ), it.value()[ "id" ] );
            }

            if (!_itemStringList.isEmpty())
            {
                ui->listWidget->addItems(_itemStringList);

                _stringCompleter = new QCompleter(_itemStringList);
                _stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);

                ui->lineEdit->setCompleter(_stringCompleter);
            }
        }
    }

    qDebug() << "Finalized";
}

void MainWindow::onResult( QNetworkReply *reply )
{
    QString replyString = reply->readAll();

    // qDebug() << "Received data:" << replyString;

    try
    {
        json doc = json::parse(replyString.toStdString().c_str());

        qDebug() << doc.dump(4).c_str();
        qDebug() << "Item price is:" << QString::fromStdString(doc["item"]["current"]["price"]);
    }
    catch (...)
    {
        qDebug() << "Error decoding the Json";
    }
}
