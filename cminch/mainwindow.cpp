#include "mainwindow.h"
#include "ui_mainwindow.h"

QMap<QString, QStringList> MainWindow::typesLists =
{
    {
        "Distance",
        {
            "Meters", "Inches"
        }
    },
    {
        "Weight",
        {
            "Kilograms", "Pounds"
        }
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->currSpinBox->setMinimum( ui->minSpinBox->value() );
    ui->currSpinBox->setMaximum( ui->maxSpinBox->value() );
    on_categoryComboBox_currentIndexChanged( ui->categoryComboBox->currentText() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_minSpinBox_valueChanged( double arg1 )
{
    ui->currSpinBox->setMinimum( arg1 );
    ui->valueSlider->setMinimum( arg1 );
}

void MainWindow::on_maxSpinBox_valueChanged( double arg1 )
{
    ui->currSpinBox->setMaximum( arg1 );
    ui->valueSlider->setMaximum( arg1 );
}

void MainWindow::on_valueSlider_valueChanged( int value )
{
    ui->currSpinBox->setValue( value );
}

void MainWindow::on_currSpinBox_valueChanged( double arg1 )
{
    ui->valueSlider->setValue( arg1 );
    updateResults();
}

void MainWindow::on_categoryComboBox_currentIndexChanged(const QString &arg1)
{
    ui->type1ComboBox->clear();
    ui->type2ComboBox->clear();
    ui->type1ComboBox->addItems( typesLists[ arg1 ] );
    ui->type2ComboBox->addItems( typesLists[ arg1 ] );
    if( typesLists[ arg1 ].size() > 1 )
        ui->type2ComboBox->setCurrentIndex( 1 );
    updateResults();
}

void MainWindow::on_type1ComboBox_currentIndexChanged( int index )
{
    updateResults();
}

void MainWindow::on_type2ComboBox_currentIndexChanged( int index )
{
    updateResults();
}

void MainWindow::on_toggleButton_clicked()
{
    int temp = ui->type1ComboBox->currentIndex();
    ui->type1ComboBox->setCurrentIndex( ui->type2ComboBox->currentIndex() );
    ui->type2ComboBox->setCurrentIndex( temp );
    updateResults();
}

void MainWindow::on_type1PrefixComboBox_currentIndexChanged( int index )
{
    updateResults();
}

void MainWindow::on_type2PrefixComboBox_currentIndexChanged( int index )
{
    updateResults();
}

void MainWindow::updateResults()
{
    QString text = "";

    QString inPrefix = ui->type1PrefixComboBox->currentText();
    QString outPrefix = ui->type2PrefixComboBox->currentText();

    double output = Util::getConvertedUnit( ui->currSpinBox->value(), ui->type1ComboBox->currentText(), ui->type2ComboBox->currentText(), ui->type1PrefixComboBox->currentText(), inPrefix );
    text.append( inPrefix + ui->type1ComboBox->currentText() + ": " + QString::number( ui->currSpinBox->value() ) + "\n" );
    text.append( outPrefix + ui->type2ComboBox->currentText() + ": " + QString::number( output * Util::prefixMultipliers[ inPrefix ] / Util::prefixMultipliers[ outPrefix ] ) );
    ui->resultsLabel->setText( text );
}
