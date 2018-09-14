/*
 * Diego Henrique Dorta <diego.dorta@nxp.com>
 *
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickWindow>
#include <QWidget>
#include <QWindow>
#include <QProgressBar>
#include <QRect>
#include <QtWidgets/QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include "utils.h"
#include "thread.h"
#include <iostream>

using std::cerr;

int main(int argc, char *argv[])
{
    qmlRegisterType<Utils>("com.myself", 1, 0, "Utils");
    qmlRegisterType<Utils>("Utils", 1, 0, "Utils");
    qmlRegisterType<Utils>("Thread", 1, 0, "Thread");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto main_window_obj = engine.rootObjects()[0];
    #ifdef DEBUG
    auto main_window = qobject_cast<QQuickWindow *>(main_window_obj);
    cerr << "object name: " << main_window_obj->metaObject()->className() << '\n';
    cerr << "superclass: " << main_window_obj->metaObject()->superClass()->className() << '\n';
    cerr << "main_window: " << main_window << '\n';
    #endif

    auto combo = main_window_obj->findChild<QObject *>("COMBAO");
    auto utils = main_window_obj->findChild<Utils *>("UTILZAO");
    auto teste = main_window_obj->findChild<QObject *>("TESTE");
    auto bar = main_window_obj->findChild<QObject *>("BAR");
    auto rate = main_window_obj->findChild<QObject *>("RATE");
    auto device = main_window_obj->findChild<QObject *>("DEVICE");
    auto flash = main_window_obj->findChild<QObject *>("FLASH");
    auto download = main_window_obj->findChild<QObject *>("DOWNLOAD");
    auto exist = main_window_obj->findChild<QObject *>("EXIST");
    auto status = main_window_obj->findChild<QObject *>("STATUS");
    auto search = main_window_obj->findChild<QObject *>("SEARCH");

    #ifdef DEBUG
    cerr << "combo: " << combo << '\n';
    cerr << "utils: " << utils << '\n';
    #endif
    combo->setProperty("activeFocusOnPress", "false");
    teste->setProperty("activeFocusOnPress", "false");

    utils->combo = combo;
    utils->teste = teste;
    utils->bar = bar;
    utils->rate = rate;
    utils->device = device;
    utils->flash = flash;
    utils->download = download;
    utils->exist = exist;
    utils->status = status;
    utils->search = search;
    //Thread t("Thread inicialized");

    //t.start();
    return app.exec();
}
