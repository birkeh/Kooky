#ifndef TYPEDEF_H
#define TYPEDEF_H


#include <QList>
#include <QString>


/*!
 \brief

*/
typedef struct tagINGREDIENT
{
	qint32	iIngredient; /*!< TODO: describe */
	QString	szGroup; /*!< TODO: describe */
	QString	szIngredient; /*!< TODO: describe */
	qreal	dCalories; /*!< TODO: describe */
	qreal	dCarbohydrates; /*!< TODO: describe */
/*!
 \brief

*/
}	INGREDIENT, *LPINGREDIENT;

/*!
 \brief

*/
typedef QList<INGREDIENT> INGREDIENT_LIST;


#endif // TYPEDEF_H
