/**
  * \class cInterface
  *
  * \brief This is the base class for all plugins.
  *
  * \ingroup KOOKY
  *
  * This class implements basic interface functionality for all Kooky plugins.
  * All functions may be overwritten by derriving classes.
  *
  * \note Do not subclass this class directly, always use the appropriate subclass:
  * cDBInterface for database connectors, cImportInterface for import plugins and cExportInterface for export plugins.
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef CINTERFACE_H
#define CINTERFACE_H


#include <QString>
#include <QScrollArea>


/**
  * \brief
  */
class cInterface
{
public:
	/**
	  * \brief Defines the type of the interface.
	  *
	  */
	enum iType
	{
		iTypeImport	= 0,	/**< import plugin */
		iTypeExport	= 1,	/**< export plugin */
		iTypeDB		= 2,	/**< database connector */
	};

	/**
	  * \brief Returns the version of the API
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return qint16 version of the API
	  */
	virtual qint16	pluginAPIVersion() = 0;
	/**
	  * \brief Returns the name of the plugin.
	  *
	  * \note This function must be derived by the subclass.
	  * \note The name must be unique and will also be used to store configuration settings.
	  *
	  * \return QString name of the plugin.
	  */
	virtual QString	pluginName() = 0;
	/**
	  * \brief Version of the plugin.
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return qint16 version of the plugin.
	  */
	virtual qint16	pluginVersion() = 0;
	/**
	  * \brief Returns the type of the plugin.
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return iType type of the plugin (see enum iType).
	  */
	virtual iType	pluginType() = 0;

	/**
	  * \brief Calls the configuration dialog (if any).
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return bool true on success, false otherwise.
	  */
	virtual bool	config() = 0;

	virtual QString	author() = 0;
	/*!
	 \brief

	 \return QString
	*/
	virtual QString	company() = 0;
	/*!
	 \brief

	 \return QString
	*/
	virtual QString	link() = 0;
	/*!
	 \brief

	 \return QString
	*/
	virtual QString	description() = 0;
	/*!
	 \brief

	 \return QString
	*/
	virtual QString	copyright() = 0;
protected:
};


#endif // CINTERFACE_H
