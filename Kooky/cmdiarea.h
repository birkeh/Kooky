/**
  * \class cMDIArea
  *
  * \brief This class overwrites the default MDI area of the main window.
  *
  * \ingroup KOOKY
  *
  * This class overwrites the default MDI area of the main window. It also adds the capability to display a background image in the MDI area.
  *
  * \note
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef CMDIAREA_H
#define CMDIAREA_H


#include <QMdiArea>
#include <QImage>
#include <QMdiSubWindow>


/*!
 \brief

*/
class cMdiArea : public QMdiArea
{
	Q_OBJECT
public:
	cMdiArea(QWidget * parent = 0);
private:
	QImage		m_background; /*!< TODO: describe */
protected:
	/*!
	 \brief

	 \param event
	*/
	void		paintEvent(QPaintEvent *event);
};

#endif // CMDIAREA_H
