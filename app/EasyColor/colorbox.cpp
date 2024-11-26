#include "colorbox.h"

#include <QPainter>
#include <QTextOption>

const QString g_selectColor = "#ff673c";

ColorBox::ColorBox(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	m_bSelected = false;
}

ColorBox::~ColorBox()
{

}

void ColorBox::setColor(QColor clr)
{
	m_tClr = clr;
	update();
}

QColor ColorBox::getColor()
{
	return m_tClr;
}

void ColorBox::setSelected(bool selected)
{
	m_bSelected = selected;
	update();
}

void ColorBox::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	//绘制颜色
	if (m_tClr.isValid())
		painter.fillRect(rect().adjusted(3,3,-3,-3), m_tClr);

	//绘制选中边框
	if (m_bSelected)
	{
		painter.setPen(QColor(g_selectColor));
		painter.drawRect(rect().adjusted(1, 1, -1, -1));
	}
}

QSize ColorBox::sizeHint() const
{
	return QSize(30, 30);
}

void ColorBox::mousePressEvent(QMouseEvent* event)
{
	emit signalClicked();
	QWidget::mousePressEvent(event);
}
