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

    _clickSafeArea = cv::Rect( BAR_WIDTH, BAR_HEIGHT, _screen->size().width() - BAR_WIDTH, _screen->size().height() - BAR_HEIGHT );
    _timer->start();
    _timeoutCondition = new TimeoutCondition( 3000, 30000 );

//    QList<IntPair> locations;
//    QList<StrPair> accounts;
//    QList<int> availableLocations;
//    locations += IntPair( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT );
//    locations += IntPair( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT + 510 );
//    locations += IntPair( BAR_WIDTH + BORDER_SIZE + 1040, BAR_HEIGHT + BORDER_HEIGHT );
//    locations += IntPair( BAR_WIDTH + BORDER_SIZE + 1040, BAR_HEIGHT + BORDER_HEIGHT + 510 );
//    accounts  += StrPair( "s6cskills@mail.com", "einblicke" );
//    accounts  += StrPair( "s7cskills@mail.com", "einblicke" );
//    accounts  += StrPair( "s8cskills@mail.com", "einblicke" );
//    accounts  += StrPair( "s9cskills@mail.com", "einblicke" );

    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT, StrPair( "s6cskills@mail.com", "einblicke" ) ) );
    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT + 510, StrPair( "s7cskills@mail.com", "einblicke" ) ) );
    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE + 1040, BAR_HEIGHT + BORDER_HEIGHT, StrPair( "s8cskills@mail.com", "einblicke" ) ) );
    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE + 1040, BAR_HEIGHT + BORDER_HEIGHT + 510, StrPair( "s9cskills@mail.com", "einblicke" ) ) );


//    for( int i = 0; i < locations.size(); i++ )
//    {
//        availableLocations += i;
//    }

//    for( StrPair account : accounts )
//    {
//        if( availableLocations.size() == 0 )
//            break;
//        else
//        {
//            int availableLocationId = availableLocations.value( Util::genRand( availableLocations.size()-1 ) );
//            IntPair availableLocation = locations.value( availableLocationId );

//            _botInstances.push_back( BotFactory::makeGathererBot( availableLocation.first, availableLocation.second, account ) );

//            availableLocations.removeOne( availableLocationId );
//        }
//    }

//    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_unpauseButton_clicked()
{
    init();
//    for( BotInstance *bot : _botInstances )
//    {
//        bot->info->states.insert( BotState::Pause, false );
//    }
}

void MainWindow::on_pauseButton_clicked()
{
    for( BotInstance *bot : _botInstances )
    {
        bot->info->states.insert( BotState::Pause, true );
    }
}
