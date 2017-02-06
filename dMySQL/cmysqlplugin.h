/**
  * \defgroup MYSQL MySQL Database Connector Plugin
  *
  * \brief
  *
  * This module is designed to connect to MySQL Databases.
  *
  */

/**
  * \class cMySQLPlugin
  *
  * \brief MySQL Database Connector Plugin class
  *
  * \ingroup MYSQL
  *
  * This class implements the database connector for MySQL.
  * All functions may be overwritten by derriving classes.
  *
  * \note
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date $Date: 2016/02/09
  */

#ifndef CMYSQLPLUGIN_H
#define CMYSQLPLUGIN_H


#include "cdbinterface.h"

#include <QtCore>
#include <QObject>
#include <QString>
#include <QSqlDatabase>


/**
  * \brief
  *
  */
class cMySQLPlugin : public QObject, public cDBInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "cMySQLPlugin" FILE "dMySQL.json")
	Q_INTERFACES(cDBInterface)

public:
	/**
	  * \brief Returns the version of the plugin API
	  *
	  * \return qint16 plugin API version
	  */
	qint16					pluginAPIVersion() { return(1); }
	/**
	  * \brief Returns the name of the plugin
	  *
	  * \return QString name of the plugin
	  */
	QString					pluginName() { return("MySQL DB"); }
	/**
	  * \brief returns the version of the plugin
	  *
	  * \return qint16 version of the plugin
	  */
	qint16					pluginVersion() { return(1); }
	/**
	  * \brief returns the type of the plugin.
	  *
	  * \return iType type of the plugin.
	  *
	  * Returns the type of the plugin. Possible values are:
	  * <ul>
	  * <li> cInterface::iTypeDB
	  * <br> plugin provides DB connector
	  * <li> cInterface::iTypeExport
	  * <br> plugin provides export capabilities
	  * <li> cInterface::iTypeImport
	  * <br> plugin provides import capabilities
	  * </ol>
	  * </ul>
	  */
	iType					pluginType() { return(cInterface::iTypeDB); }

	/**
	  * \brief connects to the database.
	  *
	  * \return bool true on success or false otherwise
	  */
	bool					connect();
	/**
	  * \brief initializes default settings for the plugin.
	  *
	  * \return bool true if settings where successfully tested or false otherwise.
	  */
	bool					init();
	/**
	  * \brief returns the last error string.
	  *
	  * \return QString last error
	  */
	QString					lastError();

	/**
	  * \brief calls the configuration dialog.
	  *
	  * \return bool true if the configuration has been changed successfully or false otherwise.
	  */
	bool					config();

	qint32					exists(const QString& szName, const QString& szGroup);
	qint32					existsGroup(const QString& szGroup);
	qint32					existsIngredient(qint32 id, qint16 ingredientNumber);
	qint32					create(const QString& szName, const QString& szGroup);
	qint32					createGroup(const QString& szGroup);
	bool					set(qint32 id, qint16 ingredientNumber, qreal value);
	QString					name(qint32 id);
	QString					group(qint32 id);
	qreal					get(qint32 id, qint16 ingredientNumber);
	INGREDIENT_LIST			ingredients();
	QStringList				groups();
	bool					beginTransaction();
	bool					endTransaction();

	QString					author();
	QString					company();
	QString					link();
	QString					description();
	QString					copyright();

protected:
	/**
	  * \brief opens the database.
	  *
	  * \return bool true on success or false otherwise.
	  */
	bool					open();

	QSqlDatabase			m_db; /*!< holds the database connection */
	QString					m_szLastError; /*!< holds the last error message */
};

#endif // CMYSQLPLUGIN_H
