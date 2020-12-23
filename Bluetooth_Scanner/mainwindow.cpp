#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();

    qDebug() << "There are:" << infos.size() << "available Serial ports.";

    for (const QSerialPortInfo &info : infos)
    {
        qDebug() << info.portName();
    }

    /*
    _serial->setPortName("");
    _serial->setBaudRate(QSerialPort::Baud9600);
    _serial->setDataBits(QSerialPort::Data8);
    _serial->setParity(QSerialPort::NoParity);
    _serial->setStopBits(QSerialPort::OneStop);
    _serial->setFlowControl(QSerialPort::NoFlowControl);

    if (_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial port opened";
    }
    else
    {
        qDebug() << "Cannot open the Serial port";
    }
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
