#include "cbleibfitplugin.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMessageBox>


typedef struct tagMAPPER
{
	QString	key;
	qint16	value;
}	MAPPER;

MAPPER g_ingredientMapper[]	=
{
	{	"<td><b>Kilokalorien:</b></td>",	cIngredient::iIngredientCalories	},
	{	"<td><b>Kilojoule:</b></td>",	cIngredient::iIngredientJoule	},
	{	"<td><b>Protein:</b></td>",	cIngredient::iIngredientProtein	},
	{	"<td><b>Fett:</b></td>",	cIngredient::iIngredientFat	},
	{	"<td><b>Kohlehydrate:</b></td>",	cIngredient::iIngredientCarbohydrates	},
	{	"<td><b>davon Zucker:</b></td>",	cIngredient::iIngredientSugar	},
	{	"<td><b>Ballaststoffe:</b></td>",	cIngredient::iIngredientTotalDietaryFibre	},
	{	"<td><b>Ges&auml;ttigte Fetts&auml;uren:</b></td>",	cIngredient::iIngredientSaturatedfattyacids	},
	{	"<td><b>Einfach unges&auml;ttigte Fetts&auml;uren:</b></td>",	cIngredient::iIngredientMonounsaturatedfattyacids	},
	{	"<td><b>Mehrfach unges&auml;ttigte Fetts&auml;uren:</b></td>",	cIngredient::iIngredientPolyunsaturatedfattyacids	},
	{	"<td><b>Cholesterin:</b></td>",	cIngredient::iIngredientCholesterol	},
	{	"<td><b>Vitamin A:</b></td>",	cIngredient::iIngredientVitaminARetinol	},
	{	"<td><b>Vitamin C:</b></td>",	cIngredient::iIngredientVitaminC	},
	{	"<td><b>Vitamin D:</b></td>",	cIngredient::iIngredientVitaminD	},
	{	"<td><b>Vitamin E:</b></td>",	cIngredient::iIngredientVitaminEactiv	},
	{	"<td><b>Vitamin K:</b></td>",	cIngredient::iIngredientVitaminK	},
	{	"<td><b>Vitamin B1:</b></td>",	cIngredient::iIngredientVitaminB1	},
	{	"<td><b>Vitamin B2:</b></td>",	cIngredient::iIngredientVitaminB2	},
	{	"<td><b>Vitamin B6:</b></td>",	cIngredient::iIngredientVitaminB6	},
	{	"<td><b>Vitamin B12:</b></td>",	cIngredient::iIngredientVitaminB12	},
	{	"<td><b>Biotin:</b></td>",	cIngredient::iIngredientBiotin	},
	{	"<td><b>Fols&auml;ure:</b></td>",	cIngredient::iIngredientFolicacid	},
	{	"<td><b>Niacin:</b></td>",	cIngredient::iIngredientNiacinequivalent	},
	{	"<td><b>Panthotens&auml;ure:</b></td>",	cIngredient::iIngredientPantothenicacid	},
	{	"<td><b>Calcium (Ca):</b></td>",	cIngredient::iIngredientCalcium	},
	{	"<td><b>Chlor (Cl):</b></td>",	cIngredient::iIngredientChloride	},
	{	"<td><b>Kalium (K):</b></td>",	cIngredient::iIngredientPotassium	},
	{	"<td><b>Magnesium (Mg):</b></td>",	cIngredient::iIngredientMagnesium	},
	{	"<td><b>Natrium (Na):</b></td>",	cIngredient::iIngredientSodium	},
	{	"<td><b>Phosphor (P):</b></td>",	cIngredient::iIngredientPhosphorus	},
	{	"<td><b>Schwefel (S):</b></td>",	cIngredient::iIngredientSulphur	},
	{	"<td><b>Kupfer (Cu):</b></td>",	cIngredient::iIngredientCopper	},
	{	"<td><b>Eisen (Fe):</b></td>",	cIngredient::iIngredientIron	},
	{	"<td><b>Fluor (F):</b></td>",	cIngredient::iIngredientFluoride	},
	{	"<td><b>Mangan (Mn):</b></td>",	cIngredient::iIngredientManganese	},
	{	"<td><b>Jod (J):</b></td>",	cIngredient::iIngredientIodide	},
	{	"<td><b>Zink (Zn):</b></td>",	cIngredient::iIngredientZinc	},
	{	"<td><b>Alanin:</b></td>",	cIngredient::iIngredientAlanine	},
	{	"<td><b>Arginin:</b></td>",	cIngredient::iIngredientArginine	},
	{	"<td><b>Aspargin:</b></td>",	cIngredient::iIngredientAspartid	},
	{	"<td><b>Aspargins&auml;ure:</b></td>",	cIngredient::iIngredientAsparticacid	},
	{	"<td><b>Cystein:</b></td>",	cIngredient::iIngredientCystine	},
	{	"<td><b>Glutamin:</b></td>",	cIngredient::iIngredientGlutamid	},
	{	"<td><b>Glutamins&auml;ure:</b></td>",	cIngredient::iIngredientGlutamicacid	},
	{	"<td><b>Glycerin:</b></td>",	cIngredient::iIngredientGlycerolandLipoides	},
	{	"<td><b>Histidin:</b></td>",	cIngredient::iIngredientHistidine	},
	{	"<td><b>Isoleucin:</b></td>",	cIngredient::iIngredientIsoleucine	},
	{	"<td><b>Leucin:</b></td>",	cIngredient::iIngredientLeucine	},
	{	"<td><b>Lysin:</b></td>",	cIngredient::iIngredientLysine	},
	{	"<td><b>Methionin:</b></td>",	cIngredient::iIngredientMethionine	},
	{	"<td><b>Phenylalanin:</b></td>",	cIngredient::iIngredientPhenylalanine	},
	{	"<td><b>Prolin:</b></td>",	cIngredient::iIngredientProline	},
	{	"<td><b>Serin:</b></td>",	cIngredient::iIngredientSerine	},
	{	"<td><b>Threonin:</b></td>",	cIngredient::iIngredientThreonine	},
	{	"<td><b>Tryptophan:</b></td>",	cIngredient::iIngredientTryptophane	},
	{	"<td><b>Tyrosin:</b></td>",	cIngredient::iIngredientTyrosine	},
	{	"<td><b>Valin:</b></td>",	cIngredient::iIngredientValine	}
};

QMap<QString, QString> cBleibFitPlugin::detailsCapability()
{
	QMap<QString, QString>	map;
	return(map);
}

//http://www.bleibfit.at/index.php?lebensmittel&food=true&mode=suche&su_begriff=milch
QStringList cBleibFitPlugin::search(const QString& szSearch, const QString&)
{
	int						z;

	m_szUrls.clear();
	m_szIngredients.clear();

	for(z = 0;z < cIngredient::iIngredientMax;z++)
		m_rValues[z]	= -1;

	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("http://www.bleibfit.at/index.php?lebensmittel&food=true&mode=suche&su_begriff=") + szSearch));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	QByteArray				szData  = reply->readAll();
	delete reply;

	QList<QByteArray>		szList  = szData.split('\n');

	for(z = 0;z < szList.count();z++)
	{
		QString szLine  = QString::fromLatin1(szList.at(z));
		if(szLine.contains("<table border=\"0\" cellpadding=\"2\" cellspacing=\"1\" width=\"100%\">"))
			break;
	}

	if(z >= szList.count())
		return(QStringList());

	for(;z < szList.count();z++)
	{
		QString szLine  = QString::fromLatin1(szList.at(z));
		if(szLine.contains("</tr>"))
			break;
	}

	for(;z < szList.count();z++)
	{
		QString szLine  = QString::fromLatin1(szList.at(z));
		if(szLine.contains("<tr bgcolor="))
		{
			z++;
			szLine  = QString::fromLatin1(szList.at(z));

			QString szURL;
			QString	szIngredient;

			if(szLine.indexOf("<a href"))
			{
				int pos = szLine.indexOf("<a href")+9;
				szURL	= szLine.mid(pos);
				if(szURL.indexOf(">"))
					szURL   = QString("http://www.bleibfit.at/")+szURL.left(szURL.indexOf(">")-1);
				else
					szURL   = "";
			}

			if(szLine.indexOf("<b>"))
			{
				szIngredient	= szLine.mid(szLine.indexOf("<b>")+3);
				szIngredient	= szIngredient.left(szIngredient.indexOf("</b>"));
			}

			if(szIngredient.length())
			{
				m_szIngredients.append(szIngredient);
				m_szUrls.append(szURL);
			}
			z++;
		}
	}
	return(m_szIngredients);
}

//http://www.bleibfit.at/lebensmittel&food=true&link=buttermilch.phtml?hashID=929deedd0e06667441d7afa4570a12ba
bool cBleibFitPlugin::load(qint16 iIndex)
{
	if(iIndex > m_szUrls.count())
		return(false);

	for(int i = 0;i < cIngredient::iIngredientMax;i++)
		m_rValues[i] = -1;

	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(m_szUrls.at(iIndex)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	QByteArray				szData  = reply->readAll();
	delete reply;

	QList<QByteArray>		szList  = szData.split('\n');

	for(int z = 0;z < szList.count();z++)
	{
		QString szLine  = QString::fromLatin1(szList.at(z));
		if(szLine.contains("<div class=\"balken1\">"))
		{
			for(;z < szList.count();z++)
			{
				szLine  = QString::fromLatin1(szList.at(z));
				if(szLine.contains("</table>"))
					break;

				if(szLine.contains("<tr>"))
				{
					z++;
					szLine  = QString::fromLatin1(szList.at(z));
					for(int y = 0;y < (int)sizeof(g_ingredientMapper)/(int)sizeof(MAPPER);y++)
					{
						if(szLine.contains(g_ingredientMapper[y].key))
						{
							z++;
							szLine  = QString::fromLatin1(szList.at(z));

							int		x		= szLine.indexOf(">")+1;
							QString	szTmp	= szLine.mid(x);
							szTmp			= szTmp.left(szTmp.indexOf("<"));

							z++;
							szLine			= QString::fromLatin1(szList.at(z));

							qreal	dFactor	= 1;

							if(szLine.contains(">g<"))
								dFactor	= 1;
							else if(szLine.contains(">mg<"))
								dFactor	= 1000;
							else if(szLine.contains(">µg<"))
								dFactor	= 1000000;

							qreal	dValue	= szTmp.replace(",", ".").toDouble();
							m_rValues[g_ingredientMapper[y].value]	= dValue/dFactor;
							break;
						}
					}
				}
			}
		}
	}

	m_bLoaded		= true;
	m_iLoadedIndex	= iIndex;
	return(true);
}

qreal cBleibFitPlugin::value(cIngredient::iIngredient i)
{
	if(m_bLoaded)
		return(m_rValues[i]);
	return(-1);
}

QString cBleibFitPlugin::ingredientName()
{
	if(m_bLoaded)
		return(m_szIngredients.at(m_iLoadedIndex));
	else
		return(QString(""));
}

bool cBleibFitPlugin::config()
{
	return(true);
}

QString cBleibFitPlugin::author()
{
	return("Herwig Birke");
}

QString cBleibFitPlugin::company()
{
	return("WIN-DESIGN");
}

QString cBleibFitPlugin::link()
{
	return("http://www.windesign.at");
}

QString cBleibFitPlugin::description()
{
	return("This is the description.");
}

QString cBleibFitPlugin::copyright()
{
	return("This is the copyright.");
}
