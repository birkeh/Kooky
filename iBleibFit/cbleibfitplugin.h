#ifndef CBLEIBFITPLUGIN_H
#define CBLEIBFITPLUGIN_H


#include <QtCore>
#include <QObject>
#include <QString>
#include "cimportinterface.h"


/*!
 \brief

*/
class cBleibFitPlugin : public QObject, public cImportInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "cBleibFitPlugin" FILE "iBleibFit.json")
	Q_INTERFACES(cImportInterface)

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
	QString					pluginName() { return("import Bleib Fit"); }
	/*!
	 \brief

	 \return qint16
	*/
	qint16					pluginVersion() { return(1); }
	/*!
	 \brief

	 \return iType
	*/
	iType					pluginType() { return(cInterface::iTypeImport); }

	/*!
	 \brief

	 \return bool
	*/
	bool					config();

	QString					author();
	QString					company();
	QString					link();
	QString					description();
	QString					copyright();

	/*!
	 \brief

	 \return QMap<QString, QString>
	*/
	QMap<QString, QString>	detailsCapability();
	/*!
	 \brief

	 \param szSearch
	 \param szDetails
	 \return QStringList
	*/
	QStringList				search(const QString& szSearch, const QString& szDetails = QString(""));
	/*!
	 \brief

	 \param iIndex
	 \return bool
	*/
	bool					load(qint16 iIndex);
	/*!
	 \brief

	 \param i
	 \return qreal
	*/
	qreal					value(cIngredient::iIngredient i);
	/*!
	 \brief

	 \return QString
	*/
	QString					ingredientName();
private:
	QStringList				m_szUrls; /*!< TODO: describe */
	QStringList				m_szIngredients; /*!< TODO: describe */
	qreal					m_rValues[cIngredient::iIngredientMax]; /*!< TODO: describe */
	qint16					m_iLoadedIndex; /*!< TODO: describe */
};

#endif // CBLEIBFITPLUGIN_H
