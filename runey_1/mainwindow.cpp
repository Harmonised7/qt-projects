#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_released()
{
    Mat image = imread( "cat.jpg" );

    if( !image.data )
    {
        QMessageBox box;
        box.setText( "Shiet" );
        box.exec();
    }
    else
    {
        line( image, Point( 10, 20 ), Point( 200, 300 ), Scalar( 255, 0, 255 ), 3, LINE_8, 0 );
        imshow( "Cat Image", image );
    }
}
