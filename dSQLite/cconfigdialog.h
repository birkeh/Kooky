#ifndef CCONFIGDIALOG_H
#define CCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class cConfigDialog;
}

/*!
 \brief

*/
class cConfigDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \param parent
	*/
	explicit	cConfigDialog(QWidget *parent = 0);
	/*!
	 \brief

	*/
	~cConfigDialog();

	/*!
	 \brief

	 \param szFile
	*/
	void		setFile(const QString& szFile);
	/*!
	 \brief

	 \return QString
	*/
	QString		file();
private slots:
	/*!
	 \brief

	*/
	void on_m_lpBrowse_clicked();

	/*!
	 \brief

	 \param arg1
	*/
	void on_m_lpFile_textChanged(const QString &arg1);

private:
	Ui::cConfigDialog *ui; /*!< TODO: describe */
};

#endif // CCONFIGDIALOG_H
