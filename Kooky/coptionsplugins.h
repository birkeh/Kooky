/**
  * \class cOptionsPlugins
  *
  * \brief This dialog displays all plugins.
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

#ifndef COPTIONSPLUGINS_H
#define COPTIONSPLUGINS_H

#include "cplugin.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class cOptionsPlugins;
}

/*!
 \brief

*/
class cOptionsPlugins : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \param parent
	*/
	explicit				cOptionsPlugins(QWidget *parent = 0);
	/*!
	 \brief

	*/
	~cOptionsPlugins();

	/*!
	 \brief

	 \param plugins
	*/
	void					setPlugins(QList<cPlugin*>& plugins);

signals:
	void					somethingChanged();
private slots:
	/*!
	 \brief

	 \param selected
	 \param deselected
	*/
	void					onOptionsPluginTreeSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	/*!
	 \brief

	 \param index
	*/
	void					onOptionsPluginTreeDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \param b
	*/
	void					onOptionsPluginTreePluginToggled(bool b);
	/*!
	 \brief

	*/
	void					on_m_lpButtonConfigure_clicked();

private:
	Ui::cOptionsPlugins*	ui; /*!< TODO: describe */
	QStandardItemModel*		m_lpPluginsListModel; /*!< TODO: describe */

protected:
	/*!
	 \brief

	*/
	void					init();
	/*!
	 \brief

	 \param index
	*/
	void					showConfigDlg(const QModelIndex& index);
};

#endif // COPTIONSPLUGINS_H
