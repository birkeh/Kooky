#ifndef CPLUGININFO_H
#define CPLUGININFO_H


#include "cplugin.h"

#include <QWidget>


namespace Ui {
class cPluginInfo;
}

class cPluginInfo : public QWidget
{
	Q_OBJECT

public:
	explicit cPluginInfo(QWidget *parent = 0);
	~cPluginInfo();

	void	setInfo(cPlugin* lpPlugin);
private:
	Ui::cPluginInfo *ui;
};

#endif // CPLUGININFO_H
