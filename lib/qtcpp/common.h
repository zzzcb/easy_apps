#ifndef QTCPP_COMMON_H
#define QTCPP_COMMON_H

#include <QString>
#include <QFile>
#include <QColor>
#include <QIcon>

#include "export.h"

namespace QtCpp
{
	enum ColorTextType
	{
		Em_NONE,
		Em_RGBA,
		Em_HEX,
		Em_HSV
	};

	QString API_EXPORT getFileContent(QString filePath);
	QColor API_EXPORT grabScreenColor(const QPoint& p);
	QIcon API_EXPORT createIcon(const QString& file,bool bDarkIcon = false);
	QRect API_EXPORT getCurScreenRect();
	QString API_EXPORT getColorText(QColor clr, ColorTextType type);
	QStringList API_EXPORT getCommonColor();
};

#endif
