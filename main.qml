import QtQuick 2.13
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.13
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1
import Qt.labs.platform 1.0
import "Icon.js" as MdiFont
import "BRUtils.js" as Utils

ApplicationWindow {

    id: window
    visible: true
    width: 1024
    height: 748
    title: qsTr("batch-run")

    Settings {
        id: setting
        category: "mainWindow"
        property alias width: window.width
        property alias height: window.height
        property alias x: window.x
        property alias y: window.y
        fileName: "./batch-run-qt.ini"
    }

    header: ToolBar {

        FolderSelect {
            anchors.fill: parent
        }
    }

    ColumnLayout {
        id: leftLayout
        width: 400
        height: parent.height
        anchors.left: parent.left

        FileFilter {
            id: fileFilter
            Layout.fillWidth: true
        }

        FolderContentList {
            id: scrollViewFiles
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

    }

    ScrollView {
        id: scrollViewText
        height: parent.height
        anchors.left: leftLayout.right
        anchors.right: parent.right
        Button {
            text: MdiFont.Icon.plus
            width: 50
            height: 50
        }

        /*
        TaskUI {
            width: 300
            height: 400
        }
        */
    }

}
