#ifndef CINGREDIENTWINDOW_H
#define CINGREDIENTWINDOW_H


#include "cplugin.h"
#include "cingredient.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cIngredientWindow;
}


class cIngredientWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cIngredientWindow(QWidget *parent = 0);
	~cIngredientWindow();

	void					setIngredient(qint32 iIngredient, cPlugin* lpPlugin);
	qint32					ingredientID(void);

	bool					isChanged();
private slots:
	void					ingredientEdit(const QModelIndex& modelIndex);

private:
	Ui::cIngredientWindow*	ui;

	cPlugin*				m_lpDBPlugin;
	qint32					m_iIngredient;
	cIngredient				m_ingredient;
	cIngredient				m_ingredientSaved;
	QStandardItemModel*		m_lpIngredientValuesModel;
};

#endif // CINGREDIENTWINDOW_H
