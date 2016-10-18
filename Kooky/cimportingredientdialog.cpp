#include "cimportingredientdialog.h"
#include "ui_cimportingredientdialog.h"

#include "cmessageanimatedialog.h"

#include <QSettings>


cImportIngredientDialog::cImportIngredientDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImportIngredientDialog),
	m_lpIngredientListModel(0),
	m_lpIngredientDetailsModel(0)
{
	init();
}

cImportIngredientDialog::~cImportIngredientDialog()
{
	delete ui;
}

void cImportIngredientDialog::init()
{
	ui->setupUi(this);

	initIngredientList();
	initIngredientDetails();
}

void cImportIngredientDialog::initIngredientList()
{
	if(!m_lpIngredientListModel)
	{
		m_lpIngredientListModel		= new QStandardItemModel(0, 1);
		ui->m_lpIngredientList->setModel(m_lpIngredientListModel);
		connect(ui->m_lpIngredientList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(onIngredientListSelectionChanged(QItemSelection,QItemSelection)));
	}
	m_lpIngredientListModel->clear();
}

void cImportIngredientDialog::initIngredientDetails()
{
	if(!m_lpIngredientDetailsModel)
	{
		m_lpIngredientDetailsModel	= new QStandardItemModel(0, 2);
		ui->m_lpIngredientDetails->setModel(m_lpIngredientDetailsModel);
	}
	m_lpIngredientDetailsModel->clear();
	QStringList	headerLabels	= QStringList() << tr("Group/Name") << tr("Value");
	m_lpIngredientDetailsModel->setHorizontalHeaderLabels(headerLabels);
}

void cImportIngredientDialog::setPluginList(const QList<cPlugin*> pluginList)
{
	m_pluginList	= pluginList;

	for(int z = 0;z < m_pluginList.count();z++)
	{
		cPlugin*	lpPlugin	= m_pluginList.at(z);
		if(lpPlugin->capability() == cPlugin::PluginCapImport)
		{
			QSettings	settings;
			if(settings.value(QString("plugins/%1/enabled").arg(lpPlugin->pluginName()), QVariant(false)).toBool())
				ui->m_lpSource->addItem(lpPlugin->pluginName(), QVariant::fromValue(lpPlugin));
		}
	}
	ui->m_lpSource->setCurrentIndex(0);
}

void cImportIngredientDialog::on_m_lpSearchString_textChanged(const QString &/*arg1*/)
{
	if(ui->m_lpSearchString->text().length())
		ui->m_lpSearchButton->setEnabled(true);
	else
		ui->m_lpSearchButton->setEnabled(false);
}

void cImportIngredientDialog::on_m_lpSearchButton_clicked()
{
	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Import Ingredient");
	lpDialog->setMessage("Searching");
	lpDialog->show();

	m_lpIngredientListModel->removeRows(0, m_lpIngredientListModel->rowCount());

	cPlugin*			lpPlugin	= ui->m_lpSource->currentData().value<cPlugin*>();

	if(!lpPlugin)
	{
		delete lpDialog;
		return;
	}

	cImportInterface*	lpImport	= lpPlugin->importInterface();
	if(!lpImport)
	{
		delete lpDialog;
		return;
	}

	QStringList			strList		= lpImport->search(ui->m_lpSearchString->text());
	for(int z = 0;z < strList.count();z++)
	{
		QStandardItem*	lpNew		= new QStandardItem(strList.at(z));
		m_lpIngredientListModel->appendRow(lpNew);
	}

	delete lpDialog;
}

void cImportIngredientDialog::onIngredientListSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Import Ingredient");
	lpDialog->setMessage("Loading");
	lpDialog->show();

	m_lpIngredientDetailsModel->removeRows(0, m_lpIngredientDetailsModel->rowCount());

	cPlugin*			lpPlugin	= ui->m_lpSource->currentData().value<cPlugin*>();

	if(!lpPlugin)
	{
		delete lpDialog;
		return;
	}

	cImportInterface*	lpImport	= lpPlugin->importInterface();
	if(!lpImport)
	{
		delete lpDialog;
		return;
	}

	int					iIndex		= ui->m_lpIngredientList->currentIndex().row();
	if(iIndex < 0)
	{
		delete lpDialog;
		return;
	}

	if(!lpImport->load(iIndex))
	{
		delete lpDialog;
		return;
	}

	if(!lpImport->load(ui->m_lpIngredientList->currentIndex().row()))
	{
		delete lpDialog;
		return;
	}

	for(int z = 0;z < cIngredient::iIngredientMax;z++)
	{
		if(lpImport->value((cIngredient::iIngredient)z) != -1)
		{
			QStandardItem*	lpParent	= addGroup(lpImport->group((cIngredient::iIngredient)z));

			QStandardItem*	lpName		= new QStandardItem(lpImport->name((cIngredient::iIngredient)z));
			QStandardItem*	lpValue		= new QStandardItem(lpImport->valueStr((cIngredient::iIngredient)z));
			lpValue->setTextAlignment(Qt::AlignRight);
			lpParent->appendRow(QList<QStandardItem*>() << lpName << lpValue);
		}
	}
	ui->m_lpIngredientDetails->resizeColumnToContents(0);
	ui->m_lpIngredientDetails->resizeColumnToContents(1);

	delete lpDialog;
}

QStandardItem* cImportIngredientDialog::addGroup(const QString& group)
{
	QList<QStandardItem*>itemList	= m_lpIngredientDetailsModel->findItems(group);
	for(int z = 0;z < itemList.count();z++)
	{
		if(!itemList.at(z)->parent())
			return(itemList.at(z));
	}
	QStandardItem*	lpItem	= new QStandardItem(group);
	m_lpIngredientDetailsModel->appendRow(lpItem);
	return(lpItem);
}

cIngredient cImportIngredientDialog::toIngredient()
{
	cPlugin*			lpPlugin	= ui->m_lpSource->currentData().value<cPlugin*>();

	if(!lpPlugin)
		return(cIngredient(""));

	cImportInterface*	lpImport	= lpPlugin->importInterface();
	if(!lpImport)
		return(cIngredient(""));

	if(!lpImport->loaded())
		return(cIngredient(""));


	cIngredient	ingredient(lpImport->ingredientName());
	for(int z = 0;z < cIngredient::iIngredientMax;z++)
	{
		if(lpImport->value((cIngredient::iIngredient)z) != -1)
			ingredient.setValue((cIngredient::iIngredient)z, lpImport->value((cIngredient::iIngredient)z));
	}

	return(ingredient);
}
