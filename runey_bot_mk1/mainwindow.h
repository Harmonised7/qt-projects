#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// OpenCV Includes
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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
