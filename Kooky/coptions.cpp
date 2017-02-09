#include "coptions.h"
#include "ui_coptions.h"

#include "coptionsplugins.h"
#include "cplugininfo.h"

#include <QTreeWidgetItem>
#include <QPushButton>

#include <QMessageBox>


cOptions::cOptions(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cOptions),
	m_bOptionsTreeSelectionUndo(false)
{
	init();

	m_lpMainWindow	= (cMainWindow*)parent;
	m_pluginList	= m_lpMainWindow->pluginList();

	m_lpPluginRoot	= new QStandardItem("Plugins");
	m_lpOptionsTreeModel->appendRow(m_lpPluginRoot);

	for(int z = 0;z < m_pluginList.count();z++)
	{
		QStandardItem*		lpItemNew	= new QStandardItem(m_pluginList.at(z)->pluginName());
		lpItemNew->setData(QVariant::fromValue(m_pluginList.at(z)), Qt::UserRole);
		m_lpPluginRoot->appendRow(lpItemNew);
	}
	ui->m_lpOptionsTree->expandAll();
}

cOptions::~cOptions()
{
	delete ui;
}

void cOptions::init()
{
	ui->setupUi(this);
	ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

	m_lpOptionsTreeModel	= new QStandardItemModel(0, 1);
	ui->m_lpOptionsTree->setModel(m_lpOptionsTreeModel);

	ui->m_lpSplitter->setStretchFactor(0, 0);
	ui->m_lpSplitter->setStretchFactor(1, 1);

	connect(ui->m_lpOptionsTree->selectionModel(), &QItemSelectionModel::selectionChanged, this, &cOptions::onOptionsTreeSelectionChanged);
}

void cOptions::onOptionsTreeSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	if(m_bOptionsTreeSelectionUndo)
		return;

	QStandardItem*	lpSelected		= 0;
	QStandardItem*	lpDeSelected	= 0;

	if(selected.indexes().count())
		lpSelected		= m_lpOptionsTreeModel->itemFromIndex(selected.indexes().at(0));
	else
		return;

	if(deselected.indexes().count())
		lpDeSelected	= m_lpOptionsTreeModel->itemFromIndex(deselected.indexes().at(0));

	if(lpDeSelected)
	{
		if(ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->isEnabled())
		{
			if(QMessageBox::question(this, tr("Save"), tr("Data has been changed. Do you want to save?")) != QMessageBox::Yes)
			{
				m_bOptionsTreeSelectionUndo	= true;
				ui->m_lpOptionsTree->setCurrentIndex(deselected.indexes().at(0));
				m_bOptionsTreeSelectionUndo	= false;
				return;
			}
		}
		saveData(lpDeSelected);
	}

	if(lpSelected == m_lpPluginRoot)
	{
		cOptionsPlugins*	lpOptionsPlugins	= new cOptionsPlugins(this);
		lpOptionsPlugins->setPlugins(m_pluginList);
		ui->m_lpOptionsScrollArea->setWidget(lpOptionsPlugins);
		connect(lpOptionsPlugins, &cOptionsPlugins::somethingChanged, this, &cOptions::somethingChanged);
	}
	else
	{
		cPlugin*	lpPlugin	= lpSelected->data(Qt::UserRole).value<cPlugin*>();

		cPluginInfo*	lpPluginInfo	= new cPluginInfo;
		lpPluginInfo->setInfo(lpPlugin);
		ui->m_lpOptionsScrollArea->setWidget(lpPluginInfo);
	}
}

void cOptions::somethingChanged()
{
	ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

bool cOptions::saveData(QStandardItem* /*lpItem*/)
{
	return(true);
}

void cOptions::on_m_lpButtonBox_clicked(QAbstractButton *button)
{
	if(button == ui->m_lpButtonBox->button(QDialogButtonBox::Apply))
	{
		if(saveData())
			ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
	}
}

void cOptions::on_m_lpButtonBox_accepted()
{
	saveData();
	accept();
}

void cOptions::on_m_lpButtonBox_rejected()
{
	reject();
}
