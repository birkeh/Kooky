#ifndef CINGREDIENTWINDOW_H
#define CINGREDIENTWINDOW_H


#include "cplugin.h"

#include <QWidget>


namespace Ui {
class cIngredientWindow;
}


class cIngredientWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cIngredientWindow(QWidget *parent = 0);
	~cIngredientWindow();

	void	setIngredient(qint32 iIngredient, cPlugin* lpPlugin);
private:
	Ui::cIngredientWindow *ui;

	cPlugin*	m_lpDBPlugin;
	qint32		m_iIngredient;
};

#endif // CINGREDIENTWINDOW_H
