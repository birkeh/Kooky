#ifndef CCONFIGDIALOG_H
#define CCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class cConfigDialog;
}

class cConfigDialog : public QDialog
{
	Q_OBJECT

public:
	explicit	cConfigDialog(QWidget *parent = 0);
	~cConfigDialog();

	void		setFile(const QString& szFile);
	QString		file();
private slots:
	void on_m_lpBrowse_clicked();

	void on_m_lpFile_textChanged(const QString &arg1);

private:
	Ui::cConfigDialog *ui;
};

#endif // CCONFIGDIALOG_H
