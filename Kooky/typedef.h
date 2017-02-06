#ifndef TYPEDEF_H
#define TYPEDEF_H


#include <QList>
#include <QString>


typedef struct tagINGREDIENT
{
	qint32	iIngredient;
	QString	szGroup;
	QString	szIngredient;
	double	dCalories;
	double	dCarbohydrates;
}	INGREDIENT, *LPINGREDIENT;

typedef QList<INGREDIENT> INGREDIENT_LIST;


#endif // TYPEDEF_H
