#include "cingredientwindow.h"
#include "ui_cingredientwindow.h"

#include "cingredient.h"


cIngredientWindow::cIngredientWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cIngredientWindow)
{
	ui->setupUi(this);
}

cIngredientWindow::~cIngredientWindow()
{
	delete ui;
}

void cIngredientWindow::setIngredient(qint32 iIngredient, cPlugin* lpPlugin)
{
	m_iIngredient	= iIngredient;
	m_lpDBPlugin	= lpPlugin;
	cIngredient	ingredient;
	if(!ingredient.load(m_iIngredient, m_lpDBPlugin))
		return;

	setWindowTitle(ingredient.ingredientName());
}
