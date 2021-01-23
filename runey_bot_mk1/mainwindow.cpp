#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

using namespace cv;

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() ),
    _timer( new Timer )
{
    ui->setupUi(this);
    setRes();

    QList<QPoint> availableBotPos;

    availableBotPos.push_back( QPoint( _rightX, _topY ) );
    availableBotPos.push_back( QPoint( _rightX, _botY ) );
    availableBotPos.push_back( QPoint( _leftX, _topY ) );
    availableBotPos.push_back( QPoint( _leftX, _botY ) );

    QString path = QDir::current().absolutePath() + "/accounts.txt";
    qDebug() << path;
    QFile file( path );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        _accounts.push_back( "s6cskills@mail.com\teinblicke\tgather\tdrop" );
        _accounts.push_back( "s7cskills@mail.com\teinblicke\tgather\tdrop" );
        _accounts.push_back( "s8cskills@mail.com\teinblicke\tgather\tdrop" );
        _accounts.push_back( "s9cskills@mail.com\teinblicke\tgather\tdrop" );

        qDebug() << "file not found, loading default accounts";
    }
    else
    {
        for( QByteArray account : file.readAll().split( '\n' ) )
        {
            _accounts.push_back( QString( account ) );
        }
    }

    for( int i = 0; i < min( _accounts.size(), 4 ); i++ )
    {
        QString account = _accounts[i];
        QList<QString> accountInfo = account.split( "\t" );

        if( accountInfo.size() < 3 )
        {
            if( account.length() > 0 )
                qDebug() << account << "not enough info";
            continue;
        }

        QString accountInfoText = accountInfo[0] + " " + accountInfo[2];
        StrPair loginInfo = StrPair( accountInfo[0].toStdString(), accountInfo[1].toStdString() );
        QPoint pos = availableBotPos[ 0 ];
        availableBotPos.removeAt( 0 );


        if( accountInfo[2] == "gather" )
        {
            _botInstances.push_back( BotFactory::makeGathererBot( pos, loginInfo, false ) );
        }
        else if( accountInfo[2] == "powergather" )
        {
            _botInstances.push_back( BotFactory::makeGathererBot( pos, loginInfo, true ) );
        }
        else if( accountInfo[2] == "kill" )
        {
            _botInstances.push_back( BotFactory::makeKillerBot( pos, loginInfo ) );
        }
        else
            qDebug() << "Invalid settings" << accountInfo;

        ui->accountsInfoLabel->setText( ui->accountsInfoLabel->text() + "\n" + accountInfoText );
    }

//    ui->accountsInfoLabel->setText( ui->accountsInfoLabel->text() + "\n" + path );

    _clickSafeArea = cv::Rect( BAR_WIDTH, BAR_HEIGHT, _screen->size().width() - BAR_WIDTH, _screen->size().height() - BAR_HEIGHT );
    _timeoutCondition = new TimeoutCondition( 3000, 30000 );

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addBot( BotInstance *bot )
{
    _botInstances.push_back( bot );
}

void MainWindow::setRes()
{
    int width = _screen->size().width();
    int height = _screen->size().height();

    if( width == 1920 && height == 1080 )
    {
        qDebug() << "Set resolution to 1920x1080";
        _rightX = _screen->size().width() - RUNELITE_WIDTH - BORDER_SIZE;
        _leftX = BAR_WIDTH + BORDER_SIZE;
        _botY = _screen->size().height() - RUNELITE_HEIGHT - BORDER_SIZE;
        _topY = _botY - 510;
    }
    else if( width == 1600 && height == 1200 )
    {
        qDebug() << "Set resolution to 1600x1200";
        _rightX = 831;
        _leftX = 14;
        _botY = 693;
        _topY = 61;
    }
    else
        qDebug() << "WARNING WRONG RESOLUTION" << width << height;
}

void MainWindow::on_unpauseButton_clicked()
{
    _botsRunning = true;
}

void MainWindow::on_pauseButton_clicked()
{
    _botsRunning = false;
}

void MainWindow::on_logoutButton_clicked()
{
    for( BotInstance *bot : _botInstances )
    {
        bot->info->states.insert( BotState::Pause, true );
    }
}

void MainWindow::on_showButton_clicked()
{
        Mat screen = Util::pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) );

        rectangle( screen, Rect( _leftX, _topY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
        rectangle( screen, Rect( _leftX, _botY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
        rectangle( screen, Rect( _rightX, _topY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
        rectangle( screen, Rect( _rightX, _botY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );

        imshow( "test", screen );
}
