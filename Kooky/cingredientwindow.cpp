#include "cingredientwindow.h"
#include "ui_cingredientwindow.h"

#include <QStandardItem>


cIngredientWindow::cIngredientWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cIngredientWindow)
{
	ui->setupUi(this);

	m_lpIngredientValuesModel	= new QStandardItemModel(0, 2);
	ui->m_lpIngredientValues->setModel(m_lpIngredientValuesModel);
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

	setWindowTitle(m_ingredientSaved.ingredientName());
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
	}
	ui->m_lpIngredientValues->expandAll();
	ui->m_lpIngredientValues->resizeColumnToContents(0);
}
