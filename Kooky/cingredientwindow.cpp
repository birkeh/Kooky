#include "cingredientwindow.h"
#include "ui_cingredientwindow.h"

#include "cingredientvalue.h"

#include <QStandardItem>


cIngredientWindow::cIngredientWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cIngredientWindow)
{
	ui->setupUi(this);
	ui->m_lpIngredientValues->setMinimumWidth(1);

	m_lpIngredientValuesModel	= new QStandardItemModel(0, 2);
	ui->m_lpIngredientValues->setModel(m_lpIngredientValuesModel);

	connect(ui->m_lpIngredientValues, &QTreeView::doubleClicked, this, &cIngredientWindow::ingredientEdit);
}

cIngredientWindow::~cIngredientWindow()
{
	delete ui;
}

void cIngredientWindow::setIngredient(qint32 iIngredient, cPlugin* lpPlugin)
{
	m_iIngredient		= iIngredient;
	m_lpDBPlugin		= lpPlugin;
	if(!m_ingredientSaved.load(m_iIngredient, m_lpDBPlugin))
		return;

	m_ingredient		= m_ingredientSaved;

	setWindowTitle(QString("<Ingredient> %1").arg(m_ingredientSaved.ingredientName()));
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
}

qint32 cIngredientWindow::ingredientID(void)
{
	return(m_iIngredient);
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

	bool	bChanged	= isChanged();	// may not be later as it seems to be buggy ...

	QStandardItem*				lpParent		= lpCurrentItem->parent();
	QStandardItem*				lpValue			= lpParent->child(modelIndex.row(), 1);
	lpValue->setText(m_ingredient.valueFormatted(iIngredient));

	if(bChanged)
		setWindowTitle(QString("<Ingredient> %1*").arg(m_ingredientSaved.ingredientName()));
	else
		setWindowTitle(QString("<Ingredient> %1").arg(m_ingredientSaved.ingredientName()));
}

bool cIngredientWindow::isChanged()
{
	if(m_ingredient != m_ingredientSaved)
		return(true);
	return(false);
}
