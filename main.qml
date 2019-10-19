import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 748
    title: qsTr("batch-run")

    Action {
        id: actionNew
        text: qsTr("&New")
        shortcut: StandardKey.New
        icon.name: "document-new"
        onTriggered: textArea.placeholderText = "To do - New"
    }

    Action {
        id: actionOpen
        text: qsTr("&Open")
        shortcut: StandardKey.Open
        icon.name: "document-open"
        onTriggered: textArea.placeholderText = "To do - Open"
    }

    Action {
        id: actionSave
        text: qsTr("&Save")
        shortcut: StandardKey.Save
        icon.name: "document-save"
        onTriggered: textArea.placeholderText = "To do - Save"
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {action: actionNew}
            MenuItem {action: actionOpen}
            MenuItem {action: actionSave}
        }
    }

    header: ToolBar {
        RowLayout {
            ToolButton {action: actionNew}
            ToolButton {action: actionOpen}
            ToolButton {action: actionSave}
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
        TextArea {
            id: textArea
            anchors.fill: parent
            height: parent.height
        }
    }

}
