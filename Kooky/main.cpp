#include "cmainwindow.h"
#include "csplashscreen.h"

#include <QApplication>
#include <QPixmap>
#include <QThread>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QPixmap			pixmap(":/images/splash");
	cSplashScreen	splashScreen(pixmap);
	splashScreen.show();
	splashScreen.showMessage("initializing ...");
	QThread::msleep(1000);

	a.processEvents();

	splashScreen.showMessage("loading database ...");

	QCoreApplication::setOrganizationName("WIN-DESIGN");
	QCoreApplication::setOrganizationDomain("windesign.at");
	QCoreApplication::setApplicationName("Kooky");

	cMainWindow w;
	w.showMaximized();
	splashScreen.finish(&w);

	return a.exec();
}
