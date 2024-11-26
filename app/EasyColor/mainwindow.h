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
#include "easywidget/scrollarea.h"

#include "colorbox.h"

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

	void updateColor(QColor color);

	void slotPickColor();
	void slotAction(QAction* action);
	void slotColorBoxClicked(ColorBox* colorBox);
	void slotColorPropChanged(QtProperty* prop, const QColor& color);

	//property browser
	QtProperty*					m_pPropColor;
	QtSliderFactory*			m_pFacSlider;
	QtColorPropertyManager*		m_pMngColor;
	QtGroupBoxPropertyBrowser*	m_pBrowser;

	//界面布局 
	QSplitter*					m_pHSplitter;
	QSplitter*					m_pLeftVSplitter;
	QSplitter*					m_pRightVSplitter;
	
	ColorBox*					m_pColorDisplay;
	QPlainTextEdit*				m_pColorInfo;
	EasyLib::FlowLayout*		m_pHistoryColorLayout;

	QAction*					m_pStartPick;
	QAction*					m_pConfirmPick;

	//其他
	QTimer*						m_pPickTimer;
	ColorBox*					m_pCurColorBox;
};

#endif
