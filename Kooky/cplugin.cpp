#include "cplugin.h"
#include <QObject>


cPlugin::cPlugin(const QString& szFile) :
	m_lpPluginLoader(0),
	m_lpImportInterface(0),
	m_lpAction(0)
{
	m_lpPluginLoader	= new QPluginLoader(szFile);
	if(!m_lpPluginLoader)
		return;
	if(!m_lpPluginLoader->load())
	{
		delete m_lpPluginLoader;
		m_lpPluginLoader = 0;
		return;
	}

	QObject*	lpObject	= m_lpPluginLoader->instance();
	if(!lpObject)
	{
		delete m_lpPluginLoader;
		m_lpPluginLoader = 0;
		return;
	}

	if(!szFile.left(1).compare("i", Qt::CaseInsensitive))
	{
		m_lpImportInterface	= qobject_cast<cImportInterface*>(lpObject);
		if(!m_lpImportInterface)
		{
			delete m_lpPluginLoader;
			m_lpPluginLoader = 0;
			return;
		}
	}
	else if(!szFile.left(1).compare("d", Qt::CaseInsensitive))
	{
		m_lpDBInterface	= qobject_cast<cDBInterface*>(lpObject);
		if(!m_lpDBInterface)
		{
			delete m_lpPluginLoader;
			m_lpPluginLoader = 0;
			return;
		}
	}
}

cPlugin::~cPlugin()
{
	if(m_lpPluginLoader)
		delete m_lpPluginLoader;
}

bool cPlugin::isValid()
{
	return(m_lpPluginLoader != 0);
}

cPlugin::PluginCap cPlugin::capability()
{
	if(m_lpImportInterface)
		return(PluginCapImport);
	else if(m_lpDBInterface)
		return(PluginCapDB);
	return(PluginCapNone);
}

QString cPlugin::pluginName()
{
	if(m_lpImportInterface)
		return(m_lpImportInterface->pluginName());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->pluginName());
	return("noname");
}

qint16 cPlugin::pluginAPIVersion()
{
	if(m_lpImportInterface)
			return(m_lpImportInterface->pluginAPIVersion());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->pluginAPIVersion());
	return(0);
}

qint16 cPlugin::pluginVersion()
{
	if(m_lpImportInterface)
			return(m_lpImportInterface->pluginVersion());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->pluginVersion());
	return(0);
}

QString cPlugin::pluginFile()
{
	return(m_lpPluginLoader->fileName());
}

void cPlugin::setAction(QAction* lpAction)
{
	m_lpAction	= lpAction;
}

QAction* cPlugin::action()
{
	return(m_lpAction);
}

cImportInterface* cPlugin::importInterface()
{
	return(m_lpImportInterface);
}

cDBInterface* cPlugin::dbInterface()
{
	return(m_lpDBInterface);
}

QString cPlugin::author()
{
	if(m_lpImportInterface)
		return(m_lpImportInterface->author());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->author());
	return("");
}

QString cPlugin::company()
{
	if(m_lpImportInterface)
		return(m_lpImportInterface->company());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->company());
	return("");
}

QString cPlugin::link()
{
	if(m_lpImportInterface)
		return(m_lpImportInterface->link());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->link());
	return("");
}

QString cPlugin::description()
{
	if(m_lpImportInterface)
		return(m_lpImportInterface->description());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->description());
	return("");
}

QString cPlugin::copyright()
{
	if(m_lpImportInterface)
		return(m_lpImportInterface->copyright());
	else if(m_lpDBInterface)
		return(m_lpDBInterface->copyright());
	return("");
}
