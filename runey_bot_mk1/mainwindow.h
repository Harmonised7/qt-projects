#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define FPS 10
#define RUNELITE_WIDTH 765
#define RUNELITE_HEGIHT 503

//Qt Stuff
#include <QMainWindow>
#include <QScreen>
#include <QRect>
#include <QTimer>
#include <QDebug>
#include <QDesktopWidget>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

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
    void on_screenshotButton_clicked();

    //Screen Stuff
    void handleFrame();

private:
    Ui::MainWindow *ui;

    //Init
    void init();

    //ObjectDeclarations
    QScreen *_screen;
    QRect _screenGeometry;
    QPixmap _screenPixMap;
    QTimer _refreshTimer;

    //Function Declarations
    QPixmap matToPixmap(const cv::Mat &openCVMat);
    cv::Mat pixmapToMat(const QPixmap &QtPixmap);
    QImage pixmapToQImage(const QPixmap &QtPixmap);
};
#endif // MAINWINDOW_H
