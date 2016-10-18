/**
  * \class cPlugin
  *
  * \brief This class holds data of an plugin.
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

#ifndef CPLUGIN_H
#define CPLUGIN_H

#include "cimportinterface.h"
#include "cdbinterface.h"
#include <QPluginLoader>
#include <QAction>


/*!
 \brief

*/
class cPlugin
{
public:
	/*!
	 \brief

	*/
	enum PluginCap
	{
		PluginCapNone	= 0,
		PluginCapImport	= 1,
		PluginCapExport	= 2,
		PluginCapDB		= 3,
	};

	cPlugin(const QString& szFile);
	/*!
	 \brief

	*/
	~cPlugin();

	/*!
	 \brief

	 \return bool
	*/
	bool				isValid();
	/*!
	 \brief

	 \return PluginCap
	*/
	PluginCap			capability();
	/*!
	 \brief

	 \return QString
	*/
	QString				pluginName();
	/*!
	 \brief

	 \return qint16
	*/
	qint16				pluginAPIVersion();
	/*!
	 \brief

	 \return qint16
	*/
	qint16				pluginVersion();
	/*!
	 \brief

	 \param lpAction
	*/
	void				setAction(QAction* lpAction);
	/*!
	 \brief

	 \return QAction
	*/
	QAction*			action();
	/*!
	 \brief

	 \return QString
	*/
	QString				pluginFile();

	/*!
	 \brief

	 \return cImportInterface
	*/
	cImportInterface*	importInterface();
	/*!
	 \brief

	 \return cDBInterface
	*/
	cDBInterface*		dbInterface();

	QString				author();
	QString				company();
	QString				link();
	QString				description();
	QString				copyright();

private:
	QPluginLoader*		m_lpPluginLoader; /*!< TODO: describe */
	cImportInterface*	m_lpImportInterface; /*!< TODO: describe */
	cDBInterface*		m_lpDBInterface; /*!< TODO: describe */
	QAction*			m_lpAction; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cPlugin*)

#endif // CPLUGIN_H
