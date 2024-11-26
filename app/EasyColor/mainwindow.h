#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QHBoxLayout>
#include <QWindow>
#include <QTimer>
#include <QAction>
#include <QPlainTextEdit>

#include "propertybrowser/qtgroupboxpropertybrowser.h"
#include "propertybrowser/qtpropertymanager.h"
#include "propertybrowser/qteditorfactory.h"

#include "flowlayout/flowlayout.h"

#include "colorwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

protected:
	void showEvent(QShowEvent* event) override;

private:
	void initStyle();
	void initToolbar();
	void initPropertyBrowser();
	void initLayout();

	void updateColorInfo(QColor color);

	void slotPickColor();
	void slotAction(QAction* action);
	void slotChangeColor(ColorWidget* colorWidget);
	void slotColorPropChanged(QtProperty* prop, const QColor& color);

	//property browser
	QtGroupBoxPropertyBrowser* m_pBrowser;

	QtColorPropertyManager* m_pColorMngCanEdit;
	QtSliderFactory* m_pSliderFac;

	QtProperty* m_pColorProp;
	

	//splitter 
	QSplitter* m_pHSplitter;
	QSplitter* m_pLeftVSplitter;
	QSplitter* m_pRightVSplitter;
	
	ColorWidget* m_pColorWidget;
	QPlainTextEdit* m_pColorInfo;
	FlowLayout* m_pHistoryLayout;
	QWidget* m_pHistoryWidget;
	ColorWidget* m_pCurColorWidget;

	//action
	QAction* m_pStartPick;
	QAction* m_pEndPick;
	QAction* m_pConfirmPick;

	QTimer* m_pPickTimer;
};

#endif
