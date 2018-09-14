#include <QPixmap>
#include <QTouchEvent>
#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(PATH_TO_LOGO);

    auto *timer = new QTimer(this);

    auto w = ui->label_pic->width();
    auto h = ui->label_pic->height();

    ui->closeButton->setText("Close");
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    connect(timer, &QTimer::timeout, this, &MainWindow::fileChanged);

    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileChanged()
{
    QFile file(PATH_TO_SENSOR);
    QTextStream in(&file);

    bool ok;

    if (!file.open(QIODevice::ReadOnly)) {
         QMessageBox::information(0, "Error", file.errorString());
    }

    auto str = in.readAll();
    auto value = str.toDouble(&ok);
    value = value/DIVIDEND;

    str = QString::number(value);

    ui->textBrowser->setText((str + "°C"));
}
