#include "scrollarea.h"

#include <QScrollArea>
#include <QHBoxLayout>

ScrollArea::ScrollArea(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	auto mainLayout = new QHBoxLayout(this);

	auto scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true);
	mainLayout->addWidget(scrollArea);

	m_pRealWidget = new QWidget;
	scrollArea->setWidget(m_pRealWidget);
}

ScrollArea::~ScrollArea()
{

}

QWidget* ScrollArea::getRealWidget()
{
	return m_pRealWidget;
}

