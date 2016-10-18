#include "cmdiarea.h"
#include <QSettings>
#include <QPainter>


cMdiArea::cMdiArea(QWidget *parent) :
	QMdiArea(parent)
{
	QSettings	settings;
	m_background	= QImage(settings.value("program/background", QVariant(":/images/image1")).toString());
}

void cMdiArea::paintEvent(QPaintEvent *event)
{
	QMdiArea::paintEvent(event);

	QPainter	painter(viewport());
	QRect		target	= this->rect();
	QRect		source	= m_background.rect();

	if(!source.width() || !source.height() || !m_background.width() || !m_background.height())
		return;

	int			w		= target.height()*source.width()/source.height();
	int			h		= target.width()*source.height()/source.width();

	if(w > target.width())
		target.setWidth(w);
	else if(h > target.height())
		target.setHeight(h);

	painter.drawImage(target, m_background, source);
}
