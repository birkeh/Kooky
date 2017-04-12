#ifndef CSQLITEPLUGIN_H
#define CSQLITEPLUGIN_H


#include "cdbinterface.h"

#include <QtCore>
#include <QObject>
#include <QString>
#include <QSqlDatabase>


/*!
 \brief

*/
class cSQLitePlugin : public QObject, public cDBInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "cSQLitePlugin" FILE "dSQLite.json")
	Q_INTERFACES(cDBInterface)

public:
	/*!
	 \brief

	 \return qint16
	*/
	qint16					pluginAPIVersion() { return(1); }
	/*!
	 \brief

	 \return QString
	*/
	QString					pluginName() { return("SQLite DB"); }
	/*!
	 \brief

	 \return qint16
	*/
	qint16					pluginVersion() { return(1); }
	/*!
	 \brief

	 \return iType
	*/
	iType					pluginType() { return(cInterface::iTypeDB); }

	/*!
	 \brief

	 \return bool
	*/
	bool					connect();
	/*!
	 \brief

	 \return bool
	*/
	bool					init();
	/*!
	 \brief

	 \return QString
	*/
	QString					lastError();

	/*!
	 \brief

	 \return bool
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
	qint32					create(const QString& szName, const QString &szGroup);
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
	/*!
	 \brief

	 \return bool
	*/
	bool					open();

	QSqlDatabase			m_db; /*!< TODO: describe */
	QString					m_szLastError; /*!< TODO: describe */
};

#endif // CSQLITEPLUGIN_H
