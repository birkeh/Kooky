/**
  * \class cOptions
  *
  * \brief This dialog displays all options.
  *
  * \ingroup KOOKY
  *
  *
  *
  * \note
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef COPTIONS_H
#define COPTIONS_H

#include "cmainwindow.h"

#include <QDialog>
#include <QStandardItemModel>
#include <QItemSelection>
#include <QAbstractButton>


namespace Ui {
class cOptions;
}

/*!
 \brief

*/
class cOptions : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \param parent
	*/
	explicit			cOptions(QWidget *parent = 0);
	/*!
	 \brief

	*/
	~cOptions();

private slots:
	/*!
	 \brief

	 \param selected
	 \param deselected
	*/
	void				onOptionsTreeSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	void				on_m_lpButtonBox_clicked(QAbstractButton *button);
	void				on_m_lpButtonBox_accepted();
	void				on_m_lpButtonBox_rejected();

	void				somethingChanged();
private:
	Ui::cOptions*		ui; /*!< TODO: describe */
	cMainWindow*		m_lpMainWindow; /*!< TODO: describe */
	QList<cPlugin*>		m_pluginList; /*!< TODO: describe */
	QStandardItemModel*	m_lpOptionsTreeModel; /*!< TODO: describe */
	bool				m_bOptionsTreeSelectionUndo;

	QStandardItem*		m_lpPluginRoot;

	bool				saveData(QStandardItem *lpItem = 0);
protected:
	/*!
	 \brief

	*/
	void				init();
};

#endif // COPTIONS_H
