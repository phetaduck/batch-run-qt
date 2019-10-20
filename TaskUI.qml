import QtQuick 2.13
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.13
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1
import Qt.labs.folderlistmodel 2.12
import "Icon.js" as MdiFont

GroupBox {
    clip: true
    label: CheckBox {
        id: completed
        checkable: false
        checked: false
        text: program.text
    }
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillHeight: false
            Layout.fillWidth: true
            Label {
                Layout.fillWidth: true
                id: shellLabel
                text: "shell:"
            }
            TextField {
                Layout.fillWidth: true
                id: shell
                text: "cmd"
            }
        }


        RowLayout {
            Layout.fillHeight: false
            Layout.fillWidth: true
            Label {
                id: programLabel
                text: "program:"
            }
            TextField {
                id: program
                Layout.fillWidth: true
                text: "dir"
            }
        }
        ListView {
            id: arguments
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: 10
            delegate: ItemDelegate {
                clip: true
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    }
}
