#include "csqliteplugin.h"
#include "cconfigdialog.h"

#include "cingredient.h"

#include <QSqlError>
#include <QSettings>
#include <QSqlQuery>
#include <QMessageBox>


bool cSQLitePlugin::connect()
{
	QSettings	settings;

	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName(settings.value(QString("plugins/%1/hostName").arg(pluginName())).toString());
	m_db.setDatabaseName(settings.value(QString("plugins/%1/databaseName").arg(pluginName())).toString());

	return(open());
}

bool cSQLitePlugin::init()
{
	QSettings	settings;

	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName(settings.value(QString("plugins/%1/hostName").arg(pluginName())).toString());
	m_db.setDatabaseName(settings.value(QString("plugins/%1/databaseName").arg(pluginName())).toString());

	m_bConnected	= m_db.open();

	if(m_bConnected)
	{
		QStringList	tables	= m_db.tables();
		if(tables.count())
		{
			if(QMessageBox::question(0, "Tables exist", "Database not empty.\nExisting tables will be deleted.\nContinue?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::No)
				return(m_bConnected);
		}
		QSqlQuery	query(m_db);
		for(int z = 0;z < tables.count();z++)
			query.exec(QString("DROP TABLE %1;").arg(tables.at(z)));

		if(!query.exec("CREATE TABLE settings ( `var` VARCHAR(100) NOT NULL , `val` VARCHAR(100) NOT NULL )"))
		{
			m_szLastError	= query.lastError().text();
			m_db.close();
			m_bConnected	= false;
			return(m_bConnected);
		}

		if(!query.exec("INSERT INTO settings values ('version', '1.0');"))
		{
			m_szLastError	= query.lastError().text();
			m_db.close();
			m_bConnected	= false;
			return(m_bConnected);
		}

		if(!query.exec("CREATE TABLE ingredient_group ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` VARCHAR(100) NOT NULL )"))
		{
			m_szLastError	= query.lastError().text();
			m_db.close();
			m_bConnected	= false;
			return(m_bConnected);
		}

		if(!query.exec("CREATE TABLE ingredient ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` VARCHAR(100) NOT NULL, ingredient_group_id INTEGER NOT NULL )"))
		{
			m_szLastError	= query.lastError().text();
			m_db.close();
			m_bConnected	= false;
			return(m_bConnected);
		}

		if(!query.exec("CREATE TABLE ingredient_values ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `ingredient_id` INTEGER NOT NULL, `ingredient_number` INTEGER NOT NULL, `value` REAL, FOREIGN KEY(ingredient_id) REFERENCES ingredient(id) )"))
		{
			m_szLastError	= query.lastError().text();
			m_db.close();
			m_bConnected	= false;
			return(m_bConnected);
		}

		createGroup("default");
	}
	else
		m_szLastError	= m_db.lastError().text();

	return(m_bConnected);
}

bool cSQLitePlugin::open()
{
	m_bConnected	= m_db.open();

	if(m_bConnected)
	{
		QSqlQuery	query(m_db);
		if(!query.exec("SELECT * FROM settings"))
		{
			init();

			if(!query.exec("SELECT * FROM settings"))
			{
				m_szLastError	= query.lastError().text();
				m_db.close();
				m_bConnected	= false;
				return(m_bConnected);
			}
		}
	}
	else
		m_szLastError	= m_db.lastError().text();

	return(m_bConnected);
}

QString cSQLitePlugin::lastError()
{
	return(m_szLastError);
}

bool cSQLitePlugin::config()
{
	cConfigDialog	dlg;
	QSettings		settings;
	dlg.setFile(settings.value(QString("plugins/%1/databaseName").arg(pluginName())).toString());

	if(dlg.exec() == QDialog::Accepted)
	{
		m_db.close();
		settings.setValue(QString("plugins/%1/databaseName").arg(pluginName()), dlg.file());
		m_db.setDatabaseName(settings.value(QString("plugins/%1/databaseName").arg(pluginName())).toString());
		return(open());
	}
	return(m_bConnected);
}

qint32 cSQLitePlugin::exists(const QString& szName, const QString& szGroup)
{
	if(!m_bConnected)
		return(-1);

	qint32	iGroup	= existsGroup(szGroup);
	if(iGroup == -1)
		return(-1);

	QSqlQuery	query(m_db);

	if(!query.exec(QString("SELECT id FROM ingredient WHERE name = \"%1\" AND ingredient_group_id=%2").arg(szName).arg(iGroup)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	query.first();
	if(!query.isValid())
		return(-1);

	return(query.value(0).toInt());
}

qint32 cSQLitePlugin::existsGroup(const QString& szGroup)
{
	if(!m_bConnected)
		return(-1);

	QSqlQuery	query(m_db);

	if(!query.exec(QString("SELECT id FROM ingredient_group WHERE name = \"%1\"").arg(szGroup)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	query.first();
	if(!query.isValid())
		return(-1);

	return(query.value(0).toInt());
}

qint32 cSQLitePlugin::existsIngredient(qint32 id, qint16 ingredientNumber)
{
	if(!m_bConnected)
		return(-1);

	QSqlQuery	query(m_db);

	if(!query.exec(QString("SELECT id FROM ingredient_values WHERE ingredient_id = %1 AND ingredient_number = %2").arg(id).arg(ingredientNumber)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	query.first();
	if(!query.isValid())
		return(-1);

	return(query.value(0).toInt());
}

qint32 cSQLitePlugin::create(const QString& szName, const QString& szGroup)
{
	if(!m_bConnected)
		return(-1);

	if(exists(szName, szGroup) != -1)
		return(-1);

	qint32	iGroup	= existsGroup(szGroup);
	if(iGroup == -1)
		iGroup	= createGroup(szGroup);
	if(iGroup == -1)
		return(-1);

	QSqlQuery	query(m_db);
	if(!query.exec(QString("INSERT INTO ingredient (name, ingredient_group_id) VALUES (\"%1\", %2)").arg(szName).arg(iGroup)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	return(exists(szName, szGroup));
}

qint32 cSQLitePlugin::createGroup(const QString& szGroup)
{
	if(!m_bConnected)
		return(-1);

	if(existsGroup(szGroup) != -1)
		return(-1);

	QSqlQuery	query(m_db);
	if(!query.exec(QString("INSERT INTO ingredient_group (name) VALUES (\"%1\")").arg(szGroup)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	return(existsGroup(szGroup));
}

bool cSQLitePlugin::set(qint32 id, qint16 ingredientNumber, qreal value)
{
	if(!m_bConnected)
		return(-1);

	if(existsIngredient(id, ingredientNumber) != -1)
		return(-1);

	QSqlQuery	query(m_db);
	if(!query.exec(QString("INSERT INTO ingredient_values (ingredient_id, ingredient_number, value) VALUES (%1, %2, %3)").arg(id).arg(ingredientNumber).arg(value)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	return(existsIngredient(id, ingredientNumber));
}

QString cSQLitePlugin::name(qint32 id)
{
	if(!m_bConnected)
		return("");

	QSqlQuery	query(m_db);
	if(!query.exec(QString("SELECT name FROM ingredient WHERE id=%1").arg(id)))
	{
		m_szLastError	= query.lastError().text();
		return("");
	}
	if(!query.first())
		return("");
	return(query.value("name").toString());
}

QString cSQLitePlugin::group(qint32 id)
{
	if(!m_bConnected)
		return("");

	QSqlQuery	query(m_db);
	if(!query.exec(QString("SELECT ingredient_group.name FROM ingredient, ingredient_group WHERE ingredient.ingredient_group_id=ingredient_group.id AND ingredient.id=%1").arg(id)))
	{
		m_szLastError	= query.lastError().text();
		return("");
	}
	if(!query.first())
		return("");
	return(query.value("name").toString());
}

qreal cSQLitePlugin::get(qint32 id, qint16 ingredientNumber)
{
	if(!m_bConnected)
		return(-1);

	QSqlQuery	query(m_db);
	if(!query.exec(QString("SELECT value FROM ingredient_values WHERE ingredient_id=%1 AND ingredient_number=%2").arg(id).arg(ingredientNumber)))
	{
		m_szLastError	= query.lastError().text();
		return(-1);
	}
	if(!query.first())
		return(0);
	return(query.value("value").toReal());
}

INGREDIENT_LIST cSQLitePlugin::ingredients()
{
	if(!m_bConnected)
		return(INGREDIENT_LIST());

	QSqlQuery	query(m_db);
	if(!query.exec(QString(QString("SELECT ingredient.id, ingredient.name, ingredient_group.name, calories.value, carbohydrates.value FROM ingredient, ingredient_group, ingredient_values AS calories, ingredient_values AS carbohydrates WHERE ingredient.ingredient_group_id = ingredient_group.id AND calories.ingredient_id = ingredient.id AND calories.ingredient_number = %1 AND carbohydrates.ingredient_id = ingredient.id AND carbohydrates.ingredient_number = %2 ORDER BY ingredient_group.name, ingredient.name").arg(cIngredient::iIngredientCalories).arg(cIngredient::iIngredientCarbohydrates))))
	{
		m_szLastError	= query.lastError().text();
		return(INGREDIENT_LIST());
	}

	INGREDIENT_LIST	list;
	while(query.next())
	{
		INGREDIENT	i;
		i.iIngredient		= query.value(0).toInt();
		i.szIngredient		= query.value(1).toString();
		i.szGroup			= query.value(2).toString();
		i.dCalories			= query.value(3).toReal();
		i.dCarbohydrates	= query.value(4).toReal();
		list.append(i);
	}

	return(list);
}

QStringList cSQLitePlugin::groups()
{
	if(!m_bConnected)
		return(QStringList());

	QSqlQuery	query(m_db);
	if(!query.exec(QString("SELECT name FROM ingredient_group ORDER BY name")))
	{
		m_szLastError	= query.lastError().text();
		return(QStringList());
	}

	QStringList	list;
	while(query.next())
		list.append(query.value(0).toString());

	return(list);
}

bool cSQLitePlugin::beginTransaction()
{
	if(!m_bConnected)
		return(false);
	return(m_db.transaction());
}

bool cSQLitePlugin::endTransaction()
{
	if(!m_bConnected)
		return(false);
	return(m_db.commit());
}

QString cSQLitePlugin::author()
{
	return("Herwig Birke");
}

QString cSQLitePlugin::company()
{
	return("WIN-DESIGN");
}

QString cSQLitePlugin::link()
{
	return("http://www.windesign.at");
}

QString cSQLitePlugin::description()
{
	return("This is the description.");
}

QString cSQLitePlugin::copyright()
{
	return("This is the copyright.");
}
