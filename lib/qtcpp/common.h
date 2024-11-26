#ifndef QTCPP_COMMON_H
#define QTCPP_COMMON_H

#include <QString>
#include <QFile>
#include <QColor>
#include <QIcon>

#include "export.h"

namespace EasyLib
{
	namespace QtCpp
	{
		enum ColorTextType
		{
			Em_NONE,
			Em_RGBA,
			Em_HEX,
			Em_HSV
		};

		QIcon		API_EXPORT createIcon(const QString& file, bool bDarkIcon = false);
		QRect		API_EXPORT getCurScreenRect();
		QColor		API_EXPORT getScreenColor(const QPoint& pt);
		QString		API_EXPORT getColorText(QColor clr, ColorTextType type);
		QString		API_EXPORT getFileContent(QString filePath);
		QStringList API_EXPORT getCommonColor();
	}
}

#endif
