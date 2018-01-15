#include <iostream>

#include <QApplication>
#include <QSplashScreen>
#include <qthread.h>

#include "MainWindow.h"

#include "AudioInterface.h"

#include "FIFOQueue.h"
#include "StereoSamplesBuffer.h"
#include "SamplesCollector.h"
#include "EffectsRenderer.h"
#include "EffectsController.h"
#include "EffectsFactory.h"


int main(int argc, char **argv) {
    // Supress warnings:
    (void) argc;
    (void) argv;

	//Start application
	QApplication app(argc, argv);
	//Show splash screen for 2 seconds
	QPixmap pixmap("../../src/logo.png");
	QSplashScreen splash(pixmap);
	splash.show();
	app.processEvents();
	//Initialize AudioInterface:
	AudioInterface::getInstance().initialize();
	//Initialize EffectsController:
	MainWindow mainWin;
	mainWin.setWindowTitle("BlinkyTune");
	mainWin.setWindowIcon(pixmap);
	mainWin.setupUi();
	QThread::sleep(2); // splash is shown for 2 seconds
	mainWin.show();
	splash.finish(&mainWin);
	return app.exec();

}