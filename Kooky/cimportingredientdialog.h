/**
  * \class cImportIngredientDialog
  *
  * \brief This dialog imports ingredients based on the selected import plugin.
  *
  * \ingroup KOOKY
  *
  * This dialog imports ingredients based on the selected import plugin.
  *
  * \note
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef CIMPORTINGREDIENTDIALOG_H
#define CIMPORTINGREDIENTDIALOG_H


#include "cplugin.h"
#include "cingredient.h"

#include <QDialog>
#include <QList>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class cImportIngredientDialog;
}

/**
  * \brief
  *
  */
class cImportIngredientDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	  * \brief
	  *
	  * \param parent
	  */
	explicit						cImportIngredientDialog(QWidget *parent = 0);
	/**
	  * \brief
	  *
	  */
	~cImportIngredientDialog();

	/**
	  * \brief
	  *
	  * \param pluginList
	  */
	void							setPluginList(const QList<cPlugin*> pluginList, const QString& szPlugin = QString(""));
	cIngredient						toIngredient();

	QString							pluginSelected();

	void							setIngredientGroupList(const QStringList ingredientGroupList);
private:
	Ui::cImportIngredientDialog*	ui; /*!< TODO: describe */
	QStandardItemModel*				m_lpIngredientListModel; /*!< TODO: describe */
	QStandardItemModel*				m_lpIngredientDetailsModel; /*!< TODO: describe */

private slots:
	void							on_m_lpSearchButton_clicked();
	void							on_m_lpSearchString_textChanged(const QString &arg1);
	/**
	  * \brief
	  *
	  * \param selected
	  * \param deselected
	  */
	void							onIngredientListSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

protected:
	QList<cPlugin*>					m_pluginList; /*!< TODO: describe */

	/**
	  * \brief
	  *
	  * \param group
	  * \return QStandardItem
	  */
	QStandardItem*					addGroup(const QString& group);
	/**
	  * \brief
	  *
	  */
	void							init();
	/**
	  * \brief
	  *
	  */
	void							initIngredientList();
	/**
	  * \brief
	  *
	  */
	void							initIngredientDetails();
};

#endif // CIMPORTINGREDIENTDIALOG_H
