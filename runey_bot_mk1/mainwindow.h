#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define FPS 0.7615

//Qt Stuff
#include <QMainWindow>
#include <QScreen>
#include <QTimer>
#include <QDebug>
#include <QCursor>
#include <QProcess>
#include <QSet>
#include <QPixmap>
#include <QDir>
#include <QMap>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Controllers
#include "Controllers/mouseController.h"
#include "Controllers/keyboardController.h"
#include "Controllers/windowController.h"

//Util Includes
#include "Util/botFactory.h"
#include "Util/timer.h"
#include "Util/defines.h"

//Other Includes
#include "botInstance.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Screen Stuff
    void handleFrame();

    void on_unpauseButton_clicked();

    void on_logoutButton_clicked();

    void on_showButton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;

    //Init
    void init();

    //ObjectDeclarations
    QMap<int, BotInstance *> _botInstances;

    QScreen *_screen;
    QRect _screenGeometry;
    QTimer _refreshTimer;

    cv::Mat _screenPixMat;

    cv::Rect _clickSafeArea;

    Timer *_timer;
    TimeoutCondition *_timeoutCondition;

    //Methods
    void setRes();

    //Objects
    int _leftX, _rightX;
    int _topY, _botY;
    bool _botsRunning = false;
    bool _frameFinished = true;
    QList<QString> _accounts;
};
#endif // MAINWINDOW_H
