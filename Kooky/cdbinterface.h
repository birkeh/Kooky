/**
  * \class cDBInterface
  *
  * \brief This is the base class for all database connector plugins.
  *
  * \ingroup KOOKY
  *
  * This class implements basic interface functionality for all Kooky database connector plugins.
  * All functions may be overwritten by derriving classes.
  *
  * \note
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef CDBINTERFACE_H
#define CDBINTERFACE_H


#include "cInterface.h"
#include "typedef.h"

#include <QtPlugin>
#include <QString>
#include <QStringList>


/**
  * \brief
  */
class cDBInterface : public cInterface
{
public:
	/**
	  * \brief Constructor.
	  *
	  */
	cDBInterface() : m_bConnected(false) { }
	/**
	  * \brief Destructor.
	  *
	  */
	virtual ~cDBInterface() {}

	/**
	  * \brief Opens a connection to the database.
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return bool true on success, false otherwise.
	  */
	virtual bool			connect() = 0;
	/**
	  * \brief Initializes the module with default values.
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return bool true on success, false otherwise.
	  */
	virtual bool			init() = 0;
	/**
	  * \brief Returns the current connection status.
	  *
	  * \note This function must be derived by the subclass.
	  *
	  * \return bool true if connected, false otherwise.
	  */
	bool					connected() { return(m_bConnected); }
	/**
	  * \brief Returns the last error message of the last operation.
	  *
	  * \return QString error message of the last operation.
	*/
	QString					lastError() { return(QString("no error")); }

	virtual qint32			exists(const QString& szName, const QString& szGroup) = 0;
	/*!
	 \brief

	 \param szGroup
	 \return qint32
	*/
	virtual qint32			existsGroup(const QString& szGroup) = 0;
	/*!
	 \brief

	 \param id
	 \param ingredientNumber
	 \return qint32
	*/
	virtual qint32			existsIngredient(qint32 id, qint16 ingredientNumber) = 0;
	/*!
	 \brief

	 \param szName
	 \param szGroup
	 \return qint32
	*/
	virtual qint32			create(const QString& szName, const QString& szGroup) = 0;
	/*!
	 \brief

	 \param id
	 \return bool
	*/
	virtual bool			deleteIngredient(qint32 id) = 0;
	/*!
	 \brief

	 \param szGroup
	 \return qint32
	*/
	virtual qint32			createGroup(const QString& szGroup) = 0;
	/*!
	 \brief

	 \param id
	 \param ingredientNumber
	 \param value
	 \return bool
	*/
	virtual bool			set(qint32 id, qint16 ingredientNumber, qreal value) = 0;
	/*!
	 \brief

	 \param id
	 \param szName
	 \return bool
	*/
	virtual bool			setName(qint32 id, const QString& szName) = 0;
	/*!
	 \brief

	 \param id
	 \param szGroup
	 \return bool
	*/
	virtual bool			setGroup(qint32 id, const QString& szGroup) = 0;
	/*!
	 \brief

	 \param id
	 \return QString
	*/
	virtual QString			name(qint32 id) = 0;
	/*!
	 \brief

	 \param id
	 \return QString
	*/
	virtual QString			group(qint32 id) = 0;
	/*!
	 \brief

	 \param id
	 \param ingredientNumber
	 \return qreal
	*/
	virtual qreal			get(qint32 id, qint16 ingredientNumber) = 0;
	/*!
	 \brief

	 \return INGREDIENT_LIST
	*/
	virtual INGREDIENT_LIST	ingredients() = 0;
	/*!
	 \brief

	 \return QStringList
	*/
	virtual QStringList		groups() = 0;
	/*!
	 \brief

	 \return bool
	*/
	virtual bool			beginTransaction() = 0;
	/*!
	 \brief

	 \return bool
	*/
	virtual bool			endTransaction() = 0;
protected:
	bool					m_bConnected; /*!< holds the current connection status. */
};

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(cDBInterface, "WIN-DESIGN.cDBInterface/1.0");
QT_END_NAMESPACE

#endif // CDBINTERFACE_H
