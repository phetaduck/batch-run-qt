QT += quick \
widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./Tasks \
./Utils \


HEADERS += \
    JSON/json.hpp \
    Tasks/PredefinedTasks.h \
    Tasks/Task.h \
    Tasks/taskmanager.h \
    Utils/helperutil.h \
    appstate.h \
    fallout4hardcode.h \
    filefilterstate.h \
    foldercontentlist.h \
    foldercontentmodel.h \
    settings.h

SOURCES += \
        Tasks/PredefinedTasks.cpp \
        Tasks/Task.cpp \
        Tasks/taskmanager.cpp \
        Utils/helperutil.cpp \
        appstate.cpp \
        fallout4hardcode.cpp \
        filefilterstate.cpp \
        foldercontentlist.cpp \
        foldercontentmodel.cpp \
        main.cpp \
        settings.cpp

RESOURCES += qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES +=

#update qml
qml_scenes.depends = $$PWD/resources/scene1.qml $$PWD/resources/scene2.qml ...
qml_scenes.commands =
QMAKE_EXTRA_TARGETS += qml_scenes
