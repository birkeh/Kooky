#include "coptionsplugins.h"
#include "ui_coptionsplugins.h"
#include "coptions.h"

#include <QCheckBox>
#include <QSettings>


cOptionsPlugins::cOptionsPlugins(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cOptionsPlugins)
{
	init();
}

cOptionsPlugins::~cOptionsPlugins()
{
	delete ui;
}

void cOptionsPlugins::init()
{
	ui->setupUi(this);

	m_lpPluginsListModel	= new QStandardItemModel(0, 4);
	ui->m_lpPluginsList->setModel(m_lpPluginsListModel);

	QStringList	headerLabels	= QStringList() << tr("") << tr("Name") << tr("Version") << tr("Capability") << tr("File");
	m_lpPluginsListModel->setHorizontalHeaderLabels(headerLabels);

	connect(ui->m_lpPluginsList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &cOptionsPlugins::onOptionsPluginTreeSelectionChanged);
	connect(ui->m_lpPluginsList, &QTreeView::doubleClicked, this, &cOptionsPlugins::onOptionsPluginTreeDoubleClicked);
}

void cOptionsPlugins::setPlugins(QList<cPlugin*> &plugins)
{
	QSettings	settings;

	for(int z = 0;z < plugins.count();z++)
	{
		QStandardItem*	lpItemNew		= new QStandardItem;
		m_lpPluginsListModel->appendRow(lpItemNew);
		QModelIndex		index			= m_lpPluginsListModel->indexFromItem(lpItemNew);
		m_lpPluginsListModel->setData(index, QVariant::fromValue(plugins.at(z)), Qt::UserRole);
		QCheckBox*		lpCheckBox		= new QCheckBox(this);
		lpCheckBox->setChecked(settings.value(QString("plugins/%1/enabled").arg(plugins.at(z)->pluginName()), QVariant(false)).toBool());
		ui->m_lpPluginsList->setIndexWidget(m_lpPluginsListModel->index(index.row(), 0), lpCheckBox);
		connect(lpCheckBox, &QCheckBox::toggled, this, &cOptionsPlugins::onOptionsPluginTreePluginToggled);
		QStandardItem*	lpItemText		= new QStandardItem(plugins.at(z)->pluginName());
		m_lpPluginsListModel->setItem(index.row(), 1, lpItemText);
		QStandardItem*	lpItemVersion	= new QStandardItem(QString("%1").arg(plugins.at(z)->pluginVersion()));
		lpItemVersion->setTextAlignment(Qt::AlignRight);
		m_lpPluginsListModel->setItem(index.row(), 2, lpItemVersion);
		QString			szPluginType;
		switch(plugins.at(z)->capability())
		{
		case cPlugin::PluginCapNone:
			szPluginType	= "none";
			break;
		case cPlugin::PluginCapExport:
			szPluginType	= "export";
			break;
		case cPlugin::PluginCapImport:
			szPluginType	= "import";
			break;
		case cPlugin::PluginCapDB:
			szPluginType	= "database";
			break;
		default:
			szPluginType	= "unknown";
			break;
		}

		QStandardItem*	lpItemType		= new QStandardItem(szPluginType);
		m_lpPluginsListModel->setItem(index.row(), 3, lpItemType);

		QStandardItem*	lpItemFile		= new QStandardItem(plugins.at(z)->pluginFile());
		m_lpPluginsListModel->setItem(index.row(), 4, lpItemFile);
	}
	ui->m_lpPluginsList->resizeColumnToContents(0);
	ui->m_lpPluginsList->resizeColumnToContents(1);
	ui->m_lpPluginsList->resizeColumnToContents(2);
	ui->m_lpPluginsList->resizeColumnToContents(3);
	ui->m_lpPluginsList->resizeColumnToContents(4);
}

void cOptionsPlugins::onOptionsPluginTreeSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
	ui->m_lpButtonConfigure->setEnabled(true);
}

void cOptionsPlugins::onOptionsPluginTreePluginToggled(bool /*b*/)
{
	QObject*	lpSender	= QObject::sender();
	QCheckBox*	lpCheckBox	= 0;

	QModelIndex	index		= m_lpPluginsListModel->index(0, 0);
	for(;index.isValid();index = m_lpPluginsListModel->index(index.row()+1, 0))
	{
		lpCheckBox	= (QCheckBox*)ui->m_lpPluginsList->indexWidget(index);
		if(lpCheckBox == lpSender)
			break;
	}
	if(index.isValid())
	{
		cPlugin*	lpPlugin	= m_lpPluginsListModel->data(index, Qt::UserRole).value<cPlugin*>();
		if(lpPlugin)
		{
			QSettings	settings;
			settings.setValue(QString("plugins/%1/enabled").arg(lpPlugin->pluginName()), QVariant(lpCheckBox->isChecked()));

			if(lpPlugin->capability() == cPlugin::PluginCapDB && lpCheckBox->isChecked())
			{
				for(int z = 0;z < m_lpPluginsListModel->rowCount();z++)
				{
					QStandardItem*	lpItem		= m_lpPluginsListModel->item(z, 0);
					cPlugin*		lpPlugin1	= lpItem->data(Qt::UserRole).value<cPlugin*>();
					if(lpPlugin1 != lpPlugin)
					{
						if(lpPlugin1->capability() == cPlugin::PluginCapDB)
						{
							QCheckBox*	lpCheckBox	= (QCheckBox*)ui->m_lpPluginsList->indexWidget(m_lpPluginsListModel->index(z, 0));
							lpCheckBox->setChecked(false);
						}
					}
				}
			}
		}
		emit somethingChanged();
	}
}

void cOptionsPlugins::onOptionsPluginTreeDoubleClicked(const QModelIndex& index)
{
	QModelIndex	selected	= m_lpPluginsListModel->index(m_lpPluginsListModel->itemFromIndex(index)->row(), 0);
	showConfigDlg(selected);
}

void cOptionsPlugins::on_m_lpButtonConfigure_clicked()
{
	QModelIndex	selected	= m_lpPluginsListModel->index(m_lpPluginsListModel->itemFromIndex(ui->m_lpPluginsList->currentIndex())->row(), 0);

	if(!selected.isValid())
		return;

	showConfigDlg(selected);
}

void cOptionsPlugins::showConfigDlg(const QModelIndex& index)
{
	if(!index.isValid())
		return;

	cPlugin*	lpPlugin	= m_lpPluginsListModel->data(index, Qt::UserRole).value<cPlugin*>();
	if(!lpPlugin)
		return;

	switch(lpPlugin->capability())
	{
		case cPlugin::PluginCapDB:
		{
			cDBInterface*		lpDBInterface	= lpPlugin->dbInterface();
			if(lpDBInterface)
				lpDBInterface->config();
			break;
		}
		case cPlugin::PluginCapImport:
		{
			cImportInterface*	lpImportInterface	= lpPlugin->importInterface();
			if(lpImportInterface)
				lpImportInterface->config();
			break;
		}
		case cPlugin::PluginCapExport:
		{
			break;
		}
		default:
			break;
	}
}
