#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QDebug>

#include "util.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QMap<QString, QStringList> typesLists;
    void updateResults();

private slots:
    void on_minSpinBox_valueChanged(double arg1);

    void on_maxSpinBox_valueChanged(double arg1);

    void on_valueSlider_valueChanged(int value);

    void on_currSpinBox_valueChanged(double arg1);

    void on_categoryComboBox_currentIndexChanged(const QString &arg1);

    void on_toggleButton_clicked();

    void on_type1ComboBox_currentIndexChanged(int index);

    void on_type2ComboBox_currentIndexChanged(int index);


    void on_type1PrefixComboBox_currentIndexChanged(int index);

    void on_type2PrefixComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
