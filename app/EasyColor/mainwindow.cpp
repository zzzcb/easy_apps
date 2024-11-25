#include "mainwindow.h"


MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	//property browser
	m_pGroupMng = new QtGroupPropertyManager(this);
	
	m_pPointFMngCanEdit = new QtPointFPropertyManager(this);
	m_pDoubleFac = new QtDoubleSpinBoxFactory(this);

	m_pColorMngCanEdit = new QtColorPropertyManager(this);
	m_pColorFac = new QtColorEditorFactory(this);

	m_pBrowser = new QtTreePropertyBrowser;
	m_pBrowser->setHeaderVisible(false);
	m_pBrowser->setFactoryForManager(m_pPointFMngCanEdit->subDoublePropertyManager(), m_pDoubleFac);
	m_pBrowser->setFactoryForManager(m_pColorMngCanEdit, m_pColorFac);


	//中心窗体
	auto central = new QWidget;
	setCentralWidget(central);

	//中心窗体的布局
	auto mainLayout = new QHBoxLayout(central);
	mainLayout->addWidget(m_pBrowser);

	m_pBrowser->addProperty(m_pPointFMngCanEdit->addProperty("鼠标位置"));
	m_pBrowser->addProperty(m_pColorMngCanEdit->addProperty("颜色"));
}

MainWindow::~MainWindow()
{

}

