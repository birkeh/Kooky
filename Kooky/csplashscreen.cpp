#include "csplashscreen.h"

#include <QPainter>


cSplashScreen::cSplashScreen(const QPixmap &pixmap, Qt::WindowFlags f) :
	QSplashScreen(pixmap, f)
{
}

void cSplashScreen::drawContents(QPainter *painter)
{
	QFont	font	= this->font();
	font.setPixelSize(15);
	font.setBold(true);
	this->setFont(font);

	painter->setPen(Qt::white);
	QRect r = rect();
	r.setLeft(10);
	r.setTop(r.bottom()-20);
	painter->drawText(r, message());
 }
