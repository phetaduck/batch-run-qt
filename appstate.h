#ifndef APPSTATE_H
#define APPSTATE_H

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>

#include "foldercontentlist.h"
#include "foldercontentmodel.h"

#include "settings.h"
#include "filefilterstate.h"

class AppState {
public:

	AppState(int argc, char* argv[]);

	template <typename T>
	int qmlReqisterAndExpose(
			const QString& name,
			T t,
			const char* uri,
			const char* qmlName,
			int versionMajor = 1,
			int versionMinor = 0);

	template <typename T>
	int qmlReqisterUncreatableAndExpose(
			const QString& name,
			T t,
			const char* uri,
			const char* qmlName,
			int versionMajor,
			int versionMinor,
			QString message);

	int exec();

private:

	void registerQMLTypes();

	void connectSlots();

	void exposeObjectsToQml();

	void setupNames();

	QApplication app;
	QQmlApplicationEngine engine;
	QUrl url;

	FolderContentList folderContentList;
	FileFilterState fileFilterState;

};

template <typename T>
int AppState::qmlReqisterAndExpose(
		const QString& name,
		T t,
		const char* uri,
		const char* qmlName,
		int versionMajor,
		int versionMinor)
{
	int out = qmlRegisterType<T>(uri, versionMajor, versionMinor, qmlName);
	engine.rootContext()->setContextProperty(
				name,
				&t);
	return out;
}

template <typename T>
int AppState::qmlReqisterUncreatableAndExpose(
		const QString& name,
		T t,
		const char* uri,
		const char* qmlName,
		int versionMajor,
		int versionMinor,
		QString message)
{
	QString actualMessage = std::move(message);
	if (message.isEmpty()) {
		actualMessage = QString (qmlName) +
										QString (" should not be created in QML");
	}
	int out = qmlRegisterUncreatableType<T>(
				t, uri, versionMajor, versionMinor, qmlName, actualMessage);
	engine.rootContext()->setContextProperty(
				name,
				&t);
	return out;

}

#endif // APPSTATE_H
