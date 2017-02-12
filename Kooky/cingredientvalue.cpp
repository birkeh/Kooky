#include "cingredientvalue.h"
#include "ui_cingredientvalue.h"


cIngredientValue::cIngredientValue(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cIngredientValue)
{
	ui->setupUi(this);
}

cIngredientValue::~cIngredientValue()
{
	delete ui;
}

void cIngredientValue::setValues(const QString& szName, qreal value, cIngredient::UNIT unit)
{
	ui->m_lpIngredient->setText(szName);

	switch(unit)
	{
	case cIngredient::UNIT_Calories:
		ui->m_lpIngredientUnit->addItem("kCal", QVariant((qreal)1));
		ui->m_lpIngredientUnit->setCurrentIndex(0);
		ui->m_lpIngredientValue->setValue(value);
		break;
	case cIngredient::UNIT_Fluid:
		ui->m_lpIngredientUnit->addItem("l", QVariant((qreal)1));
		ui->m_lpIngredientUnit->setCurrentIndex(0);
		ui->m_lpIngredientValue->setValue(value);
		break;
	case cIngredient::UNIT_Joule:
		ui->m_lpIngredientUnit->addItem("kJoule", QVariant((qreal)1));
		ui->m_lpIngredientUnit->setCurrentIndex(0);
		ui->m_lpIngredientValue->setValue(value);
		break;
	case cIngredient::UNIT_None:
		ui->m_lpIngredientValue->setValue(value);
		ui->m_lpIngredientUnit->setEnabled(false);
		break;
	case cIngredient::UNIT_Peace:
		ui->m_lpIngredientUnit->addItem("pcs", QVariant((qreal)1));
		ui->m_lpIngredientUnit->setCurrentIndex(0);
		ui->m_lpIngredientValue->setValue(value);
		break;
	case cIngredient::UNIT_Volume:
		ui->m_lpIngredientUnit->addItem("qm", QVariant((qreal)1));
		ui->m_lpIngredientUnit->setCurrentIndex(0);
		ui->m_lpIngredientValue->setValue(value);
		break;
	case cIngredient::UNIT_Weight:
		m_index	= 1;

		if(value != 0)
		{
			while(value < 1)
			{
				value *= 1000;
				m_index++;
			}
		}

		ui->m_lpIngredientUnit->addItem("kg", QVariant((qreal)1000));
		ui->m_lpIngredientUnit->addItem("g", QVariant((qreal)1));
		ui->m_lpIngredientUnit->addItem("mg", QVariant((qreal)1/1000));
		ui->m_lpIngredientUnit->addItem("µg", QVariant((qreal)1/1000000));
		ui->m_lpIngredientUnit->addItem("ng", QVariant((qreal)1/1000000000));
		ui->m_lpIngredientUnit->addItem("pg", QVariant((qreal)1/1000000000000));

		ui->m_lpIngredientUnit->setCurrentIndex(m_index);

		ui->m_lpIngredientValue->setValue(value);
		break;
	default:
		ui->m_lpIngredientValue->setValue(value);
		ui->m_lpIngredientUnit->setEnabled(false);
		break;
	}
}

qreal cIngredientValue::value()
{
	qreal	factor	= ui->m_lpIngredientUnit->currentData().toReal();
	if(!ui->m_lpIngredientUnit->isEnabled())
		factor		= 1;
	qreal	value	= ui->m_lpIngredientValue->value();
	return(value*factor);
}
