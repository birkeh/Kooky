#ifndef CPLUGININFO_H
#define CPLUGININFO_H


#include "cplugin.h"

#include <QWidget>


namespace Ui {
class cPluginInfo;
}

/*!
 \brief

*/
class cPluginInfo : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \param parent
	*/
	explicit cPluginInfo(QWidget *parent = 0);
	/*!
	 \brief

	*/
	~cPluginInfo();

	/*!
	 \brief

	 \param lpPlugin
	*/
	void	setInfo(cPlugin* lpPlugin);
private:
	Ui::cPluginInfo *ui; /*!< TODO: describe */
};

#endif // CPLUGININFO_H
