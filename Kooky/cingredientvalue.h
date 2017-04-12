#ifndef CINGREDIENTVALUE_H
#define CINGREDIENTVALUE_H


#include "cingredient.h"

#include <QDialog>


namespace Ui {
class cIngredientValue;
}

/*!
 \brief

*/
class cIngredientValue : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \param parent
	*/
	explicit cIngredientValue(QWidget *parent = 0);
	/*!
	 \brief

	*/
	~cIngredientValue();

	/*!
	 \brief

	 \param szName
	 \param value
	 \param unit
	*/
	void					setValues(const QString& szName, qreal value, cIngredient::UNIT unit);
	/*!
	 \brief

	 \return qreal
	*/
	qreal					value();
private:
	Ui::cIngredientValue*	ui; /*!< TODO: describe */
	qint32					m_index; /*!< TODO: describe */
};

#endif // CINGREDIENTVALUE_H
