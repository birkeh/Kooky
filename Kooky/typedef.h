#ifndef TYPEDEF_H
#define TYPEDEF_H


#include <QList>
#include <QString>


typedef struct tagINGREDIENT
{
	QString	szGroup;
	QString	szIngredient;
}	INGREDIENT, *LPINGREDIENT;

typedef QList<INGREDIENT> INGREDIENT_LIST;


#endif // TYPEDEF_H
