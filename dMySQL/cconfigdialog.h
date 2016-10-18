/**
  * \class cConfigDialog
  *
  * \brief Configuration Dialog for dMySQL
  *
  * \ingroup MYSQL
  *
  * This class implements basic import functionality for Kooky.
  * All functions may be overwritten by derriving classes.
  *
  * \note Attempts at zen rarely work.
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef CCONFIGDIALOG_H
#define CCONFIGDIALOG_H

#include <QDialog>
#include <QCloseEvent>


namespace Ui {
class cConfigDialog;
}

class cConfigDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	  * \brief
	  *
	 \param parent
	*/
	explicit cConfigDialog(QWidget *parent = 0);
	/**
	  * \brief
	  *
	*/
	~cConfigDialog();

	/**
	  * \brief
	  *
	 \param szHostname
	*/
	void	setHostname(const QString& szHostname);
	/**
	  * \brief
	  *
	 \param szDatabase
	*/
	void	setDatabase(const QString& szDatabase);
	/**
	  * \brief
	  *
	 \param szUserName
	*/
	void	setUserName(const QString& szUserName);
	/**
	  * \brief
	  *
	 \param szPassword
	*/
	void	setPassword(const QString& szPassword);
	/**
	  * \brief
	  *
	 \return QString
	*/
	QString	hostname();
	/**
	  * \brief
	  *
	 \return QString
	*/
	QString	database();
	/**
	  * \brief
	  *
	 \return QString
	*/
	QString	userName();
	/**
	  * \brief
	  *
	 \return QString
	*/
	QString	password();

	QWidget*	widget();
private slots:
	/**
	  * \brief
	  *

	*/
	void on_m_lpTestButton_clicked();
	/**
	  * \brief
	  *
	 \param arg1
	*/
	void on_m_lpPassword_textChanged(const QString &arg1);
	/**
	  * \brief
	  *
	 \param arg1
	*/
	void on_m_lpPassword2_textChanged(const QString &arg1);
	/**
	  * \brief
	  *
	*/
	void on_m_lpOKButton_clicked();
	/**
	  * \brief
	  *
	*/
	void on_m_lpCancelButton_clicked();

private:
	Ui::cConfigDialog *ui; /*!< TODO: describe */
	bool	m_bPasswordChanged; /*!< TODO: describe */

protected:
};

#endif // CCONFIGDIALOG_H
