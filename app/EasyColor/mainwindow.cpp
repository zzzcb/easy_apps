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
	:QMainWindow(parent), m_pCurColorBox(nullptr)
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
	m_pRightVSplitter->setSizes({ 100,200,200 });
}

void MainWindow::initStyle()
{
	//界面美化
	qApp->setStyle(QStyleFactory::create("Fusion"));
	qApp->setStyleSheet(EasyLib::QtCpp::getFileContent(":/qss/common.qss"));
}

void MainWindow::initToolbar()
{
	//快捷键
	m_pStartPick = newAction("开始拾取颜色", EasyLib::QtCpp::createIcon(":/images/run.png"), QKeySequence("Ctrl+S"));
	m_pConfirmPick = newAction("确定拾取颜色", EasyLib::QtCpp::createIcon(":/images/ok.png"), QKeySequence("Ctrl+D"));

	auto editToolBar = addToolBar("Edit");
	editToolBar->addAction(m_pStartPick);
	editToolBar->addAction(m_pConfirmPick);

	connect(m_pStartPick, &QAction::triggered, [=]() {slotAction(m_pStartPick); });
	connect(m_pConfirmPick, &QAction::triggered, [=]() {slotAction(m_pConfirmPick); });
}

void MainWindow::initPropertyBrowser()
{
	m_pMngColor = new QtColorPropertyManager(this);
	m_pFacSlider = new QtSliderFactory(this);

	m_pBrowser = new QtGroupBoxPropertyBrowser;
	m_pBrowser->setFactoryForManager(m_pMngColor->subIntPropertyManager(), m_pFacSlider);

	//添加颜色属性
	m_pPropColor = m_pMngColor->addProperty("颜色");
	m_pBrowser->addProperty(m_pPropColor);

	connect(m_pMngColor, &QtColorPropertyManager::valueChanged, this, &MainWindow::slotColorPropChanged);
}

void MainWindow::initLayout()
{
	//中心窗体
	auto central = new QWidget;
	setCentralWidget(central);

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
	m_pColorDisplay = new ColorBox;
	auto commonColorArea = new EasyLib::ScrollArea;
	auto commonColorLayout = new EasyLib::FlowLayout(commonColorArea->getRealWidget());
	for (auto& color : EasyLib::QtCpp::getCommonColor())
	{
		auto widget = new ColorBox;
		widget->setColor(QColor(color));
		commonColorLayout->addWidget(widget);
		connect(widget, &ColorBox::signalClicked, [=]() {slotColorBoxClicked(widget); });
	}
	auto historyColorArea = new EasyLib::ScrollArea;
	m_pHistoryColorLayout = new EasyLib::FlowLayout(historyColorArea->getRealWidget());
	m_pRightVSplitter->addWidget(m_pColorDisplay);
	m_pRightVSplitter->addWidget(commonColorArea);
	m_pRightVSplitter->addWidget(historyColorArea);
	m_pHSplitter->addWidget(m_pRightVSplitter);
}

void MainWindow::updateColor(QColor color)
{
	m_pColorDisplay->setColor(color);
	m_pMngColor->setValue(m_pPropColor, color);

	m_pColorInfo->clear();
	QStringList clrs;
	clrs << "HEX:" + EasyLib::QtCpp::getColorText(color, EasyLib::QtCpp::ColorTextType::Em_HEX)
		<< "HSV:" + EasyLib::QtCpp::getColorText(color, EasyLib::QtCpp::ColorTextType::Em_HSV)
		<< "RGBA:" + EasyLib::QtCpp::getColorText(color, EasyLib::QtCpp::ColorTextType::Em_RGBA);
	for (auto& clr : clrs)
		m_pColorInfo->appendPlainText(clr);
}

void MainWindow::slotPickColor()
{
	auto newPos = QCursor::pos();
	auto color = EasyLib::QtCpp::getScreenColor(newPos);

	updateColor(color);
}

void MainWindow::slotAction(QAction* action)
{
	if (action == m_pStartPick)
	{
		m_pMngColor->blockSignals(true);
		m_pPickTimer->start(30);
		centralWidget()->setEnabled(false);
	}
	else if (action == m_pConfirmPick)
	{
		m_pMngColor->blockSignals(false);
		m_pPickTimer->stop();
		centralWidget()->setEnabled(true);

		auto clrBox = new ColorBox;
		clrBox->setColor(m_pColorDisplay->getColor());
		clrBox->setSelected(true);
		connect(clrBox, &ColorBox::signalClicked, [=]() {slotColorBoxClicked(clrBox); });

		m_pHistoryColorLayout->addWidget(clrBox);

		if (m_pCurColorBox)
			m_pCurColorBox->setSelected(false);

		m_pCurColorBox = clrBox;
	}
}

void MainWindow::slotColorBoxClicked(ColorBox* colorBox)
{
	if (m_pCurColorBox)
		m_pCurColorBox->setSelected(false);

	colorBox->setSelected(true);
	m_pCurColorBox = colorBox;

	updateColor(m_pCurColorBox->getColor());
}

void MainWindow::slotColorPropChanged(QtProperty* prop, const QColor& color)
{
	if (prop == m_pPropColor)
	{
		updateColor(color);

		if (m_pCurColorBox)
			m_pCurColorBox->setColor(color);
	}
}
