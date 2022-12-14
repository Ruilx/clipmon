#include "MainWindow.h"

#include <QApplication>

#include <src/Global.h>
#include <src/Tray.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationDisplayName(QObject::tr(ApplicationDisplayName));
	a.setApplicationName(ApplicationName);
	a.setApplicationVersion(VERSION_STR);


	MainWindow w;

	Tray tray(&w);
	tray.show();

	return a.exec();
}
