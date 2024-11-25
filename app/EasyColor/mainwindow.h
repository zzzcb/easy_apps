#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "propertybrowser/qttreepropertybrowser.h"
#include "propertybrowser/qtpropertymanager.h"
#include "propertybrowser/qteditorfactory.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:





	//property browser
	QtTreePropertyBrowser* m_pBrowser;

	QtGroupPropertyManager* m_pGroupMng;

	QtPointFPropertyManager* m_pPointFMngCanEdit;
	QtDoubleSpinBoxFactory* m_pDoubleFac;

	QtColorPropertyManager* m_pColorMngCanEdit;
	QtColorEditorFactory* m_pColorFac;
};

#endif
