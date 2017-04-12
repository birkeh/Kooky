#ifndef CINGREDIENTWINDOW_H
#define CINGREDIENTWINDOW_H


#include "cplugin.h"
#include "cingredient.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cIngredientWindow;
}


/*!
 \brief

*/
class cIngredientWindow : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \param parent
	*/
	explicit cIngredientWindow(QWidget *parent = 0);
	/*!
	 \brief

	*/
	~cIngredientWindow();

	/*!
	 \brief

	 \param lpItem
	 \param lpPlugin
	*/
	void					setIngredient(QStandardItem* lpItem = 0, cPlugin* lpPlugin = 0);
	/*!
	 \brief

	 \return qint32
	*/
	qint32					ingredientID(void);

	/*!
	 \brief

	 \param szIngredientGroup
	*/
	void					setIngredientGroup(const QString& szIngredientGroup);
	/*!
	 \brief

	 \return bool
	*/
	bool					isChanged();
	/*!
	 \brief

	*/
	void					forceClose();
private slots:
	/*!
	 \brief

	 \param text
	*/
	void					nameChanged(const QString& text);
	/*!
	 \brief

	 \param text
	*/
	void					groupChanged(const QString & text);
	/*!
	 \brief

	 \param modelIndex
	*/
	void					ingredientEdit(const QModelIndex& modelIndex);
	/*!
	 \brief

	*/
	void					saveClicked();
	/*!
	 \brief

	*/
	void					revertClicked();
	/*!
	 \brief

	*/
	void					closeClicked();

private:
	Ui::cIngredientWindow*	ui; /*!< TODO: describe */

	cPlugin*				m_lpDBPlugin; /*!< TODO: describe */
	qint32					m_iIngredient; /*!< TODO: describe */
	cIngredient				m_ingredient; /*!< TODO: describe */
	cIngredient				m_ingredientSaved; /*!< TODO: describe */
	QStandardItemModel*		m_lpIngredientValuesModel; /*!< TODO: describe */
	QStandardItem*			m_lpItem; /*!< TODO: describe */
	bool					m_bIsInitialized; /*!< TODO: describe */

	/*!
	 \brief

	 \return bool
	*/
	bool					save();
	/*!
	 \brief

	*/
	void					updateTitle();
protected:
	/*!
	 \brief

	*/
	void					checkGroupChanged();
	/*!
	 \brief

	 \param event
	*/
	void					closeEvent(QCloseEvent *event);
};

#endif // CINGREDIENTWINDOW_H
