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
	/*!
	 \brief

	 \param szGroup
	 \return qint32
	*/
	qint32					existsGroup(const QString& szGroup);
	/*!
	 \brief

	 \param id
	 \param ingredientNumber
	 \return qint32
	*/
	qint32					existsIngredient(qint32 id, qint16 ingredientNumber);
	/*!
	 \brief

	 \param szName
	 \param szGroup
	 \return qint32
	*/
	qint32					create(const QString& szName, const QString& szGroup);
	/*!
	 \brief

	 \param szGroup
	 \return qint32
	*/
	qint32					createGroup(const QString& szGroup);
	/*!
	 \brief

	 \param id
	 \return bool
	*/
	bool					deleteIngredient(qint32 id);
	/*!
	 \brief

	 \param id
	 \param ingredientNumber
	 \param value
	 \return bool
	*/
	bool					set(qint32 id, qint16 ingredientNumber, qreal value);
	/*!
	 \brief

	 \param id
	 \param szName
	 \return bool
	*/
	bool					setName(qint32 id, const QString& szName);
	/*!
	 \brief

	 \param id
	 \param szGroup
	 \return bool
	*/
	bool					setGroup(qint32 id, const QString& szGroup);
	/*!
	 \brief

	 \param id
	 \return QString
	*/
	QString					name(qint32 id);
	/*!
	 \brief

	 \param id
	 \return QString
	*/
	QString					group(qint32 id);
	/*!
	 \brief

	 \param id
	 \param ingredientNumber
	 \return qreal
	*/
	qreal					get(qint32 id, qint16 ingredientNumber);
	/*!
	 \brief

	 \return INGREDIENT_LIST
	*/
	INGREDIENT_LIST			ingredients();
	/*!
	 \brief

	 \return QStringList
	*/
	QStringList				groups();
	/*!
	 \brief

	 \return bool
	*/
	bool					beginTransaction();
	/*!
	 \brief

	 \return bool
	*/
	bool					endTransaction();

	/*!
	 \brief

	 \return QString
	*/
	QString					author();
	/*!
	 \brief

	 \return QString
	*/
	QString					company();
	/*!
	 \brief

	 \return QString
	*/
	QString					link();
	/*!
	 \brief

	 \return QString
	*/
	QString					description();
	/*!
	 \brief

	 \return QString
	*/
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
