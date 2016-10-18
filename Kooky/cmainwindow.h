/**
  * \defgroup KOOKY Kooky Main Program
  *
  * \brief
  *
  * This is the main program of Kooky.
  *
  */

/**
  * \class cMainWindow
  *
  * \brief This is the class that implements the main window.
  *
  * \ingroup KOOKY
  *
  * This class implements the main window and main functionality of Kooky.
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */


#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "cplugin.h"

#include <QList>
#include <QMainWindow>
#include <QStandardItemModel>


namespace Ui
{
	class cMainWindow;
}

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/**
	  * \brief Constructor.
	  *
	  * \param parent
	  */
	explicit cMainWindow(QWidget *parent = 0);
	/**
	  * \brief Destructor.
	  *
	  */
	~cMainWindow();

	void				loadIngredients();

	/**
	  * \brief Returns the list of loaded plugins.
	  *
	  * \return QList<cPlugin *> List of loaded plugins.
	  */
	QList<cPlugin*>		pluginList();
private slots:
	/**
	  * \brief Testing of import trigger raised by import plugins
	  *
	  */
	void				pluginImportTriggered();
	/**
	  * \brief Testing of export trigger raised by export plugins
	  *
	  */
	void				pluginExportTriggered();
	/**
	  * \brief Testing of database trigger raised by database connector plugins
	  *
	  */
	void				pluginDBTriggered();
	/**
	  * \brief Menu entry "File -> Exit" triggered.
	  *
	  */
	void				menuFileExitTriggered();
	/**
	  * \brief Menu entry "Tools -> Options" triggered.
	  *
	  */
	void				menuToolsOptionsTriggered();

	/**
	  * \brief Custom contest menu of ingredients list has been requested.
	  *
	  * \param point Current position of mouse cursor.
	  */
	void				ingredientsListCustomContextMenu(const QPoint& point);
	/**
	  * \brief New ingredient has been requested.
	  *
	  */
	void				ingredientsListNewTriggered();
	/**
	  * \brief Import of ingredient has been requested.
	  *
	  */
	void				ingredientsListImportTriggered();
	/**
	  * \brief Delete of ingredient has been requested.
	  *
	  */
	void				ingredientsListDeleteTriggered();
	/**
	  * \brief Edit of ingredient has been requested.
	  *
	  */
	void				ingredientsListEditTriggered();

private:
	Ui::cMainWindow*	ui; /**< the main window GUI */
	QList<cPlugin*>		m_pluginList; /**< List of loaded plugins */
	QStandardItemModel*	m_lpIngredientsListModel; /**< standard item model for ingredients list */
	QAction*			m_lpIngredientsListNew; /**< "New Ingredient" Action for ingredients context menu */
	QAction*			m_lpIngredientsListImport; /**< "Import Ingredient" Action for ingredients context menu */
	QAction*			m_lpIngredientsListDelete; /**< "Delee Ingredient" Action for ingredients context menu */
	QAction*			m_lpIngredientsListEdit; /**< "Edit Ingredient" Action for ingredients context menu */
	QMenu*				m_lpIngredientsListMenu; /**< Context menu for ingredients list */

	cPlugin*			m_lpDB;

	/**
	  * \brief Initialized main windows.
	  *
	  */
	void				init();
	/**
	  * \brief Initializes default settings for Kooky.
	  *
	  */
	void				initDefaultSettings();
	/**
	  * \brief Loads plugins in the given path.
	  *
	  * \param szPluginDir Path to plugins
	  */
	void				loadPlugins(const QString& szPluginDir);
	/**
	  * \brief Finds a plugin with the given action.
	  *
	  * \param lpAction Action of the plugin.
	  * \return cPlugin Plugin corresponding to the action, NULL if not found.
	  */
	cPlugin*			plugin(QAction* lpAction);
protected:
};

#endif // CMAINWINDOW_H
