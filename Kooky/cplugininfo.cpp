#include "cplugininfo.h"
#include "cInterface.h"
#include "ui_cplugininfo.h"


cPluginInfo::cPluginInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cPluginInfo)
{
	ui->setupUi(this);
}

cPluginInfo::~cPluginInfo()
{
	delete ui;
}

void cPluginInfo::setInfo(cPlugin *lpPlugin)
{
	if(!lpPlugin)
		return;

	ui->m_lpPluginName->setText(lpPlugin->pluginName());
	ui->m_lpCopyright->setText(lpPlugin->copyright());
	ui->m_lpFileName->setText(lpPlugin->pluginFile());

	if(lpPlugin->capability() == cPlugin::PluginCapDB)
		ui->m_lpPluginType->setText(tr("Database"));
	else if(lpPlugin->capability() == cPlugin::PluginCapExport)
		ui->m_lpPluginType->setText(tr("Export"));
	else
		ui->m_lpPluginType->setText(tr("Import"));

	ui->m_lpPluginVersion->setText(QString("%1").arg(lpPlugin->pluginVersion()));
	ui->m_lpPluginAPIVersion->setText(QString("%1").arg(lpPlugin->pluginAPIVersion()));
	ui->m_lpAuthor->setText(lpPlugin->author());
	ui->m_lpCompany->setText(lpPlugin->company());
	ui->m_lpLink->setText(QString("<a href=\"%1\">%1").arg(lpPlugin->link()));
	ui->m_lpLink->setTextFormat(Qt::RichText);
	ui->m_lpLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui->m_lpLink->setOpenExternalLinks(true);
	ui->m_lpDescription->setText(lpPlugin->description());
}
