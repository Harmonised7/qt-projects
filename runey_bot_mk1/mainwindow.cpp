#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() ),
    _mc( MouseController( (double) MOUSE_JITTER, MOUSE_FPS, MOUSE_MIN, MOUSE_MAX, MOUSE_CURVES, MOUSE_SCREEN ) ),
    _randomNumbers( new RndController() )
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testButton_clicked()
{
    Sleeper::msleep( 1500 );
    for( int i = 0; i < 10; i++ )
    {
        _mc.mouseDrag( MouseStates::Left, _randomNumbers->generateRandom( 200, 600 ), _randomNumbers->generateRandom( 200, 600 ), 500, 750 );
    }
}
