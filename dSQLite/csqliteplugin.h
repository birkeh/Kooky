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
	qint32					existsGroup(const QString& szGroup);
	qint32					existsIngredient(qint32 id, qint16 ingredientNumber);
	qint32					create(const QString& szName, const QString &szGroup);
	qint32					createGroup(const QString& szGroup);
	bool					set(qint32 id, qint16 ingredientNumber, qreal value);
	bool					setName(qint32 id, const QString& szName);
	bool					setGroup(qint32 id, const QString& szGroup);
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
	/*!
	 \brief

	 \return bool
	*/
	bool					open();

	QSqlDatabase			m_db; /*!< TODO: describe */
	QString					m_szLastError; /*!< TODO: describe */
};

#endif // CSQLITEPLUGIN_H
