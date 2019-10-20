import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import "Icon.js" as MdiFont

import FolderContent 1.0
ItemDelegate {
    onClicked: {
        if (model.isFile) {
            checkBox.checked = !checkBox.checked
        } else {
            folderContentList.workingDir = textLabel.text
        }
    }
    RowLayout {
        anchors.fill: parent

        CheckBox {
            id: checkBox
            visible: model.isFile
            checked: model.selected
            onCheckedChanged: {
                model.selected = checked
                textLabel.font.italic = checked
            }
        }

        IconLabel {
            text: MdiFont.Icon.subdirectoryArrowRight
            visible: !model.isFile &&
                     model.name !== ".."
        }

        IconLabel {
            text: MdiFont.Icon.subdirectoryArrowLeft
            visible: !model.isFile &&
                     model.name === ".."

        }

        IconLabel {
            text: MdiFont.Icon.fileOutline
            visible: model.isFile
        }

        IconLabel {
            text: MdiFont.Icon.folderOutline
            visible: !model.isFile
        }

        Label {
            id: textLabel
            font.italic: checkBox.checked
            Layout.fillWidth: true
            text: model.name
            clip: true
        }
    }
}
