#include "cconfigdialog.h"
#include "ui_cconfigdialog.h"

#include <QFileDialog>
#include <QDir>


cConfigDialog::cConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cConfigDialog)
{
	ui->setupUi(this);
	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

cConfigDialog::~cConfigDialog()
{
	delete ui;
}

void cConfigDialog::setFile(const QString& szFile)
{
	ui->m_lpFile->setText(szFile);
}

QString cConfigDialog::file()
{
	return(ui->m_lpFile->text());
}

void cConfigDialog::on_m_lpBrowse_clicked()
{
	QString	szFile	= ui->m_lpFile->text();
	if(szFile.isEmpty())
		szFile	= QDir::homePath();

	szFile	= QFileDialog::getOpenFileName(this, tr("Select Database"), szFile, tr("Database Files (*.db)"));
	if(szFile.isNull())
		return;
	ui->m_lpFile->setText(szFile);
}

void cConfigDialog::on_m_lpFile_textChanged(const QString &arg1)
{
	if(arg1.isEmpty())
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	else
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
