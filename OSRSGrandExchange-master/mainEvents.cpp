#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QList<QListWidgetItem *> item = ui->itemsListWidget->findItems(arg1, Qt::MatchExactly);

    if (item.size() == 1)
    {
        ui->itemsListWidget->setCurrentItem(item[0]);
    }
}
