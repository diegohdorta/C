#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    #define PATH_TO_LOGO "/usr/lib/qt/examples/demo_imx7/images/NXP-logo.jpg"
    #define PATH_TO_SENSOR "/sys/bus/platform/devices/sensor/temp1_input"
    #define DIVIDEND 1000

private slots:

    void fileChanged();

private:

    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H



