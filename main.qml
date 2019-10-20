import QtQuick 2.13
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.13
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1
import "Icon.js" as MdiFont

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
        RowLayout {
            anchors.fill: parent

            function urlToString(fileUrl) {
                var path = fileUrl.toString();
                // remove prefixed "file:///"
                path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
                // unescape html codes like '%23' for '#'
                var cleanPath = decodeURIComponent(path);
                return cleanPath
            }

            Button {
                flat: true
                text: MdiFont.Icon.folderOpen
                font.family: "Material Design Icons"
                font.pixelSize: 24
                onClicked: {
                    actionOpen.trigger()
                }
            }

            TextField {
                id: textFieldWorkingDir
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                text: folderContentList.workingDir
                rightPadding: 6
                leftPadding: 6
                //selectByMouse: true

                Shortcut {
                    sequence: StandardKey.Cancel
                    onActivated: {
                        if (focus) {
                            focus = false
                        }
                    }
                }

                onAccepted: {
                    textEdited()
                    focus = false
                }

            }

            Button {
                flat: true
                text: MdiFont.Icon.play
                font.family: "Material Design Icons"
                font.pixelSize: 24
                onClicked: {
                }
            }

            Action {
                id: actionOpen
                text: MdiFont.Icon.folderOpen
                shortcut: StandardKey.Open
                icon.name: "document-open"
                onTriggered: {
                    workingDirDialog.folder = Qt.resolvedUrl("file:///" + folderContentList.workingDir)
                    workingDirDialog.open()
                }

            }

            FileDialog {
                id: workingDirDialog
                title: "Select directory"
                selectFolder: true
                onAccepted: {
                    if (folder.length)
                        folderContentList.workingDir = urlToString(folder)
                }
            }
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
        TaskUI {
            width: 300
            height: 400
        }
    }

}
