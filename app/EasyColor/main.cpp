#include <QApplication>

#include "mainwindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	MainWindow mw;
	mw.setWindowTitle("EasyColor | 0.9.0");
	mw.resize(500, 400);
	mw.show();

	return app.exec();
}