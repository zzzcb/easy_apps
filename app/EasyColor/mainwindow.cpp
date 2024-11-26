#include "mainwindow.h"

#include <QStyleFactory>
#include <QApplication>
#include <QScreen>
#include <QKeySequence>
#include <QToolBar>

#include "qtcpp/common.h"

QAction* newAction(QString text, QIcon icon,QKeySequence seq)
{
	auto act = new QAction(text);
	act->setIcon(icon);
	act->setShortcut(seq);

	return act;
}

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent), m_pCurColorWidget(nullptr)
{
	initStyle();
	initToolbar();
	initPropertyBrowser();

	initLayout();
	
	//定时器
	m_pPickTimer = new QTimer(this);
	connect(m_pPickTimer, &QTimer::timeout, [=]() {slotPickColor(); });
}

MainWindow::~MainWindow()
{

}

void MainWindow::showEvent(QShowEvent* event)
{
	m_pHSplitter->setSizes({ 100,200});
	m_pLeftVSplitter->setSizes({ 100,200 });
	m_pRightVSplitter->setSizes({ 100,200 });
}

void MainWindow::initStyle()
{
	//界面美化
	qApp->setStyle(QStyleFactory::create("Fusion"));
	qApp->setStyleSheet(QtCpp::getFileContent(":/qss/common.qss"));
}

void MainWindow::initToolbar()
{
	//菜单、快捷键
	m_pStartPick = newAction("开始拾取颜色",QtCpp::createIcon(":/images/run.png"), QKeySequence("Ctrl+S"));
	m_pConfirmPick = newAction("确定拾取颜色", QtCpp::createIcon(":/images/ok.png"), QKeySequence("Ctrl+D"));

	auto editToolBar = addToolBar("Edit");
	editToolBar->addAction(m_pStartPick);
	editToolBar->addAction(m_pConfirmPick);

	connect(m_pStartPick, &QAction::triggered, [=]() {slotAction(m_pStartPick); });
	connect(m_pConfirmPick, &QAction::triggered, [=]() {slotAction(m_pConfirmPick); });
}

void MainWindow::initPropertyBrowser()
{
	m_pColorMngCanEdit = new QtColorPropertyManager(this);
	m_pSliderFac = new QtSliderFactory(this);

	m_pBrowser = new QtGroupBoxPropertyBrowser;
	m_pBrowser->setFactoryForManager(m_pColorMngCanEdit->subIntPropertyManager(), m_pSliderFac);

	//添加颜色属性
	m_pColorProp = m_pColorMngCanEdit->addProperty("颜色");
	m_pBrowser->addProperty(m_pColorProp);

	connect(m_pColorMngCanEdit, &QtColorPropertyManager::valueChanged, this, &MainWindow::slotColorPropChanged);
}

void MainWindow::initLayout()
{
	//中心窗体
	auto central = new QWidget;
	setCentralWidget(central);
	central->setEnabled(false);

	//中心窗体的布局
	auto mainLayout = new QHBoxLayout(central);
	m_pHSplitter = new QSplitter(Qt::Horizontal);
	mainLayout->addWidget(m_pHSplitter);

	m_pLeftVSplitter = new QSplitter(Qt::Vertical);
	m_pColorInfo = new QPlainTextEdit;
	m_pColorInfo->setReadOnly(true);
	m_pLeftVSplitter->addWidget(m_pBrowser);
	m_pLeftVSplitter->addWidget(m_pColorInfo);
	m_pHSplitter->addWidget(m_pLeftVSplitter);

	m_pRightVSplitter = new QSplitter(Qt::Vertical);
	m_pColorWidget = new ColorWidget;
	m_pHistoryWidget = new QWidget;
	m_pHistoryLayout = new FlowLayout(m_pHistoryWidget);
	m_pRightVSplitter->addWidget(m_pColorWidget);
	m_pRightVSplitter->addWidget(m_pHistoryWidget);
	m_pHSplitter->addWidget(m_pRightVSplitter);
}

void MainWindow::updateColorInfo(QColor color)
{
	m_pColorWidget->setColor(color);
	m_pColorMngCanEdit->setValue(m_pColorProp, color);

	m_pColorInfo->clear();
	QStringList clrs;
	clrs << "HEX:" + QtCpp::getColorText(color, QtCpp::ColorTextType::Em_HEX)
		<< "HSV:" + QtCpp::getColorText(color, QtCpp::ColorTextType::Em_HSV)
		<< "RGBA:" + QtCpp::getColorText(color, QtCpp::ColorTextType::Em_RGBA);
	for (auto& clr : clrs)
		m_pColorInfo->appendPlainText(clr);
}

void MainWindow::slotPickColor()
{
	auto newPos = QCursor::pos();
	auto color = QtCpp::grabScreenColor(newPos);

	updateColorInfo(color);
}

void MainWindow::slotAction(QAction* action)
{
	if (action == m_pStartPick)
	{
		m_pColorMngCanEdit->blockSignals(true);
		m_pPickTimer->start(30);
		centralWidget()->setEnabled(false);
	}
	else if (action == m_pConfirmPick)
	{
		m_pColorMngCanEdit->blockSignals(false);
		m_pPickTimer->stop();
		centralWidget()->setEnabled(true);

		auto clrWidget = new ColorWidget;
		clrWidget->setColor(m_pColorWidget->getColor());
		clrWidget->setSelected(true);
		connect(clrWidget, &ColorWidget::signalClicked, [=]() {slotChangeColor(clrWidget); });

		m_pHistoryLayout->addWidget(clrWidget);

		if (m_pCurColorWidget)
		{
			m_pCurColorWidget->setSelected(false);
		}
		m_pCurColorWidget = clrWidget;
	}
}

void MainWindow::slotChangeColor(ColorWidget* colorWidget)
{
	if (m_pCurColorWidget)
		m_pCurColorWidget->setSelected(false);

	colorWidget->setSelected(true);
	m_pCurColorWidget = colorWidget;

	updateColorInfo(m_pCurColorWidget->getColor());
}

void MainWindow::slotColorPropChanged(QtProperty* prop, const QColor& color)
{
	if (prop == m_pColorProp)
	{
		updateColorInfo(color);

		if (m_pCurColorWidget)
			m_pCurColorWidget->setColor(color);
	}
}
