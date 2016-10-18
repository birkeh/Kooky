#ifndef CSPLASHSCREEN_H
#define CSPLASHSCREEN_H


#include <QSplashScreen>


class cSplashScreen : public QSplashScreen
{
public:
	cSplashScreen(const QPixmap & pixmap = QPixmap(), Qt::WindowFlags f = 0);

	virtual void	drawContents(QPainter *painter);
};

#endif // CSPLASHSCREEN_H
