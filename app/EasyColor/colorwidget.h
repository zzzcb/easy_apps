#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QColor>

#include "qtcpp/common.h"

class ColorWidget : public QWidget
{
	Q_OBJECT
public:
	ColorWidget(QWidget* parent = nullptr);
	~ColorWidget();

	void setColor(QColor clr);
	QColor getColor();
	void setColorTextType(QtCpp::ColorTextType type);

	void setSelected(bool selected);

protected:
	void paintEvent(QPaintEvent* event) override;
	QSize sizeHint() const override;

	void mousePressEvent(QMouseEvent* event) override;

signals:
	void signalClicked();

private:
	QColor m_tClr;
	QtCpp::ColorTextType m_eClrTextType;
	bool m_bSelected;
};

#endif