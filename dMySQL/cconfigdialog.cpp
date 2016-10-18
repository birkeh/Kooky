#include "cconfigdialog.h"
#include "ui_cconfigdialog.h"
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>


cConfigDialog::cConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cConfigDialog),
	m_bPasswordChanged(false)
{
	ui->setupUi(this);
}

cConfigDialog::~cConfigDialog()
{
	delete ui;
}

void cConfigDialog::setHostname(const QString& szHostname)
{
	ui->m_lpHostname->setText(szHostname);
}

void cConfigDialog::setDatabase(const QString& szDatabase)
{
	ui->m_lpDatabase->setText(szDatabase);
}

void cConfigDialog::setUserName(const QString& szUserName)
{
	ui->m_lpUsername->setText(szUserName);
}

void cConfigDialog::setPassword(const QString& szPassword)
{
	ui->m_lpPassword->setText(szPassword);
	ui->m_lpPassword2->setText(szPassword);
}

QString cConfigDialog::hostname()
{
	return(ui->m_lpHostname->text());
}

QString cConfigDialog::database()
{
	return(ui->m_lpDatabase->text());
}

QString cConfigDialog::userName()
{
	return(ui->m_lpUsername->text());
}

QString cConfigDialog::password()
{
	return(ui->m_lpPassword->text());
}

void cConfigDialog::on_m_lpTestButton_clicked()
{
}

void cConfigDialog::on_m_lpOKButton_clicked()
{
	if(ui->m_lpPassword->text() != ui->m_lpPassword2->text())
		QMessageBox::critical(this, "Database", "password does not match");
	else
		accept();
}

void cConfigDialog::on_m_lpCancelButton_clicked()
{
	reject();
}

void cConfigDialog::on_m_lpPassword_textChanged(const QString&/*arg1*/)
{
	m_bPasswordChanged	= true;
	if(ui->m_lpPassword->text() != ui->m_lpPassword2->text())
		ui->m_lpPasswordMatch->setText("password does not match");
	else
		ui->m_lpPasswordMatch->setText("");
}

void cConfigDialog::on_m_lpPassword2_textChanged(const QString&/*arg1*/)
{
	m_bPasswordChanged	= true;
	if(ui->m_lpPassword->text() != ui->m_lpPassword2->text())
		ui->m_lpPasswordMatch->setText("password does not match");
	else
		ui->m_lpPasswordMatch->setText("");
}

QWidget* cConfigDialog::widget()
{
	return((QWidget*)ui->gridLayout);
}
