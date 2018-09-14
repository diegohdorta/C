/*
 * Diego Henrique Dorta <diego.dorta@nxp.com>
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <algorithm>
#include <string>
#include <vector>
#include <QProgressBar>

#include <dirent.h>
#include <qqml.h>

#include "utils.h"

#include <QObject>


#define SIZE (256<<10)

class Utils : public QObject {

   Q_OBJECT

public:
    explicit Utils (QObject* parent = 0);

    QObject *combo = NULL;
    QObject *teste = NULL;
    QObject *bar = NULL;
    QObject *rate = NULL;
    QObject *device = NULL;
    QObject *flash = NULL;
    QObject *download = NULL;
    QObject *exist = NULL;
    QObject *status = NULL;
    QObject *search = NULL;
    QStringList boards = (QStringList() << "Select Board");
    QStringList devices = (QStringList() << "Select Device");
    QString global_path;
    QString home;
    double global_totalbytes;
    bool downloading = false;
    qint64 x = 0;
    qint64 filesize = 0;

    Q_INVOKABLE int get_github(void);
    Q_INVOKABLE int get_github_info(void);
    Q_INVOKABLE int get_boards_info(int currentIndex);
    Q_INVOKABLE int download_image(QString board_name, QString config_file_name);
    Q_INVOKABLE int get_sdcard_image(QString board_name, QString config_file_name);
    Q_INVOKABLE int get_devices(void);
    Q_INVOKABLE int burning_sd_card(QString board_name, QString image_name, int currentIndexDevice, int currentIndexConfig);
    Q_INVOKABLE int burn(QString board_name, QString image_name, int currentIndexDevice, int currentIndexConfig);
    Q_INVOKABLE void enable_download(QString board_name, QString image_name, int currentIndex);


public slots:
    int error(QNetworkReply::NetworkError err);
    void updateProgress(qint64 read, qint64 total);
    void finishedDownload(QNetworkReply *reply); //, QString path);
    bool writeFull(QFile &out, char *buffer, qint64 size);


private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    QElapsedTimer downloadTime;
};

#endif // UTILS_H
