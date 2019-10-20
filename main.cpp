#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>

#include "foldercontentlist.h"
#include "foldercontentmodel.h"

#include "settings.h"
#include "filefilterstate.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

		QGuiApplication app(argc, argv);
		app.setOrganizationName(QStringLiteral("batch-run-qt"));
		app.setOrganizationDomain(QStringLiteral("batch-run-qt"));
		app.setApplicationName(QStringLiteral("batch-run-qt"));
		QFontDatabase::addApplicationFont(":/MdiFont.ttf");

    qmlRegisterType<FolderContentModel>("FolderContent", 1, 0, "FolderContentModel");
		qmlRegisterUncreatableType<FolderContentList>(
					"FolderContent", 1, 0, "FolderContentList",
					QStringLiteral("FolderContentList should not be created in QML"));
		qmlRegisterUncreatableType<FolderContentList>(
					"UIState", 1, 0, "UIState",
					QStringLiteral("UIState should not be created in QML"));

    FolderContentList folderContentList;
		FileFilterState fileFilterState;
		QObject::connect(&fileFilterState, SIGNAL(fileFilterEnabledChanged(bool)),
										 &folderContentList, SLOT(filteringEnabled(bool)));
		QObject::connect(&fileFilterState, SIGNAL(fileFilterChanged(QStringList)),
										 &folderContentList, SLOT(filterChanged(QStringList)));

    QQmlApplicationEngine engine;

		engine.rootContext()->setContextProperty(
					QStringLiteral("folderContentList"),
					&folderContentList);
		engine.rootContext()->setContextProperty(
					QStringLiteral("fileFilterState"),
					&fileFilterState);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
		engine.load(url);

    return app.exec();
}
