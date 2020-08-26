#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    qDebug() << "Beginning initialization...";

    if (_jsonFileObj.open(QFile::ReadOnly))
    {
        _jsonObj = json::parse(_jsonFileObj.readAll().toStdString().c_str());

        if (!_jsonObj.empty())
        {
            for (json::iterator it = _jsonObj.begin(); it != _jsonObj.end(); ++it)
            {
                _itemStringList << QString::fromStdString(it.value()["name"]);
            }

            if (!_itemStringList.isEmpty())
            {
                ui->itemsListWidget->addItems(_itemStringList);

                _stringCompleter = new QCompleter(_itemStringList);
                _stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);

                ui->lineEdit->setCompleter(_stringCompleter);
            }
        }
    }

    qDebug() << "Ending initialization...";
}
