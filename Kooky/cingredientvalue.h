#ifndef CINGREDIENTVALUE_H
#define CINGREDIENTVALUE_H


#include "cingredient.h"

#include <QDialog>


namespace Ui {
class cIngredientValue;
}

class cIngredientValue : public QDialog
{
	Q_OBJECT

public:
	explicit cIngredientValue(QWidget *parent = 0);
	~cIngredientValue();

	void					setValues(const QString& szName, qreal value, cIngredient::UNIT unit);
	qreal					value();
private:
	Ui::cIngredientValue*	ui;
	qint32					m_index;
};

#endif // CINGREDIENTVALUE_H
