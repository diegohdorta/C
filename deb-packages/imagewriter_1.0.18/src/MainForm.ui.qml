import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480
    property alias searchButton: searchButton
    property alias comboBoxDevice: comboBoxDevice
    property alias downloadButton: downloadButton
    property alias comboBoxConfig: comboBoxConfig
    property alias flashButton: flashButton
    property alias comboBoxBoard: comboBoxBoard

    RowLayout {
        anchors.verticalCenterOffset: 106
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
    }

    Button {
        id: flashButton
        x: 368
        y: 173
        text: qsTr("Flash")
    }

    ComboBox {
        id: comboBoxBoard
        x: 84
        y: 27
        width: 272
        height: 22
    }

    Text {
        id: chooseBoardText
        x: 19
        y: 27
        text: qsTr("Board:")
        font.pixelSize: 15
    }

    Row {
    }

    RowLayout {
    }

    ComboBox {
        id: comboBoxConfig
        x: 84
        y: 59
        width: 272
        height: 22
    }

    Text {
        id: chooseBoardText1
        x: 19
        y: 59
        text: qsTr("Image:")
        font.pixelSize: 15
    }

    Button {
        id: downloadButton
        x: 368
        y: 141
        text: qsTr("Download")
    }

    Text {
        id: chooseDevice
        x: 19
        y: 99
        text: qsTr("Device:")
        font.pixelSize: 15
    }

    ComboBox {
        id: comboBoxDevice
        x: 84
        y: 97
        width: 272
        height: 22
    }

    Text {
        id: chooseDevice1
        x: 86
        y: 141
        text: qsTr("Download progress")
        font.pixelSize: 10
    }

    Button {
        id: searchButton
        x: 368
        y: 99
        text: qsTr("Search")
    }
}
