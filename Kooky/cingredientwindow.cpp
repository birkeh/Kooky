#include "cingredientwindow.h"
#include "ui_cingredientwindow.h"

#include "cingredientvalue.h"

#include <QStandardItem>
#include <QMessageBox>
#include <QMdiSubWindow>


cIngredientWindow::cIngredientWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cIngredientWindow),
	m_bIsInitialized(false)
{
	ui->setupUi(this);
	ui->m_lpIngredientValues->setMinimumWidth(1);

	m_lpIngredientValuesModel	= new QStandardItemModel(0, 2);
	ui->m_lpIngredientValues->setModel(m_lpIngredientValuesModel);

	ui->m_lpSave->setEnabled(false);
	ui->m_lpRevert->setEnabled(false);

	connect(ui->m_lpIngredientValues, &QTreeView::doubleClicked, this, &cIngredientWindow::ingredientEdit);
	connect(ui->m_lpIngredientName, &QLineEdit::textChanged, this, &cIngredientWindow::nameChanged);
	connect(ui->m_lpIngredientGroup, &QComboBox::currentTextChanged, this, &cIngredientWindow::groupChanged);

	connect(ui->m_lpSave, &QPushButton::clicked, this, &cIngredientWindow::saveClicked);
	connect(ui->m_lpRevert, &QPushButton::clicked, this, &cIngredientWindow::revertClicked);
	connect(ui->m_lpClose, &QPushButton::clicked, this, &cIngredientWindow::closeClicked);
}

cIngredientWindow::~cIngredientWindow()
{
	delete ui;
}

void cIngredientWindow::setIngredient(QStandardItem *lpItem, cPlugin* lpPlugin)
{
	if(lpPlugin)
	{
		m_lpItem			= lpItem;
		m_iIngredient		= lpItem->data().toInt();
		m_lpDBPlugin		= lpPlugin;
		if(!m_ingredientSaved.load(m_iIngredient, m_lpDBPlugin))
			return;
	}

	m_lpIngredientValuesModel->clear();
	m_lpIngredientValuesModel->setColumnCount(2);

	m_ingredient		= m_ingredientSaved;

	ui->m_lpIngredientName->setText(m_ingredientSaved.ingredientName());

	QStringList	groups	= m_ingredientSaved.groups();
	ui->m_lpIngredientGroup->addItems(m_lpDBPlugin->dbInterface()->groups());
	ui->m_lpIngredientGroup->setCurrentText(m_ingredientSaved.ingredientGroup());

	QStandardItem*	lpRoot[7];

	for(int z = 0;z < 7;z++)
	{
		lpRoot[z]	= new QStandardItem(groups.at(z));
		m_lpIngredientValuesModel->appendRow(lpRoot[z]);
	}

	for(int z = 0;z < cIngredient::iIngredientMax;z++)
	{
		qint32			groupID		= groups.indexOf(m_ingredientSaved.group((cIngredient::iIngredient)z));
		QStandardItem*	lpNew		= new QStandardItem(m_ingredientSaved.name((cIngredient::iIngredient)z));
		QStandardItem*	lpValue		= new QStandardItem(m_ingredientSaved.valueFormatted((cIngredient::iIngredient)z));
		lpValue->setTextAlignment(Qt::AlignRight);
		lpRoot[groupID]->appendRow(QList<QStandardItem *>() << lpNew << lpValue);
		lpNew->setData(QVariant(z));
		lpValue->setData(QVariant(z));
	}
	ui->m_lpIngredientValues->expandAll();
	ui->m_lpIngredientValues->resizeColumnToContents(0);
	ui->m_lpIngredientValues->resizeColumnToContents(1);

	setWindowTitle(QString("<Ingredient> %1").arg(m_ingredientSaved.ingredientName()));
	m_lpItem->setText(QString("%1").arg(m_ingredientSaved.ingredientName()));
	ui->m_lpSave->setEnabled(false);
	ui->m_lpRevert->setEnabled(false);

	m_bIsInitialized	= true;
}

qint32 cIngredientWindow::ingredientID(void)
{
	return(m_iIngredient);
}

void cIngredientWindow::setIngredientGroup(const QString& szIngredientGroup)
{
	ui->m_lpIngredientGroup->setCurrentText(szIngredientGroup);
}

void cIngredientWindow::nameChanged(const QString& text)
{
	if(!m_bIsInitialized)
		return;

	m_ingredient.setIngredientName(text);
	updateTitle();
}

void cIngredientWindow::groupChanged(const QString & text)
{
	if(!m_bIsInitialized)
		return;

	m_ingredient.setIngredientGroup(text);
	updateTitle();
}

void cIngredientWindow::ingredientEdit(const QModelIndex &modelIndex)
{
	QStandardItem*				lpCurrentItem	= m_lpIngredientValuesModel->itemFromIndex(modelIndex);
	if(!lpCurrentItem->parent())
		return;

	cIngredient::iIngredient	iIngredient		= (cIngredient::iIngredient)lpCurrentItem->data().toInt();
	cIngredient::UNIT			unit			= m_ingredient.unit(iIngredient);
	QString						szIngredient	= QString("%1/%2").arg(cIngredient::group(iIngredient)).arg(cIngredient::name(iIngredient));
	qreal						value			= m_ingredient.value(iIngredient);
	cIngredientValue			ingredientValue(this);
	ingredientValue.setValues(szIngredient, value, unit);

	if(ingredientValue.exec() == QDialog::Rejected)
		return;

	value	= ingredientValue.value();
	m_ingredient.setValue(iIngredient, value);

	//bool	bChanged	= isChanged();	// may not be later as it seems to be buggy ...

	QStandardItem*				lpParent		= lpCurrentItem->parent();
	QStandardItem*				lpValue			= lpParent->child(modelIndex.row(), 1);
	lpValue->setText(m_ingredient.valueFormatted(iIngredient));

	updateTitle();
}

bool cIngredientWindow::isChanged()
{
	if(!m_bIsInitialized)
		return(false);

	if(m_ingredient != m_ingredientSaved)
		return(true);
	return(false);
}

void cIngredientWindow::forceClose()
{
	m_ingredient	= m_ingredientSaved;
	closeClicked();
}

bool cIngredientWindow::save()
{
	if(m_ingredient.ingredientName().isEmpty())
	{
		QMessageBox::critical(this, "Error", "Ingredient name is empty.");
		return(false);
	}

	if(m_ingredient.ingredientGroup().isEmpty())
	{
		QMessageBox::critical(this, "Error", "Ingredient group is empty.");
		return(false);
	}

	m_ingredient.save(m_lpDBPlugin);
	m_ingredientSaved	= m_ingredient;
	return(true);
}

void cIngredientWindow::saveClicked()
{
	if(!save())
		return;

	updateTitle();
}

void cIngredientWindow::revertClicked()
{
	setIngredient();

	updateTitle();
}

void cIngredientWindow::closeClicked()
{
	if(this->parent())
	{
		QMdiSubWindow*	mdiSubWindow	= (QMdiSubWindow*)this->parent();
		mdiSubWindow->close();
	}
}

void cIngredientWindow::closeEvent(QCloseEvent *event)
{
	if(isChanged())
	{
		int	ret	= QMessageBox::question(this, "Changed", tr("Ingredient has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		switch(ret)
		{
		case QMessageBox::Yes:
			m_ingredient.save(m_lpDBPlugin);
			m_ingredient	= m_ingredientSaved;
			updateTitle();
			event->accept();
			break;
		case QMessageBox::No:
			m_ingredient	= m_ingredientSaved;
			updateTitle();
			event->accept();
			break;
		default:
			event->ignore();
			break;
		}
	}
	else
		event->accept();
}

void cIngredientWindow::updateTitle()
{
	if(!m_bIsInitialized)
		return;

	if(isChanged())
	{
		setWindowTitle(QString("<Ingredient> %1*").arg(m_ingredientSaved.ingredientName()));
		m_lpItem->setText(QString("%1*").arg(m_ingredientSaved.ingredientName()));
		checkGroupChanged();
		ui->m_lpSave->setEnabled(true);
		ui->m_lpRevert->setEnabled(true);
	}
	else
	{
		setWindowTitle(QString("<Ingredient> %1").arg(m_ingredientSaved.ingredientName()));
		m_lpItem->setText(QString("%1").arg(m_ingredientSaved.ingredientName()));
		checkGroupChanged();
		ui->m_lpSave->setEnabled(false);
		ui->m_lpRevert->setEnabled(false);
	}
}

void cIngredientWindow::checkGroupChanged()
{
	if(!m_bIsInitialized)
		return;

	if(m_ingredient.ingredientGroup() == m_ingredientSaved.ingredientGroup())
		return;

	QString					szGroup		= m_ingredient.ingredientGroup();
	QStandardItem*			lpOldGroup	= m_lpItem->parent();
	QStandardItemModel*		lpModel		= m_lpItem->model();
	QList<QStandardItem*>	lpItems		= lpOldGroup->takeRow(lpModel->indexFromItem(m_lpItem).row());

	for(int z = 0;z < lpModel->rowCount();z++)
	{
		QStandardItem*	lpGroup	= lpModel->item(z, 0);
		if(lpGroup->text() == m_ingredient.ingredientGroup())
		{
			lpGroup->insertRow(0, lpItems);
			break;
		}
	}
}
