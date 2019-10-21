#include "appstate.h"


AppState::AppState(int argc, char* argv[])
	: app(argc, argv), engine(), url(QStringLiteral("qrc:/main.qml"))
{
	QFontDatabase::addApplicationFont(":/MdiFont.ttf");
	setupNames();

	registerQMLTypes();
	exposeObjectsToQml();

	connectSlots();
	engine.load(url);
}

void AppState::setupNames()
{
	app.setOrganizationName(QStringLiteral("batch-run-qt"));
	app.setOrganizationDomain(QStringLiteral("batch-run-qt"));
	app.setApplicationName(QStringLiteral("batch-run-qt"));
}

void AppState::registerQMLTypes()
{
	qmlRegisterType<FolderContentModel>("FolderContent", 1, 0, "FolderContentModel");
	qmlRegisterUncreatableType<FolderContentList>(
				"FolderContent", 1, 0, "FolderContentList",
				QStringLiteral("FolderContentList should not be created in QML"));
}

void AppState::connectSlots()
{
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
									 &app, [=](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
					QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

	QObject::connect(&fileFilterState, SIGNAL(fileFilterEnabledChanged(bool)),
									 &folderContentList, SLOT(filteringEnabled(bool)));
	QObject::connect(&fileFilterState, SIGNAL(fileFilterChanged(QStringList)),
									 &folderContentList, SLOT(filterChanged(QStringList)));
}

void AppState::exposeObjectsToQml()
{
	engine.rootContext()->setContextProperty(
				QStringLiteral("folderContentList"),
				&folderContentList);
	engine.rootContext()->setContextProperty(
				QStringLiteral("fileFilterState"),
				&fileFilterState);
}

int AppState::exec() {
	return app.exec();
}
