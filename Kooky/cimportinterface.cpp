#include "cimportinterface.h"


QString cImportInterface::group(cIngredient::iIngredient i)
{
	return(cIngredient::group(i));
}

QString cImportInterface::name(cIngredient::iIngredient i)
{
	return(cIngredient::name(i));
}

QString cImportInterface::valueStr(cIngredient::iIngredient i)
{
	qreal	dValue	= value(i);
	QString	strValue;

	if(i == cIngredient::iIngredientCalories)
		strValue	= QString("%1 kcal").arg(dValue);
	else if(i == cIngredient::iIngredientJoule)
		strValue	= QString("%1 kJ").arg(dValue);
	else
	{
		if(dValue < 0.001)
			strValue	= QString("%1 µg").arg(dValue*1000000);
		else if(dValue < 1.0)
			strValue	= QString("%1 mg").arg(dValue*1000);
		else
			strValue	= QString("%1 g").arg(dValue);
	}
	return(strValue);
}
