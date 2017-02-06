#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "cimportinterface.h"
#include "cingredient.h"

#include "cingredientwindow.h"

#include "typedef.h"

#include "coptions.h"

#include "cimportingredientdialog.h"

#include "cmessageanimatedialog.h"

#include <QPluginLoader>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QImage>
#include <QContextMenuEvent>
#include <QThread>
#include <QMdiSubWindow>


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpIngredientsListModel(0),
	m_lpIngredientsListNew(0),
	m_lpIngredientsListImport(0),
	m_lpIngredientsListDelete(0),
	m_lpIngredientsListEdit(0),
	m_lpIngredientsListMenu(0),
	m_lpDB(0),
	m_szLastImportPlugin("")
{
	QThread::msleep(2000);
	init();
}

cMainWindow::~cMainWindow()
{
	if(m_lpIngredientsListNew)
		delete m_lpIngredientsListNew;
	if(m_lpIngredientsListDelete)
		delete m_lpIngredientsListDelete;
	if(m_lpIngredientsListEdit)
		delete m_lpIngredientsListEdit;
	delete ui;
}

void cMainWindow::init()
{
	QSettings	settings;

	if(settings.value("program/version", QVariant(-1.0)).toDouble() == -1.0)
		initDefaultSettings();

	ui->setupUi(this);

	ui->m_lpMDIArea->setViewMode(QMdiArea::TabbedView);
	ui->m_lpMDIArea->setTabsClosable(true);
	ui->m_lpMDIArea->setTabsMovable(true);

//	loadPlugins(QString("%1%2%3").arg(QDir::currentPath()).arg(QDir::separator()).arg("plugins"));
	loadPlugins(QString("%1%2%3").arg(qApp->applicationDirPath()).arg(QDir::separator()).arg("plugins"));

	m_lpIngredientsListModel	= new QStandardItemModel(0, 3);
	QStringList	header;

	ui->m_lpIngredientsList->setModel(m_lpIngredientsListModel);
	header << tr("Ingredient") << tr("Calories") << tr("Carboh.");
	m_lpIngredientsListModel->setHorizontalHeaderLabels(header);
	ui->m_lpIngredientsList->header()->setStretchLastSection(false);
	ui->m_lpIngredientsList->header()->setSectionResizeMode(0, QHeaderView::Stretch);

	connect(ui->m_lpMenu_File_Exit, SIGNAL(triggered(bool)), this, SLOT(menuFileExitTriggered()));
	connect(ui->m_lpMenu_Tools_Options, SIGNAL(triggered(bool)), this, SLOT(menuToolsOptionsTriggered()));

	ui->m_lpIngredientsList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->m_lpIngredientsList, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ingredientsListCustomContextMenu(const QPoint &)));
	m_lpIngredientsListMenu		= new QMenu(ui->m_lpIngredientsList);

	m_lpIngredientsListNew		= new QAction("&New", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListNew);
	connect(m_lpIngredientsListNew, SIGNAL(triggered(bool)), this, SLOT(ingredientsListNewTriggered()));

	m_lpIngredientsListImport	= new QAction("&Import", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListImport);
	connect(m_lpIngredientsListImport, SIGNAL(triggered(bool)), this, SLOT(ingredientsListImportTriggered()));

	m_lpIngredientsListDelete	= new QAction("&Delete", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListDelete);
	connect(m_lpIngredientsListDelete, SIGNAL(triggered(bool)), this, SLOT(ingredientsListDeleteTriggered()));

	m_lpIngredientsListEdit		= new QAction("&Edit", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListEdit);
	connect(m_lpIngredientsListEdit, SIGNAL(triggered(bool)), this, SLOT(ingredientsListEditTriggered()));

	bool	bConnected	= false;

	while(!bConnected)
	{
		if(!m_lpDB)
		{
			if(QMessageBox::critical(this, "Warning", tr("Database can't be opened. Do you want to configure plugins?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
			{
				QTimer::singleShot(0, this, SLOT(menuFileExitTriggered()));
				return;
			}

			menuToolsOptionsTriggered();
		}
		else if(!m_lpDB->dbInterface())
		{
			if(QMessageBox::critical(this, "Warning", tr("Database can't be opened. Do you want to configure plugins?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
			{
				QTimer::singleShot(0, this, SLOT(menuFileExitTriggered()));
				return;
			}

			menuToolsOptionsTriggered();
		}
		else if(!m_lpDB->dbInterface()->connect())
		{
			if(QMessageBox::critical(this, "Warning", tr("Database can't be opened. Do you want to configure plugins?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
			{
				QTimer::singleShot(0, this, SLOT(menuFileExitTriggered()));
				return;
			}

			menuToolsOptionsTriggered();
		}
		else
			bConnected	= true;
	}
	loadIngredients();
}

void cMainWindow::initDefaultSettings()
{
	QSettings	settings;
	QDir		dir;

	settings.setValue("program/version", QVariant(0.1));
	settings.setValue("program/dataDir", QVariant(QString("%1/.kooky").arg(QDir::homePath())));
	settings.setValue("program/pluginDir", QVariant(QString("%1/.kooky/plugins").arg(QDir::homePath())));
	settings.setValue("program/receiptDir", QVariant(QString("%1/.kooky/receipts").arg(QDir::homePath())));
	settings.setValue("program/ingredientDir", QVariant(QString("%1/.kooky/ingredients").arg(QDir::homePath())));
	settings.setValue("program/imageDir", QVariant(QString("%1/.kooky/images").arg(QDir::homePath())));

	dir.mkpath(settings.value("program/dataDir").toString());
	dir.mkpath(settings.value("program/pluginDir").toString());
	dir.mkpath(settings.value("program/receiptDir").toString());
	dir.mkpath(settings.value("program/ingredientDir").toString());
	dir.mkpath(settings.value("program/imageDir").toString());
}

void cMainWindow::loadPlugins(const QString& szPluginDir)
{
	QCoreApplication::addLibraryPath(szPluginDir);
	QDir		pluginDir(szPluginDir);
	QSettings	settings;

#ifdef Q_OS_WIN
	QStringList	szImportList	= pluginDir.entryList(QStringList() << "i*.dll");
	QStringList	szExportList	= pluginDir.entryList(QStringList() << "e*.dll");
	QStringList	szDBList		= pluginDir.entryList(QStringList() << "d*.dll");
#else
	QStringList	szImportList	= pluginDir.entryList(QStringList() << "libi*.so");
	QStringList	szExportList	= pluginDir.entryList(QStringList() << "libe*.so");
	QStringList	szDBList		= pluginDir.entryList(QStringList() << "libd*.so");
#endif

	for(int z = 0;z < szImportList.count();z++)
	{
#ifdef Q_OS_WIN
		QString		szFile	= szImportList.at(z);
#else
		QString		szFile	= szImportList.at(z).mid(3, szImportList.at(z).length()-6);
#endif
		cPlugin*	lpPlugin	= new cPlugin(szFile);
		if(lpPlugin->isValid())
		{
			QAction*	lpAction	= new QAction(this);
			ui->m_lpMenu_Plugins_Import->addAction(lpAction);
			lpAction->setText(lpPlugin->pluginName());
			connect(lpAction, SIGNAL(triggered()), this, SLOT(pluginImportTriggered()));
			lpPlugin->setAction(lpAction);
			m_pluginList.append(lpPlugin);
		}
	}

	for(int z = 0;z < szExportList.count();z++)
	{
#ifdef Q_OS_WIN
		QString		szFile	= szExportList.at(z);
#else
		QString		szFile	= szExportList.at(z).mid(3, szExportList.at(z).length()-6);
#endif
		cPlugin*	lpPlugin	= new cPlugin(szFile);
		if(lpPlugin->isValid())
		{
			QAction*	lpAction	= new QAction(this);
			ui->m_lpMenu_Plugins_Export->addAction(lpAction);
			lpAction->setText(lpPlugin->pluginName());
			connect(lpAction, SIGNAL(triggered()), this, SLOT(pluginExportTriggered()));
			lpPlugin->setAction(lpAction);
			m_pluginList.append(lpPlugin);
		}
	}

	for(int z = 0;z < szDBList.count();z++)
	{
#ifdef Q_OS_WIN
		QString		szFile	= szDBList.at(z);
#else
		QString		szFile	= szDBList.at(z).mid(3, szDBList.at(z).length()-6);
#endif
		cPlugin*	lpPlugin	= new cPlugin(szFile);
		if(lpPlugin->isValid())
		{
			QAction*	lpAction	= new QAction(this);
			ui->m_lpMenu_Plugins_Database->addAction(lpAction);
			lpAction->setText(lpPlugin->pluginName());
			connect(lpAction, SIGNAL(triggered()), this, SLOT(pluginDBTriggered()));
			lpPlugin->setAction(lpAction);
			m_pluginList.append(lpPlugin);
			if(settings.value(QString("plugins/%1/enabled").arg(lpPlugin->pluginName()), QVariant(false)).toBool())
				m_lpDB	= lpPlugin;
		}
	}
}

cPlugin* cMainWindow::plugin(QAction* lpAction)
{
	for(int z = 0;z < m_pluginList.count();z++)
	{
		if(m_pluginList.at(z)->action() == lpAction)
			return(m_pluginList.at(z));
	}
	return(0);
}

QList<cPlugin*> cMainWindow::pluginList()
{
	return(m_pluginList);
}

void cMainWindow::loadIngredients()
{
	m_lpIngredientsListModel->removeRows(0, m_lpIngredientsListModel->rowCount());

	QString			szOldGroup("");
	QStandardItem*	lpGroupItem	= 0;

	if(m_lpDB)
	{
		cDBInterface* lpInterface	= m_lpDB->dbInterface();
		if(lpInterface)
		{
			INGREDIENT_LIST	ingredients	= lpInterface->ingredients();
			for(int z = 0;z < ingredients.count();z++)
			{
				if(ingredients.at(z).szGroup != szOldGroup)
				{
					szOldGroup	= ingredients.at(z).szGroup;
					lpGroupItem	= new QStandardItem(szOldGroup);
					m_lpIngredientsListModel->appendRow(lpGroupItem);
				}
				QStandardItem*	lpNew		= new QStandardItem(ingredients.at(z).szIngredient);
				lpNew->setData(ingredients.at(z).iIngredient);
				QStandardItem*	lpCalories	= new QStandardItem(QString("%1 kCal").arg(ingredients.at(z).dCalories));
				QStandardItem*	lpCarbos	= new QStandardItem(QString("%1 g").arg(ingredients.at(z).dCarbohydrates, 0, 'f', 1));
				lpCalories->setTextAlignment(Qt::AlignRight);
				lpCarbos->setTextAlignment(Qt::AlignRight);
				lpGroupItem->appendRow(QList<QStandardItem *>() << lpNew << lpCalories << lpCarbos);
			}
		}
	}

	ui->m_lpIngredientsList->expandAll();

	ui->m_lpIngredientsList->resizeColumnToContents(0);
	ui->m_lpIngredientsList->resizeColumnToContents(1);
	ui->m_lpIngredientsList->resizeColumnToContents(2);
}

void cMainWindow::pluginImportTriggered()
{
	QAction*	lpAction	= qobject_cast<QAction *>(sender());
	if(lpAction)
	{
		cPlugin*	lpPlugin	= plugin(lpAction);
		if(lpPlugin)
		{
			cImportInterface*	lpImportInterface	= lpPlugin->importInterface();
			QString				str					= lpImportInterface->pluginName();
			if(lpImportInterface)
			{
				QStringList	list	= lpImportInterface->search("kuhmilch", "bla");

				if(lpImportInterface->load(0))
				{
					qreal		v;
					QString		str;

					str	= lpImportInterface->group(cIngredient::iIngredientCarbohydrates);
					str	= lpImportInterface->name(cIngredient::iIngredientCarbohydrates);
					v	= lpImportInterface->value(cIngredient::iIngredientCarbohydrates);
					v	= lpImportInterface->value(cIngredient::iIngredientBreadUnits);
					v	= lpImportInterface->value(cIngredient::iIngredientWater);
					v	= lpImportInterface->value(cIngredient::iIngredientCholesterol);
					v	= lpImportInterface->value(cIngredient::iIngredientCopper);
					v = 0;
				}
			}
		}
	}

}

void cMainWindow::pluginExportTriggered()
{
}

void cMainWindow::pluginDBTriggered()
{
	QAction*	lpAction	= qobject_cast<QAction *>(sender());
	if(lpAction)
	{
		cPlugin*	lpPlugin	= plugin(lpAction);
		if(lpPlugin)
		{
			cDBInterface*		lpDBInterface	= lpPlugin->dbInterface();
			if(lpDBInterface->config())
				loadIngredients();
		}
	}
}

void cMainWindow::menuFileExitTriggered()
{
	qApp->exit();
}

void cMainWindow::menuToolsOptionsTriggered()
{
	cOptions	options(this);
	if(options.exec() == QDialog::Rejected)
		return;

	QSettings	settings;

	for(int z = 0;z < m_pluginList.count();z++)
	{
		cPlugin*	lpPlugin	= m_pluginList.at(z);
		if(lpPlugin->capability() == cPlugin::PluginCapDB)
		{
			if(settings.value(QString("plugins/%1/enabled").arg(lpPlugin->pluginName()), QVariant(false)).toBool())
			{
				if(lpPlugin != m_lpDB)
				{
					m_lpDB	= lpPlugin;
					m_lpDB->dbInterface()->connect();
					loadIngredients();
					break;
				}
			}
		}
	}
}

void cMainWindow::ingredientsListCustomContextMenu(const QPoint& point)
{
	QModelIndex	index	= ui->m_lpIngredientsList->indexAt(point);
	if(index.isValid())
	{
		m_lpIngredientsListNew->setEnabled(true);
		m_lpIngredientsListDelete->setEnabled(true);
		m_lpIngredientsListEdit->setEnabled(true);
	}
	else
	{
		m_lpIngredientsListNew->setEnabled(true);
		m_lpIngredientsListDelete->setEnabled(false);
		m_lpIngredientsListEdit->setEnabled(false);
	}
	m_lpIngredientsListMenu->exec(ui->m_lpIngredientsList->mapToGlobal(point));
}

void cMainWindow::ingredientsListNewTriggered()
{
}

void cMainWindow::ingredientsListImportTriggered()
{
	cImportIngredientDialog	importIngredientDialog(this);
	importIngredientDialog.setPluginList(m_pluginList, m_szLastImportPlugin);
	cDBInterface* lpInterface	= m_lpDB->dbInterface();
	if(lpInterface)
		importIngredientDialog.setIngredientGroupList(lpInterface->groups());

	if(importIngredientDialog.exec() == QDialog::Rejected)
		return;

	m_szLastImportPlugin	= importIngredientDialog.pluginSelected();

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Import Ingredient");
	lpDialog->setMessage("Saving");
	lpDialog->show();

	cIngredient	ingredient	= importIngredientDialog.toIngredient();
	ingredient.save(m_lpDB);
	loadIngredients();

	delete lpDialog;
}

void cMainWindow::ingredientsListDeleteTriggered()
{
}

void cMainWindow::ingredientsListEditTriggered()
{
	QModelIndex	index	= ui->m_lpIngredientsList->currentIndex();
	if(index.isValid())
	{
		QStandardItem*	lpItem		= m_lpIngredientsListModel->itemFromIndex(index);
		if(!lpItem)
			return;

		QStandardItem*	lpParent	= lpItem->parent();
		if(!lpParent)
			return;

		cIngredientWindow*	lpIngredientWindow	= new cIngredientWindow(this);
		QMdiSubWindow*		lpSubWindow			= ui->m_lpMDIArea->addSubWindow(lpIngredientWindow);
		lpSubWindow->setAttribute(Qt::WA_DeleteOnClose);
		lpIngredientWindow->setIngredient(lpItem->data().toInt(), m_lpDB);
		lpIngredientWindow->show();
	}
}
