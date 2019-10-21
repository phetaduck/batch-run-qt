import QtQuick 2.13
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.13
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0

import "Icon.js" as MdiFont
import "BRUtils.js" as Utils

RowLayout {

    FolderDialog {
        id: workingDirDialog
        title: "Select directory"
        modality: Qt.ApplicationModal
        onAccepted: {
            console.log("folder : " + Utils.urlToString(folder))
            console.log("currentFolder : " + Utils.urlToString(currentFolder))
            console.log("old working dir: " + folderContentList.workingDir)
            folderContentList.workingDir = Utils.urlToString(folder)
            console.log("new working dir: " + folderContentList.workingDir)
        }
    }

    Button {
        flat: true
        text: MdiFont.Icon.folderOpen
        font.family: "Material Design Icons"
        font.pixelSize: 24
        onClicked: {
            workingDirDialog.currentFolder  = Qt.resolvedUrl("file:///" + folderContentList.workingDir)
            workingDirDialog.open()
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
            folderContentList.workingDir = text
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
}
