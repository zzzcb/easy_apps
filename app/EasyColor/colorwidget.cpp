#include "colorwidget.h"

#include <QPainter>
#include <QTextOption>

const QString g_selectColor = "#ff673c";

ColorWidget::ColorWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	m_eClrTextType = QtCpp::ColorTextType::Em_NONE;
	m_bSelected = false;
}

ColorWidget::~ColorWidget()
{

}

void ColorWidget::setColor(QColor clr)
{
	m_tClr = clr;
	update();
}

QColor ColorWidget::getColor()
{
	return m_tClr;
}

void ColorWidget::setColorTextType(QtCpp::ColorTextType type)
{
	m_eClrTextType = type;
	update();
}

void ColorWidget::setSelected(bool selected)
{
	m_bSelected = selected;
	update();
}

void ColorWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	//绘制颜色
	if (m_tClr.isValid())
		painter.fillRect(rect().adjusted(3,3,-3,-3), m_tClr);

	//绘制颜色文字
	QString clrText = QtCpp::getColorText(m_tClr, m_eClrTextType);
	if (!clrText.isEmpty())
	{
		QTextOption opt;
		opt.setAlignment(Qt::AlignCenter);
		painter.drawText(rect(), clrText, opt);
	}

	//绘制选中边框
	if (m_bSelected)
	{
		painter.setPen(QColor(g_selectColor));
		painter.drawRect(rect().adjusted(1, 1, -1, -1));
	}
}

QSize ColorWidget::sizeHint() const
{
	return QSize(30, 30);
}

void ColorWidget::mousePressEvent(QMouseEvent* event)
{
	emit signalClicked();
	QWidget::mousePressEvent(event);
}
