import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import "Icon.js" as MdiFont

import FolderContent 1.0

ScrollView {

    ListView {
        clip: true

        model: FolderContentModel {
            list: folderContentList
        }

        delegate: FolderContentListItem {
            width: parent.width
        }
    }
}
