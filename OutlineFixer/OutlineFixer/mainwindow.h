#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt Includes
#include <QMainWindow>
#include <QTimer>
#include <QDebug>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

#define FPS 10

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Init
    void init();

    //ObjectDeclarations

    QScreen *_screen;
    QRect _screenGeometry;
    QTimer _refreshTimer;

private slots:
    //Screen Stuff
    void handleFrame();

private:
    Ui::MainWindow *ui;
    bool hasAdjacentBlue( cv::Mat threeByThreeMat );
};
#endif // MAINWINDOW_H
