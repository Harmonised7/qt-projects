#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define FPS 1

//Qt Stuff
#include <QMainWindow>
#include <QScreen>
#include <QTimer>
#include <QDebug>
#include <QDesktopWidget>
#include <QCursor>
#include <QProcess>
#include <QSet>
#include <QPixmap>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Other Includes
#include "mouseController.h"
#include "botInstance.h"
#include "botFactory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    BotInstance *makeWcBot();

private slots:
    //Screen Stuff
    void handleFrame();
    void on_testButton_clicked();

private:
    Ui::MainWindow *ui;

    //Init
    void init();

    //ObjectDeclarations
    QList<BotInstance *> _botInstances;

    QScreen *_screen;
    QRect _screenGeometry;
    QTimer _refreshTimer;

    cv::Mat _screenPixMat;
};
#endif // MAINWINDOW_H
