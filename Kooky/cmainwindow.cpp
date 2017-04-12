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
	m_szLastImportPlugin(""),
	m_lpWindowMenuCloseAct(0),
	m_lpWindowMenuCloseAllAct(0),
	m_lpWindowMenuTileAct(0),
	m_lpWindowMenuCascadeAct(0),
	m_lpWindowMenuNextAct(0),
	m_lpWindowMenuPreviousAct(0),
	m_lpWindowMenuSeparatorAct(0)
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

//	ui->m_lpMDIArea->setViewMode(QMdiArea::TabbedView);
//	ui->m_lpMDIArea->setTabsClosable(true);
//	ui->m_lpMDIArea->setTabsMovable(true);

//	loadPlugins(QString("%1%2%3").arg(QDir::currentPath()).arg(QDir::separator()).arg("plugins"));
	loadPlugins(QString("%1%2%3").arg(qApp->applicationDirPath()).arg(QDir::separator()).arg("plugins"));

	m_lpIngredientsListModel	= new QStandardItemModel(0, 3);
	QStringList	header;

	ui->m_lpIngredientsList->setModel(m_lpIngredientsListModel);
	header << tr("Ingredient") << tr("Calories") << tr("Carboh.");
	m_lpIngredientsListModel->setHorizontalHeaderLabels(header);
	ui->m_lpIngredientsList->header()->setStretchLastSection(false);
	ui->m_lpIngredientsList->header()->setSectionResizeMode(0, QHeaderView::Stretch);

	connect(ui->m_lpMenu_File_Exit, &QAction::triggered, this, &cMainWindow::menuFileExitTriggered);
	connect(ui->m_lpMenu_Tools_Options, &QAction::triggered, this, &cMainWindow::menuToolsOptionsTriggered);

	ui->m_lpIngredientsList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->m_lpIngredientsList, &QTreeView::customContextMenuRequested, this, &cMainWindow::ingredientsListCustomContextMenu);
	m_lpIngredientsListMenu		= new QMenu(ui->m_lpIngredientsList);

	m_lpIngredientsListNew		= new QAction("&New", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListNew);
	connect(m_lpIngredientsListNew, &QAction::triggered, this, &cMainWindow::ingredientsListNewTriggered);

	m_lpIngredientsListImport	= new QAction("&Import", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListImport);
	connect(m_lpIngredientsListImport, &QAction::triggered, this, &cMainWindow::ingredientsListImportTriggered);

	m_lpIngredientsListDelete	= new QAction("&Delete", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListDelete);
	connect(m_lpIngredientsListDelete, &QAction::triggered, this, &cMainWindow::ingredientsListDeleteTriggered);

	m_lpIngredientsListEdit		= new QAction("&Edit", m_lpIngredientsListMenu);
	m_lpIngredientsListMenu->addAction(m_lpIngredientsListEdit);
	connect(m_lpIngredientsListEdit, &QAction::triggered, this, &cMainWindow::ingredientsListEditTriggered);

	connect(ui->m_lpIngredientsList, &QTreeView::doubleClicked, this, &cMainWindow::ingredientsListDoubleClicked);

	connect(ui->m_lpMDIArea, &cMdiArea::subWindowActivated, this, &cMainWindow::updateMenus);

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

	m_lpWindowMenuCloseAct = new QAction(tr("Cl&ose"), this);
	m_lpWindowMenuCloseAct->setStatusTip(tr("Close the active window"));
	connect(m_lpWindowMenuCloseAct, &QAction::triggered, ui->m_lpMDIArea, &QMdiArea::closeActiveSubWindow);

	m_lpWindowMenuCloseAllAct = new QAction(tr("Close &All"), this);
	m_lpWindowMenuCloseAllAct->setStatusTip(tr("Close all the windows"));
	connect(m_lpWindowMenuCloseAllAct, &QAction::triggered, ui->m_lpMDIArea, &QMdiArea::closeAllSubWindows);

	m_lpWindowMenuTileAct = new QAction(tr("&Tile"), this);
	m_lpWindowMenuTileAct->setStatusTip(tr("Tile the windows"));
	connect(m_lpWindowMenuTileAct, &QAction::triggered, ui->m_lpMDIArea, &QMdiArea::tileSubWindows);

	m_lpWindowMenuCascadeAct = new QAction(tr("&Cascade"), this);
	m_lpWindowMenuCascadeAct->setStatusTip(tr("Cascade the windows"));
	connect(m_lpWindowMenuCascadeAct, &QAction::triggered, ui->m_lpMDIArea, &QMdiArea::cascadeSubWindows);

	m_lpWindowMenuNextAct = new QAction(tr("Ne&xt"), this);
	m_lpWindowMenuNextAct->setShortcuts(QKeySequence::NextChild);
	m_lpWindowMenuNextAct->setStatusTip(tr("Move the focus to the next window"));
	connect(m_lpWindowMenuNextAct, &QAction::triggered, ui->m_lpMDIArea, &QMdiArea::activateNextSubWindow);

	m_lpWindowMenuPreviousAct = new QAction(tr("Pre&vious"), this);
	m_lpWindowMenuPreviousAct->setShortcuts(QKeySequence::PreviousChild);
	m_lpWindowMenuPreviousAct->setStatusTip(tr("Move the focus to the previous window"));
	connect(m_lpWindowMenuPreviousAct, &QAction::triggered, ui->m_lpMDIArea, &QMdiArea::activatePreviousSubWindow);

	m_lpWindowMenuSeparatorAct = new QAction(this);
	m_lpWindowMenuSeparatorAct->setSeparator(true);

	connect(ui->m_lpMenu_Window, &QMenu::aboutToShow, this, &cMainWindow::updateWindowMenu);

	updateMenus();
	updateWindowMenu();
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
			connect(lpAction, &QAction::triggered, this, &cMainWindow::pluginImportTriggered);
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
			connect(lpAction, &QAction::triggered, this, &cMainWindow::pluginExportTriggered);
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
			connect(lpAction, &QAction::triggered, this, &cMainWindow::pluginDBTriggered);
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

	if(m_lpDB)
	{
		cDBInterface* lpInterface	= m_lpDB->dbInterface();
		if(lpInterface)
		{
			QStringList	groups	= lpInterface->groups();

			for(int z = 0;z < groups.count();z++)
			{
				QStandardItem*	lpGroup		= new QStandardItem(groups.at(z));

				m_lpIngredientsListModel->appendRow(lpGroup);
				lpGroup->setBackground(QBrush(QColor(191, 191, 191)));
				QFont	font	= lpGroup->font();
				font.setItalic(true);
				font.setBold(true);
				lpGroup->setFont(font);
				ui->m_lpIngredientsList->setFirstColumnSpanned(z, ui->m_lpIngredientsList->rootIndex(), true);
			}

			INGREDIENT_LIST			ingredients	= lpInterface->ingredients();
			QList<QStandardItem*>	lpGroupItem;

			for(int z = 0;z < ingredients.count();z++)
			{
				lpGroupItem	= m_lpIngredientsListModel->findItems(ingredients.at(z).szGroup);
				if(lpGroupItem.count())
				{
					QStandardItem*	lpNew		= new QStandardItem(ingredients.at(z).szIngredient);
					QStandardItem*	lpCalories	= new QStandardItem(QString("%1 kCal").arg(ingredients.at(z).dCalories));
					QStandardItem*	lpCarbos	= new QStandardItem(QString("%1 g").arg(ingredients.at(z).dCarbohydrates, 0, 'f', 1));
					lpNew->setData(ingredients.at(z).iIngredient);
					lpCalories->setData(ingredients.at(z).iIngredient);
					lpCarbos->setData(ingredients.at(z).iIngredient);
					lpCalories->setTextAlignment(Qt::AlignRight);
					lpCarbos->setTextAlignment(Qt::AlignRight);
					lpGroupItem.at(0)->appendRow(QList<QStandardItem *>() << lpNew << lpCalories << lpCarbos);
				}
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
/*
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
*/
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
/*
	QModelIndex	index	= ui->m_lpIngredientsList->currentIndex();
	if(index.isValid())
	{
		QStandardItem*	lpItem		= m_lpIngredientsListModel->itemFromIndex(index);
		if(!lpItem)
			return;

		QStandardItem*	lpParent	= lpItem->parent();
		if(!lpParent)
			return;

		QList<QMdiSubWindow*>	windowsList	= ui->m_lpMDIArea->subWindowList();
		for(int z = 0;z < windowsList.count();z++)
		{
			cIngredientWindow*	lpWidget	= (cIngredientWindow*)windowsList.at(z)->widget();
			if(lpWidget->ingredientID() == lpItem->data().toInt())
			{
				ui->m_lpMDIArea->setActiveSubWindow(windowsList.at(z));
				return;
			}
		}

		cIngredientWindow*	lpIngredientWindow	= new cIngredientWindow(this);
		lpIngredientWindow->setIngredient(ingredientItemFromID(lpItem->data().toInt()), m_lpDB);
		QMdiSubWindow*		lpSubWindow			= ui->m_lpMDIArea->addSubWindow(lpIngredientWindow);
		lpSubWindow->setAttribute(Qt::WA_DeleteOnClose);
		lpIngredientWindow->show();
	}
*/
}

void cMainWindow::ingredientsListImportTriggered()
{
	cImportIngredientDialog	importIngredientDialog(this);
	importIngredientDialog.setPluginList(m_pluginList, m_szLastImportPlugin);
	cDBInterface* lpInterface	= m_lpDB->dbInterface();
	if(lpInterface)
		importIngredientDialog.setIngredientGroupList(lpInterface->groups());

	QModelIndex	index	= ui->m_lpIngredientsList->currentIndex();
	if(index.isValid())
	{
		QString			szGroup;
		QStandardItem*	lpItem		= m_lpIngredientsListModel->itemFromIndex(index);
		if(lpItem)
		{
			QStandardItem*	lpParent	= lpItem->parent();
			if(lpParent)
				szGroup	= lpParent->text();
			else
				szGroup	= lpItem->text();
		}
		if(!szGroup.isEmpty())
			importIngredientDialog.setIngredientGroup(szGroup);
	}

	if(importIngredientDialog.exec() == QDialog::Rejected)
		return;

	m_szLastImportPlugin	= importIngredientDialog.pluginSelected();

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Import Ingredient");
	lpDialog->setMessage("Saving");
	lpDialog->show();

	cIngredient	ingredient	= importIngredientDialog.toIngredient();
	ingredient.save(m_lpDB);

	QList<QStandardItem*>lpGroupItem	= m_lpIngredientsListModel->findItems(ingredient.ingredientGroup());
	if(lpGroupItem.count())
	{
		QStandardItem*	lpNew		= new QStandardItem(ingredient.ingredientName());
		QStandardItem*	lpCalories	= new QStandardItem(QString("%1 kCal").arg(ingredient.value(cIngredient::iIngredientCalories)));
		QStandardItem*	lpCarbos	= new QStandardItem(QString("%1 g").arg(ingredient.value(cIngredient::iIngredientCarbohydrates), 0, 'f', 1));
		lpNew->setData(ingredient.ingredientID());
		lpCalories->setData(ingredient.ingredientID());
		lpCarbos->setData(ingredient.ingredientID());
		lpCalories->setTextAlignment(Qt::AlignRight);
		lpCarbos->setTextAlignment(Qt::AlignRight);
		lpGroupItem.at(0)->appendRow(QList<QStandardItem *>() << lpNew << lpCalories << lpCarbos);
	}

	delete lpDialog;
}

void cMainWindow::ingredientsListDeleteTriggered()
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

		lpItem	= ingredientItemFromID(lpItem->data().toInt());

		if(QMessageBox::question(this, "Delete", QString("You are about to delete \"%1\".\nAre you sure?").arg(lpItem->text()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
			return;

		if(!m_lpDB->dbInterface()->deleteIngredient(lpItem->data().toInt()))
		{
			QMessageBox::critical(this, "Error", QString("Error deleting \"%1\"!").arg(lpItem->text()));
			return;
		}

		m_lpIngredientsListModel->removeRow(index.row());

		QList<QMdiSubWindow*>	windowsList	= ui->m_lpMDIArea->subWindowList();
		for(int z = 0;z < windowsList.count();z++)
		{
			cIngredientWindow*	lpWidget	= (cIngredientWindow*)windowsList.at(z)->widget();
			if(lpWidget->ingredientID() == lpItem->data().toInt())
			{
				lpWidget->forceClose();
				return;
			}
		}
	}
}

QStandardItem* cMainWindow::ingredientItemFromID(qint32 id)
{
	for(int z = 0;z < m_lpIngredientsListModel->rowCount();z++)
	{
		QStandardItem*	lpItem	= m_lpIngredientsListModel->item(z);
		if(lpItem->data().toInt() == id)
			return(lpItem);

		if(lpItem->hasChildren())
		{
			for(int y = 0;y < lpItem->rowCount();y++)
			{
				QStandardItem*	lpItem1	= lpItem->child(y);
				if(lpItem1->data().toInt() == id)
					return(lpItem1);
			}
		}
	}
	return(0);
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

		QList<QMdiSubWindow*>	windowsList	= ui->m_lpMDIArea->subWindowList();
		for(int z = 0;z < windowsList.count();z++)
		{
			cIngredientWindow*	lpWidget	= (cIngredientWindow*)windowsList.at(z)->widget();
			if(lpWidget->ingredientID() == lpItem->data().toInt())
			{
				ui->m_lpMDIArea->setActiveSubWindow(windowsList.at(z));
				return;
			}
		}

		cIngredientWindow*	lpIngredientWindow	= new cIngredientWindow(this);
		lpIngredientWindow->setIngredient(ingredientItemFromID(lpItem->data().toInt()), m_lpDB);
		QMdiSubWindow*		lpSubWindow			= ui->m_lpMDIArea->addSubWindow(lpIngredientWindow);
		lpSubWindow->setAttribute(Qt::WA_DeleteOnClose);
		lpIngredientWindow->showMaximized();
	}
}

QMdiSubWindow* cMainWindow::activeMdiChild() const
{
	if (QMdiSubWindow*	activeSubWindow = ui->m_lpMDIArea->activeSubWindow())
		return(activeSubWindow);
	return(0);
}

void cMainWindow::ingredientsListDoubleClicked(QModelIndex /*modelIndex*/)
{
	this->ingredientsListEditTriggered();
}

void cMainWindow::updateMenus()
{
	QMdiSubWindow*	lpActiveChild	= activeMdiChild();
	bool			hasMdiChild		= (lpActiveChild != 0);

//	saveAct->setEnabled(hasMdiChild);
//	saveAsAct->setEnabled(hasMdiChild);
//#ifndef QT_NO_CLIPBOARD
//	pasteAct->setEnabled(hasMdiChild);
//#endif
	m_lpWindowMenuCloseAct->setEnabled(hasMdiChild);
	m_lpWindowMenuCloseAllAct->setEnabled(hasMdiChild);
	m_lpWindowMenuTileAct->setEnabled(hasMdiChild);
	m_lpWindowMenuCascadeAct->setEnabled(hasMdiChild);
	m_lpWindowMenuNextAct->setEnabled(hasMdiChild);
	m_lpWindowMenuPreviousAct->setEnabled(hasMdiChild);
	m_lpWindowMenuSeparatorAct->setVisible(hasMdiChild);

//#ifndef QT_NO_CLIPBOARD
//	bool hasSelection = (activeMdiChild() &&
//						 activeMdiChild()->textCursor().hasSelection());
//	cutAct->setEnabled(hasSelection);
//	copyAct->setEnabled(hasSelection);
//#endif
}


class ActiveMdiSubWindowFunctor
{
public:
	explicit ActiveMdiSubWindowFunctor(QMdiArea *mdiArea, QMdiSubWindow *activeWindow) : m_mdiArea(mdiArea), m_activeWindow(activeWindow) {}
	void operator()() const { m_mdiArea->setActiveSubWindow(m_activeWindow); }

private:
	QMdiArea*		m_mdiArea;
	QMdiSubWindow*	m_activeWindow;
};

void cMainWindow::updateWindowMenu()
{
	ui->m_lpMenu_Window->clear();

	ui->m_lpMenu_Window->addAction(m_lpWindowMenuCloseAct);
	ui->m_lpMenu_Window->addAction(m_lpWindowMenuCloseAllAct);
	ui->m_lpMenu_Window->addSeparator();
	ui->m_lpMenu_Window->addAction(m_lpWindowMenuTileAct);
	ui->m_lpMenu_Window->addAction(m_lpWindowMenuCascadeAct);
	ui->m_lpMenu_Window->addSeparator();
	ui->m_lpMenu_Window->addAction(m_lpWindowMenuNextAct);
	ui->m_lpMenu_Window->addAction(m_lpWindowMenuPreviousAct);
	ui->m_lpMenu_Window->addAction(m_lpWindowMenuSeparatorAct);

	QList<QMdiSubWindow*>	windowsList	= ui->m_lpMDIArea->subWindowList();
	m_lpWindowMenuSeparatorAct->setVisible(!windowsList.isEmpty());

	QMdiSubWindow*			lpActiveChild	= activeMdiChild();

	for(int i = 0; i < windowsList.size(); i++)
	{
		QMdiSubWindow*	lpMdiSubWindow	= windowsList.at(i);

		QString			str;

		if(i < 9)
			str = tr("&%1 %2").arg(i + 1).arg(lpMdiSubWindow->windowTitle());
		else
			str	= tr("%1 %2").arg(i + 1).arg(lpMdiSubWindow->windowTitle());

		QAction*	lpAction	= ui->m_lpMenu_Window->addAction(str, lpMdiSubWindow, ActiveMdiSubWindowFunctor(ui->m_lpMDIArea, lpMdiSubWindow));
		lpAction->setCheckable(true);
		lpAction->setChecked(lpMdiSubWindow == lpActiveChild);
	}
}
