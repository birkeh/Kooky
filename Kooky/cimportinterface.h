/**
  * \class cImportInterface
  *
  * \brief Interface class for importing data
  *
  * \ingroup KOOKY
  *
  * This class implements basic import functionality for Kooky.
  * All functions may be overwritten by derriving classes.
  *
  * \note Attempts at zen rarely work.
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date $Date: 2016/02/09
  */

#ifndef CIMPORTINTERFACE_H
#define CIMPORTINTERFACE_H

#include "cingredient.h"
#include "cInterface.h"

#include <QtPlugin>
#include <QString>
#include <QStringList>
#include <QMap>


/*!
 \brief

*/
class cImportInterface : public cInterface
{
public:
	cImportInterface() : m_bLoaded(false) {}

	/**
	  * \brief
	  *
	  * \return QMap<QString, QString>
	  */
	virtual QMap<QString, QString>	detailsCapability() = 0;
	/**
	  * \brief
	  *
	  * \param szSearch
	  * \param szDetails
	  * \return QStringList
	  */
	virtual QStringList				search(const QString& szSearch, const QString& szDetails = QString("")) = 0;
	/**
	  * \brief
	  *
	  * \param iIndex
	  * \return bool
	  */
	virtual bool					load(qint16 iIndex) = 0;
	/**
	  * \brief
	  *
	  * \return bool
	  */
	bool							loaded() { return(m_bLoaded); }
	/**
	  * \brief
	  *
	  * \param i
	  * \return qreal
	  */
	virtual qreal					value(cIngredient::iIngredient i) = 0;
	/**
	  * \brief
	  *
	  * \param i
	  * \return qreal
	  */
	QString							valueStr(cIngredient::iIngredient i);
	/**
	  * \brief
	  *
	  * \param i
	  * \return QString
	  */
	QString							name(cIngredient::iIngredient i);
	/**
	  * \brief
	  *
	  * \param i
	  * \return QString
	  */
	QString							group(cIngredient::iIngredient i);
	/**
	  * \brief
	  *
	  * \return QString
	  */
	virtual QString					ingredientName() = 0;
protected:
	bool							m_bLoaded; /*!< TODO: describe */
	qint16							m_iLoadedIndex; /*!< TODO: describe */
};

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(cImportInterface, "WIN-DESIGN.cImportInterface/1.0");
QT_END_NAMESPACE

#endif // CIMPORTINTERFACE_H
