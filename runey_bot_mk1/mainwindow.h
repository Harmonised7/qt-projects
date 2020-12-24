#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define FPS 10

#define RS_WIDTH 765
#define RS_HEIGHT 503

#define BAR_WIDTH 72
#define BORDER_SIZE 4

#define INV_X 558
#define INV_Y 211

#define INV_SLOT_X 42
#define INV_SLOT_Y 36

//Qt Stuff
#include <QMainWindow>
#include <QScreen>
#include <QRect>
#include <QTimer>
#include <QDebug>
#include <QDesktopWidget>
#include <QCursor>
#include <QProcess>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Other Includes
#include "mouseController.h"

//Mouse Controller
#define MOUSE_JITTER    1.5
#define MOUSE_FPS       90
#define MOUSE_MIN       0.015
#define MOUSE_MAX       0.035
#define MOUSE_CURVES    2
#define MOUSE_SCREEN    0

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

    void on_testButton_clicked();

private:
    Ui::MainWindow *ui;

    //Init
    void init();

    //ObjectDeclarations
    QScreen *_screen;
    QRect _screenGeometry;
    QTimer _refreshTimer;
    cv::Mat _screenPixMat;
    cv::Mat _rsMat;
    cv::Mat _invMat;
    MouseController _mc;
    RndController *_randomNumbers;

    //Function Declarations
    QPixmap matToPixmap(const cv::Mat &openCVMat);
    cv::Mat pixMapToMat(const QPixmap &QtPixmap);
    QImage pixmapToQImage(const QPixmap &QtPixmap);
};
#endif // MAINWINDOW_H
