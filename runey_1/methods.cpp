#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;

void MainWindow::onResult( QNetworkReply *reply )
{
    QString replyString = reply->readAll();

    // qDebug() << "Received data:" << replyString;

    try
    {
        json doc = json::parse(replyString.toStdString().c_str());
        //qDebug() << QString::fromStdString(doc["item"]["id"]);

        qDebug() << doc.dump(4).c_str();

        qDebug() << "Item price is:" << QString::fromStdString(doc["item"]["current"]["price"]);
    }
    catch (...)
    {
        qDebug() << "Error decoding the Json";
    }
}
