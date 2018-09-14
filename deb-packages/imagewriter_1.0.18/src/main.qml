/*
 * Diego Henrique Dorta <diego.dorta@nxp.com>
 *
 */

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import com.myself 1.0
import QtQuick.Window 2.0
import Utils 1.0
import Thread 1.0

ApplicationWindow {

    id: window
    visible: true

    width: 470
    height: 245

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    Component.onCompleted: {
         setX(Screen.width / 2 - width / 2);
         setY(Screen.height / 2 - height / 2);
     }


    title: qsTr("i.MX Image Writer V1.0.18 Beta")

    menuBar: MenuBar {
        id: menubar
        Menu {

            title: qsTr("Help")

            MenuItem {
                text: qsTr("About")
                onTriggered: messageDialog.show(qsTr("i.MX Image Writer Application - diego.dorta@nxp.com"))
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {

            title: qsTr("Tool")

            MenuItem {
                text: qsTr("Sync Boards")
                onTriggered: utils.get_github_info();
            }
        }
    }

    MainForm {

        objectName: "mainform"

        Utils {
            id: utils
            objectName: "UTILZAO"
        }

        searchButton {
            id: searchButton
            objectName: "SEARCH"
            x: 368
            y: 99
            enabled: true
        }

        searchButton.onClicked: {
            utils.get_devices()
        }

        Label {
            id: downloadOrNot
            objectName: "EXIST"
            font.pixelSize: 10
            x: 370
            y: 65
        }

        downloadButton {
            objectName: "DOWNLOAD"
            id: downloadButton
            x: 368
            y: 141
            enabled: true
        }

        downloadButton.onClicked: {
             utils.get_sdcard_image(comboboard.currentText, comboc.currentText);
        }

        flashButton {
            objectName: "FLASH"
            id: flashButton
            x: 368
            y: 173
            enabled: true
        }

        flashButton.onClicked: {
                    //busyIndication.running = !busyIndication.running
                    progressbar.indeterminate = true
                    burn.start()
        }

        comboBoxBoard {
            id: comboboard
            currentIndex: 0
            activeFocusOnPress: true
            objectName: "COMBAO"

            model: [" "] /* comboBox empty */

            onCurrentIndexChanged: {    comboc.currentIndex = 0;
                                        comboc.model = [" "]
                                        utils.get_boards_info(comboboard.currentIndex)
            }
        }

        comboBoxConfig {
            id: comboc
            currentIndex: 0
            activeFocusOnPress: true
            objectName: "TESTE"

            model: [" "] /* comboBox empty */

            onCurrentIndexChanged: utils.enable_download(comboboard.currentText, comboc.currentText, comboc.currentIndex);
        }

        comboBoxDevice {
            id: combod
            currentIndex: 0
            activeFocusOnPress: true
            objectName: "DEVICE"

            model: [" "] /* comboBox empty */
        }

        ProgressBar {
            id: progressbar
            x: 86
            y: 156
            objectName: "BAR"
            orientation: Qt.Horizontal
            indeterminate: false

            minimumValue: 0.0
            maximumValue: 100.0

            clip: true

            onValueChanged: {
                //console.log("ProgressBar value: " + progressbar.value);
            }

            Text {
                    anchors { horizontalCenter: parent.horizontalCenter;  verticalCenter: parent.verticalCenter}
                    color: "black"
                    text: Math.floor((progressbar.value - progressbar.minimumValue) / (progressbar.maximumValue - progressbar.minimumValue) * 100) + '%'
            }
        }

        Label {
            id: rateLabel
            objectName: "RATE"
            font.pixelSize: 10
            x: 86
            y: 180
        }

        Label {
            id: statusLabel
            objectName: "STATUS"
            font.pixelSize: 10
            x: 19
            y: 201
        }

        Timer {
            id: timer
            interval: 1000; repeat: true
            running: true
            triggeredOnStart: true

            onTriggered: {
                utils.enable_download(comboboard.currentText, comboc.currentText, comboc.currentIndex)
            }
        }

        BusyIndicator {
        id: busyIndication
        x: 195
        y: 65
       }

       Timer {
            id: load
            interval: 1000; repeat: false
            running: true

            onTriggered: {
                busyIndication.running = !busyIndication.running
                utils.get_github_info();
            }
        }

        Timer {
            id: burn
            interval: 100; repeat: false
            running: false
            triggeredOnStart: false

            onTriggered: {
                flashButton.enabled = false
                utils.burning_sd_card(comboboard.currentText, comboc.currentText, combod.currentIndex, comboc.currentIndex);
            }
        }

        MessageDialog {
            id: messageDialog
            title: qsTr("Warning!")

            function show(caption) {
                messageDialog.text = caption;
                messageDialog.open();
            }
        }
    }    
}

