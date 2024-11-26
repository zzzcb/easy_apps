#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QColor>

class ColorBox : public QWidget
{
	Q_OBJECT

public:
	ColorBox(QWidget* parent = nullptr);
	~ColorBox();

	void	setColor(QColor clr);
	void	setSelected(bool selected);

	QColor	getColor();

protected:
	QSize	sizeHint() const override;
	void	paintEvent(QPaintEvent* event) override;
	void	mousePressEvent(QMouseEvent* event) override;

signals:
	void	signalClicked();

private:
	QColor		m_tClr;
	bool		m_bSelected;
};

#endif