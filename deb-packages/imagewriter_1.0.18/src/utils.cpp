/*
 * Diego Henrique Dorta <diego.dorta@nxp.com>
 *
 */

#include <QApplication>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QStringListModel>
#include <QFile>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QElapsedTimer>
#include <QDialog>
#include <QDir>
#include <QSpacerItem>
#include <QGridLayout>

#include <iostream>
#include <fstream>

#include <dirent.h>
#include <qqml.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>

#include "utils.h"
#include "thread.h"

//#define DEBUG

Utils::Utils (QObject* parent) : QObject(parent) { }

int Utils::get_github_info(void)
{
    return get_github();
}

int Utils::get_github(void)
{
        bar->setProperty("indeterminate", "true");

        QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        home = homePath.first() + "/.iwcache/";

        #ifdef DEBUG
        qDebug() << home;
        #endif

        QNetworkConfigurationManager *mgr = new QNetworkConfigurationManager();

        DIR *dpdf;
        struct dirent *epdf;
        QString command;
        QString tmp;

        if (mgr->isOnline()) {

                command = "mkdir " + home;

                if((dpdf = opendir(home.toStdString().c_str())) == NULL) {
                    if(system(command.toStdString().c_str())) {
                        #ifdef DEBUG
                        std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
                        #endif
                        return EXIT_FAILURE;
                    }
                }

                tmp = home + "images/";
                command = "mkdir " + home + "images/";

                if((dpdf = opendir(tmp.toStdString().c_str())) == NULL) {
                    if(system(command.toStdString().c_str())) {
                        #ifdef DEBUG
                        std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
                        #endif
                        return EXIT_FAILURE;
                    }
                }

                command = "rm -rf " + home + "distro*";

                if(system(command.toStdString().c_str())) {
                    #ifdef DEBUG
                    std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
                    #endif
                }

                command = "wget --quiet --output-document=" + home + "distros.zip https://github.com/diegohdorta/distros/archive/master.zip 1> " + home + "log.txt 2>" + home + "error.txt";

                #ifdef DEBUG
                std::cout << "comando: " << command.toStdString().c_str() << "\n" << std::endl;
                #endif

                if(system(command.toStdString().c_str())) {
                    #ifdef DEBUG
                    std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
                    #endif
                    return EXIT_FAILURE;
                }

                command = "unzip -qq " + home + "distros.zip -d " + home + " 1>" + home + "log.txt 2>" + home + "error.txt";

                #ifdef DEBUG
                std::cout << "comando: " << command.toStdString().c_str() << "\n" << std::endl;
                #endif

                if(system(command.toStdString().c_str())) {
                    #ifdef DEBUG
                    std::cerr << "Error "<< errno << ": " << strerror(errno) << "\n" << std::endl;
                    #endif
                    return EXIT_FAILURE;
                }
        }

        command = home + "distros-master";

        #ifdef DEBUG
        std::cout << "comando: " << command.toStdString().c_str() << "\n" << std::endl;
        #endif

        if((dpdf = opendir(command.toStdString().c_str())) == NULL) {
            #ifdef DEBUG
            std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
            #endif
            return EXIT_FAILURE;
        }

        if (dpdf != NULL){
           while ((epdf = readdir(dpdf))){
               if(epdf->d_name[0] == 'i' && epdf->d_name[1] == 'm' && epdf->d_name[2] == 'x') {
                   #ifdef DEBUG
                   std::cout << epdf->d_name << std::endl;
                   #endif
                   boards.append(epdf->d_name);
               }
           }
        }

        boards.removeDuplicates();
        boards.sort(Qt::CaseSensitive);
        combo->setProperty("model", boards);

        #ifdef DEBUG
        std::cout << "get_github_info: complete" << std::endl;
        #endif

        bar->setProperty("indeterminate", "false");

        return EXIT_SUCCESS;
}

int Utils::get_boards_info(int currentIndex)
{
        DIR *dpdf;
        struct dirent *epdf;
        QString cf;
        QStringList configs = (QStringList() << "Select Image");
        QStringList empty = (QStringList() << " ");

        QString path = home + "distros-master/" + boards[currentIndex];

        if(currentIndex < 1)
            return EXIT_FAILURE;

        #ifdef DEBUG
        std::cout << "get_boards_info -> current index: " << currentIndex << " path: " << path.toStdString().c_str() << "\n" << std::endl;
        #endif

        if((dpdf = opendir(path.toStdString().c_str())) == NULL) {
            std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ << "\n" << std::endl;
            return EXIT_FAILURE;
        }

        if (dpdf != NULL){
           while ((epdf = readdir(dpdf))){
               if(epdf->d_name[0] == 'c' && epdf->d_name[1] == 'o' && epdf->d_name[2] == 'n') {
                   #ifdef DEBUG
                   std::cout << epdf->d_name << std::endl;
                   #endif
                   cf = epdf->d_name;
                   cf.remove(0,7);
                   configs.append(cf);
               }
           }
        }

        //configs.sort(Qt::CaseSensitive);
        teste->setProperty("model", configs);

        #ifdef DEBUG
        std::cout << "get_boards_info: complete" << std::endl;
        #endif

        return EXIT_SUCCESS;
}

int Utils::get_sdcard_image(QString board_name, QString config_file_name)
{
    QFile eula(home + "distros-master/" + board_name + "/eula." + config_file_name);

    if(!eula.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
        return EXIT_FAILURE;
    }

    QString eula_text = eula.readAll();
    QMessageBox msgBox;

    /*QFont font;
    font.setBold(true);
    msgBox.setFont(font);*/

    msgBox.setText("Agreement");

    msgBox.setDetailedText(eula_text);
    msgBox.setInformativeText("Please, click on 'Show Details' button to show the agreement terms");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    msgBox.setButtonText(QMessageBox::Yes, "I Accept");
    msgBox.setButtonText(QMessageBox::No, "Decline");

    auto ret = msgBox.exec();

    switch (ret) {

        case QMessageBox::Yes:
            download_image(board_name, config_file_name);
        break;

        case QMessageBox::No:
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int Utils::download_image(QString board_name, QString config_file_name)
{
        #ifdef DEBUG
        bool downloading = false;
        bool error = false;
        bool finished = false;
        #endif

        #ifdef DEBUG
        std::cout << "function: get_sdcard_image => board_name: " <<  board_name.toStdString().c_str() << " config_file_name: " << config_file_name.toStdString().c_str() << "\n" << std::endl;
        #endif

        QStringList lines;
        QString http;
        QFile file(home + "distros-master/" + board_name + "/config." + config_file_name);

        QString path = home + "images";

        #ifdef DEBUG
        std::cerr << "path: " << path.toStdString().c_str() << "\n" << std::endl;
        #endif

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
            return EXIT_FAILURE;
        }

        while(!file.atEnd()) {
          lines << file.readLine();
        }

        http = lines.at(0);
        file.close();

        global_path = home + "images/" + board_name + "." + config_file_name + ".sdcard";

        #ifdef DEBUG
        std::cout << "GLOBAL PATH: " << global_path.toStdString().c_str() << std::endl;
        #endif


        QNetworkRequest request;
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);

        request.setUrl(QUrl(http));

        QNetworkReply *reply = manager->get(request);

        #ifdef DEBUG
        downloading = connect(reply, SIGNAL(downloadProgress(qint64,qint64)) , SLOT(updateProgress(qint64,qint64)));
        error = connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
        finished = connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedDownload(QNetworkReply*)));

        
        qDebug() << "connect downloading: " << downloading;
        qDebug() << "connect error: " << error;
        qDebug() << "connect finishing: " << finished;
        #endif

        #ifndef DEBUG
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)) , SLOT(updateProgress(qint64,qint64)));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedDownload(QNetworkReply*)));
        #endif

        download->setProperty("enabled", "false");
        flash->setProperty("enabled", "false");
        downloadTime.start();
        downloading = true;

        return EXIT_SUCCESS;
}

int Utils::get_devices(void)
{
        #ifdef DEBUG
        std::cerr << "get_devices() function called!\n" << std::endl;
        #endif

        QStringList alldevices = (QStringList() << " ");
        QString dev;

        QDirIterator it("/dev/disk/by-id");
        while (it.hasNext()) {
            dev = it.next();
            dev.remove(0, 16);
            alldevices.append(dev);
        }

        devices.append(alldevices.filter("usb"));
        devices.append(alldevices.filter("mmc"));

        devices.removeDuplicates();
        devices.sort(Qt::CaseSensitive);
        device->setProperty("model", devices);

        return EXIT_SUCCESS;
}


int Utils::burning_sd_card(QString board_name, QString image_name, int currentIndexDevice, int currentIndexConfig)
{
    bar->setProperty("indeterminate", "true");
    burn(board_name, image_name, currentIndexDevice, currentIndexConfig);

    return EXIT_SUCCESS;
}


int Utils::burn(QString board_name, QString image_name, int currentIndexDevice, int currentIndexConfig)
{
        flash->setProperty("enabled", "false");
        bar->setProperty("indeterminate", "true");

        if (!currentIndexConfig) {
            QMessageBox msgBox;
            msgBox.setText("Choose an image!");
            msgBox.exec();
            return EXIT_FAILURE;
        }

        if (!currentIndexDevice) {
            QMessageBox msgBox;
            msgBox.setText("Choose a device!");
            msgBox.exec();
            return EXIT_FAILURE;
        }

        QString image = home + "images/" + board_name + "." + image_name + ".sdcard";

        #ifdef DEBUG
        std::cout << "burning_sd_card function! board_name: " << board_name.toStdString().c_str() << " image_name: " << image_name.toStdString().c_str() << std::endl;
        #endif

        QFile infile(image);
        QFile outfile("/dev/disk/by-id/" + devices[currentIndexDevice]);

        if (!infile.open(QIODevice::ReadOnly)) {
            std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
            return EXIT_FAILURE;
        }

        if (!outfile.open(QIODevice::WriteOnly)) {
            std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
            infile.close();
            return EXIT_FAILURE;
        }

        qint64 size;
        filesize = infile.size();
        char buffer[SIZE];

        do {
            size = infile.read(buffer, SIZE);

            if (size < 0) {
                std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
                QMessageBox::warning(0, QString("Warning"), QString("Error while reading image!"));
                return EXIT_FAILURE;
            }

            if (!writeFull(outfile, buffer, size)) {
                std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
                QMessageBox::warning(0, QString("Warning"), QString("Error while copying image!"));
                return EXIT_FAILURE;
            }

            //x = (100*size)/filesize;
            //bar->setProperty("value", x);

        } while (size > 0);

        infile.close();
        outfile.close();

        QString sync = "sync";

        if(system(sync.toStdString().c_str())) {
            std::cerr << "Error "<< errno << ": " << strerror(errno) << ": " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
            return EXIT_FAILURE;
        }

        QMessageBox msgBox;
        msgBox.setText("The SD card is done!");
        msgBox.exec();

        bar->setProperty("indeterminate", "false");
        flash->setProperty("enabled", "true");

        return EXIT_SUCCESS;
}

bool Utils::writeFull(QFile &out, char *buffer, qint64 size)
{
      qint64 p, w;

      for (p = 0; p < size; p += w) {
          w = out.write(buffer+p, size-p);
          if(w < 0) return false;
      }

      return true;
}

int Utils::error(QNetworkReply::NetworkError err)
{
     //#ifdef DEBUG
     std::cerr << "Error: " << err << " - " << __FILE__ << ": " << __LINE__ <<"\n" << std::endl;
     //#endif

     // what to do?

     QMessageBox::warning(0, QString("Warning"), QString("Error while downloading the image!"));

     return EXIT_SUCCESS;
}

void Utils::updateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
        #ifdef DEBUG
        std::cerr << "updateProgress Function -> " << "bytesReceived: " << bytesReceived << " bytesTotal: " << bytesTotal << " elapsed: " << downloadTime.elapsed() << "\n" << std::endl;
        #endif

        double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
        QString message;
        QString unit;

        if (speed < 1024) {
                unit = "bytes/sec";
        } else if (speed < 1024*1024) {
                speed /= 1024;
                unit = "kB/s";
        } else {
                speed /= 1024*1024;
                unit = "MB/s";
        }

        message = (QString::fromLatin1("Rate: %1 %2").arg(speed, 3, 'f', 1).arg(unit) + "\t\t " + QString::number(bytesTotal/(1024*1024)) + " MB");

        #ifdef DEBUG
        std::cout << "speed: " << message.toStdString().c_str() << std::endl;
        #endif

        global_totalbytes = bytesTotal;
        auto x = (100*bytesReceived)/bytesTotal;

        bar->setProperty("value", x);
        rate->setProperty("text", message);
}

void Utils::finishedDownload(QNetworkReply *reply) //, QString path)
{
        #ifdef DEBUG
        std::cerr << "Finished Function!\n" << std::endl;
        #endif

        QString command;
        QString path = global_path + ".zip";
        QByteArray b = reply->readAll();
        QFile file(path);

        file.open(QIODevice::WriteOnly | QIODevice::ReadOnly);

        QDataStream out(&file);

        out << b;
        reply->deleteLater();

        download->setProperty("enabled", "true");
        flash->setProperty("enabled", "true");
        exist->setProperty("text", "Image found");

        command = "unzip " + path + " -d " + home + "images/";

        #ifdef DEBUG
        std::cout << "comando: " << command.toStdString().c_str() << "\n" << std::endl;
        #endif

        if(system(command.toStdString().c_str())) {
            #ifdef DEBUG
            std::cerr << "Error "<< errno << ": " << strerror(errno) << "\n" << std::endl;
            #endif
        }

        #ifdef DEBUG
        std::cout << "Download complete! Saved file on: " << global_path.toStdString().c_str() << "\n" << std::endl;
        #endif

        downloading = false;
}

void Utils::enable_download(QString board_name, QString image_name, int currentIndex)
{
        QNetworkConfigurationManager *mgr = new QNetworkConfigurationManager();
        QString path = home + "images/" + board_name + "." + image_name + ".sdcard";

        #ifdef DEBUG
        std::cout << "command: " << path.toStdString().c_str() << "\n" << std::endl;
        #endif

        QFile file(path);
        bool x = true;
        bool t = file.exists();

        if (t) {
            exist->setProperty("text", "Image cached");
            download->setProperty("enabled", "false");
            x = false;
        }
        else {
            exist->setProperty("text", "Image not cached");
            download->setProperty("enabled", "true");
        }

        if (!mgr->isOnline()) {
            download->setProperty("enabled", "false");
            status->setProperty("text", "Network Status: No connection");
        }
        else if (x) {
            download->setProperty("enabled", "true");
            status->setProperty("text", "Network Status: Connected");
            x = true;
        }

        if(downloading == true)
            download->setProperty("enabled", "false");

        if (!currentIndex)
            exist->setProperty("text", " ");
}
