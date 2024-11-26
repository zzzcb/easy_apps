#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QWidget>

#include "export.h"

namespace EasyLib
{
	class API_EXPORT ScrollArea : public QWidget
	{
		Q_OBJECT
	public:
		ScrollArea(QWidget* parent = nullptr);
		~ScrollArea();

		QWidget* getRealWidget();

	private:
		QWidget* m_pRealWidget;
	};
}

#endif
