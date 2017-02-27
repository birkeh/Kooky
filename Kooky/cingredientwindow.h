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

	void					setIngredientGroup(const QString& szIngredientGroup);
	bool					isChanged();
	void					forceClose();
private slots:
	void					nameChanged(const QString& text);
	void					groupChanged(const QString & text);
	void					ingredientEdit(const QModelIndex& modelIndex);
	void					saveClicked();
	void					revertClicked();
	void					closeClicked();

private:
	Ui::cIngredientWindow*	ui;

	cPlugin*				m_lpDBPlugin;
	qint32					m_iIngredient;
	cIngredient				m_ingredient;
	cIngredient				m_ingredientSaved;
	QStandardItemModel*		m_lpIngredientValuesModel;
	QStandardItem*			m_lpItem;
	bool					m_bIsInitialized;

	bool					save();
	void					updateTitle();
protected:
	void					checkGroupChanged();
	void					closeEvent(QCloseEvent *event);
};

#endif // CINGREDIENTWINDOW_H
