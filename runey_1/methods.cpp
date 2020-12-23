#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    qDebug() << "Init...";

//    if( _rsJsonFile.open( QFile::ReadOnly ) )
//    {
//        qDebug() << "File Exists";

//        _json = json::parse( _rsJsonFile.readAll().toStdString().c_str() );

//        if( !_json.empty() )
//        {
//            for( json::iterator it = _json.begin(); it != _json.end(); ++it )
//            {
//                _itemStringList << QString::fromStdString( it.value()[ "name" ] );
//                idMap.insert( QString::fromStdString( it.value()[ "name" ] ), it.value()[ "id" ] );
//            }

//            if (!_itemStringList.isEmpty())
//            {
//                ui->listWidget->addItems(_itemStringList);

//                _stringCompleter = new QCompleter(_itemStringList);
//                _stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);

//                ui->lineEdit->setCompleter(_stringCompleter);
//            }
//        }
//    }

    if( _osBuddyJsonFile.open( QFile::ReadOnly ) )
    {
        qDebug() << "File Exists";

        _json = json::parse( _osBuddyJsonFile.readAll().toStdString().c_str() );

        if( !_json.empty() )
        {
            for( json::iterator it = _json.begin(); it != _json.end(); ++it )
            {
                auto value = it.value();

                _itemStringList << QString::fromStdString( value["name"] );

                PrimitiveItem tempPrimItem;

                tempPrimItem.id                 = static_cast<int>(value[ "id" ]);
                tempPrimItem.members            = static_cast<bool>(value["members"]);
                tempPrimItem.suggested_price    = static_cast<int>(value["sp"]);
                tempPrimItem.buy_quantity       = static_cast<int>(value["buy_quantity"]);
                tempPrimItem.sell_quantity      = static_cast<int>(value["sell_quantity"]);
                tempPrimItem.buy_average        = static_cast<int>(value["buy_average"]);
                tempPrimItem.sell_average       = static_cast<int>(value["sell_average"]);
                tempPrimItem.overall_quantity   = static_cast<int>(value["overall_quantity"]);
                tempPrimItem.overall_average    = static_cast<int>(value["overall_average"]);

               _itemMap.insert(_itemStringList.back(), Item(tempPrimItem));
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
