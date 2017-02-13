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

	void					setIngredient(QStandardItem* lpItem = 0, cPlugin* lpPlugin = 0);
	qint32					ingredientID(void);

	bool					isChanged();
private slots:
	void					ingredientEdit(const QModelIndex& modelIndex);

	void on_m_lpSave_clicked();

	void on_m_lpRevert_clicked();

	void on_m_lpClose_clicked();

private:
	Ui::cIngredientWindow*	ui;

	cPlugin*				m_lpDBPlugin;
	qint32					m_iIngredient;
	cIngredient				m_ingredient;
	cIngredient				m_ingredientSaved;
	QStandardItemModel*		m_lpIngredientValuesModel;
	QStandardItem*			m_lpItem;

protected:
	void					closeEvent(QCloseEvent *event);
};

#endif // CINGREDIENTWINDOW_H
