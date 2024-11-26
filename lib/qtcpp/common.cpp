#include "common.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QCursor>

QString QtCpp::getFileContent(QString filePath)
{
	QString content;
	QFile f(filePath);
	if (f.open(QIODevice::ReadOnly))
	{
		content = f.readAll();
	}
	f.close();
	return content;
}

QColor QtCpp::grabScreenColor(const QPoint& p)
{
	auto screen = QGuiApplication::screenAt(p);
	if (!screen)
		screen = QGuiApplication::primaryScreen();
	auto screenRect = screen->geometry();
	auto pixmap = screen->grabWindow(0, p.x() - screenRect.x(), p.y() - screenRect.y(), 1, 1);
	auto image = pixmap.toImage();

	return image.pixel(0, 0);
}


QIcon API_EXPORT QtCpp::createIcon(const QString& file, bool bDarkIcon)
{
	QPixmap normal(file);

	QPainter p;
	if (bDarkIcon)
	{
		p.begin(&normal);
		p.setCompositionMode(QPainter::CompositionMode_SourceIn);
		p.fillRect(normal.rect(), QColor(32, 32, 32));
		p.end();
	}

	QIcon icon;
	icon.addPixmap(normal, QIcon::Normal);

	//禁用状态
	QPixmap disabled(normal.size());
	disabled.fill(Qt::transparent);

	p.begin(&disabled);
	p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
	p.setOpacity(0.5);
	p.drawPixmap(0, 0, normal);
	p.end();

	icon.addPixmap(disabled, QIcon::Disabled);

	return icon;
}

QRect API_EXPORT QtCpp::getCurScreenRect()
{
	auto screen = QGuiApplication::screenAt(QCursor::pos());
	if (!screen)
		screen = QGuiApplication::primaryScreen();
	return screen->geometry();
}

QString  QtCpp::getColorText(QColor clr, ColorTextType type)
{
	QString clrText;
	if (type == ColorTextType::Em_RGBA)
		clrText = QString("%1 %2 %3 %4").arg(clr.red()).arg(clr.green()).arg(clr.blue()).arg(clr.alpha());
	else if (type == ColorTextType::Em_HEX)
		clrText = clr.name(QColor::HexRgb);
	else if (type == ColorTextType::Em_HSV)
		clrText = QString("%1 %2 %3").arg(clr.hue()).arg(clr.saturation()).arg(clr.value());
	return clrText;
}

QStringList API_EXPORT QtCpp::getCommonColor()
{
	return {
	"#FFFFFF", // 白色
	"#000000", // 黑色
	"#FF0000", // 红色
	"#00FF00", // 绿色
	"#0000FF", // 蓝色
	"#FFFF00", // 黄色
	"#00FFFF", // 青色
	"#FF00FF", // 品红
	"#808080", // 灰色
	"#FFA500", // 橙色
	"#800080", // 紫色
	"#A52A2A", // 棕色
	"#006400", // 深绿色
	"#00008B"  // 深蓝色
	};
}
