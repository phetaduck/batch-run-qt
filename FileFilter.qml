import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import "Icon.js" as MdiFont
import UIState 1.0

RowLayout {

    function turnFilter(b) {
        fileFilterState.fileFilterEnabled = b
        if (b) {
            filterSwitch.text = MdiFont.Icon.filter
        } else {
            filterSwitch.text = MdiFont.Icon.filterRemove
        }
    }

    function modelEmpty (b) {
        fileFilter.enabled = !b
        buttonRemoveFilterString.enabled = !b
        fileFilterState.fileFilterEnabled = !b
    }

    function reverseState() {
        buttonAddFilterString.visible = !buttonAddFilterString.visible
        fileFilter.visible = !fileFilter.visible
        newFieFilter.visible = !newFieFilter.visible
        newFieFilter.enabled = !newFieFilter.enabled
        newFieFilter.focus = !newFieFilter.focus
        buttonRemoveFilterString.visible = !buttonRemoveFilterString.visible
    }

    Button {
        id: filterSwitch
        flat: true
        Layout.maximumWidth: 40
        text: {
            if (fileFilterState.fileFilterEnabled)
                MdiFont.Icon.filter;
            else
                MdiFont.Icon.filterRemove
        }
        highlighted: !fileFilterState.fileFilterEnabled

        onClicked: {
            turnFilter(!fileFilterState.fileFilterEnabled)
        }
    }

    Button {
        id: buttonAddFilterString
        flat: true
        text: MdiFont.Icon.plus
        Layout.maximumWidth: 40
        onClicked: {
            reverseState()
            fileFilterState.append("*")
            newFieFilter.text = fileFilterState.back()
        }
    }

    TextField {
        id: newFieFilter
        visible: false
        enabled: false
        Layout.fillWidth: true
        Shortcut {
            sequence: StandardKey.Cancel
            onActivated: {
                if (focus) {
                    reverseState()
                    fileFilterState.removeLast()
                }
            }
        }

        onAccepted: {
            reverseState()
            if (!text.length) {
                fileFilterState.removeLast()
            } else {
                fileFilter.currentIndex = fileFilterState.size() - 1
            }
        }

        onTextChanged: {
            fileFilterState.setLast(text)
        }

    }

    ComboBox {
        id: fileFilter
        enabled: fileFilterState.fileFilterEnabled
        Layout.fillWidth: true
        model: fileFilterState.fileFilter
        onModelChanged: {
            modelEmpty(!fileFilterState.size())
        }
    }

    Button {
        id: buttonRemoveFilterString
        flat: true
        text: MdiFont.Icon.minus
        Layout.maximumWidth: 40
        onClicked: {
            fileFilterState.removeAt(fileFilter.currentIndex)
        }
    }
}
