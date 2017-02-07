#include "cernaehrungplugin.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMessageBox>
#include <QTextDocument>


typedef struct tagVALUES
{
	QString							szSearch;
	cIngredient::iIngredient		iIngredient;
	qreal							dValue;
} VALUES;

VALUES g_values[]	=
{
	{	"<td>Broteinheiten</td>",						cIngredient::iIngredientBreadUnits, -1	},
	{	"<td>Kilokalorien</td>",						cIngredient::iIngredientCalories, -1	},
	{	"<td>Eiweiß</td>",								cIngredient::iIngredientProtein, -1	},
	{	"<td>Fett</td>",								cIngredient::iIngredientFat, -1	},
	{	"<td>Kohlenhydrate</td>",						cIngredient::iIngredientCarbohydrates, -1	},
	{	"<td>Alkohol</td>",								cIngredient::iIngredientAlcohol, -1	},
	{	"<td>Wasser</td>",								cIngredient::iIngredientWater, -1	},
	{	"<td>Ballaststoffe gesamt</td>",				cIngredient::iIngredientTotalDietaryFibre, -1	},
	{	"<td>Cholesterin</td>",							cIngredient::iIngredientCholesterol, -1	},
	{	"<td>Mineralstoffe</td>",						cIngredient::iIngredientMineral, -1	},

	{	"<td>Vitamin A Retinol</td>",					cIngredient::iIngredientVitaminARetinol, -1	},
	{	"<td>Vitamin D</td>",							cIngredient::iIngredientVitaminD, -1	},
	{	"<td>Vitamin E Aktiv.</td>",					cIngredient::iIngredientVitaminEactiv, -1	},
	{	"<td>Folsäure</td>",							cIngredient::iIngredientFolicacid, -1	},
	{	"<td>Vitamin B1</td>",							cIngredient::iIngredientVitaminB1, -1	},
	{	"<td>Vitamin B2</td>",							cIngredient::iIngredientVitaminB2, -1	},
	{	"<td>Vitamin B6</td>",							cIngredient::iIngredientVitaminB6, -1	},
	{	"<td>Vitamin C</td>",							cIngredient::iIngredientVitaminC, -1	},
	{	"<td>a-Tocopherol</td>",						cIngredient::iIngredientaTocopherol, -1	},
	{	"<td>Vitamin K</td>",							cIngredient::iIngredientVitaminK, -1	},
	{	"<td>Nicotinamid</td>",							cIngredient::iIngredientNicotinamide, -1	},
	{	"<td>Pantothensäure</td>",						cIngredient::iIngredientPantothenicacid, -1	},
	{	"<td>Biotin</td>",								cIngredient::iIngredientBiotin, -1	},
	{	"<td>Vitamin B12</td>",							cIngredient::iIngredientVitaminB12, -1	},
	{	"<td>Retinoläquivalent</td>",					cIngredient::iIngredientRetinolequivalent, -1	},
	{	"<td>ß-Carotin</td>",							cIngredient::iIngredientbCarotene, -1	},
	{	"<td>Niacinäquivalent</td>",					cIngredient::iIngredientNiacinequivalent, -1	},
	{	"<td>freies Folsäureäquivalent</td>",			cIngredient::iIngredientfreefolicacidequivalent, -1	},
	{	"<td>freie Folsäure</td>",						cIngredient::iIngredientfreefolicacid, -1	},

	{	"<td>Natrium</td>",								cIngredient::iIngredientSodium, -1	},
	{	"<td>Kalium</td>",								cIngredient::iIngredientPotassium, -1	},
	{	"<td>Magnesium</td>",							cIngredient::iIngredientMagnesium, -1	},
	{	"<td>Calcium</td>",								cIngredient::iIngredientCalcium, -1	},
	{	"<td>Eisen</td>",								cIngredient::iIngredientIron, -1	},
	{	"<td>Phosphor</td>",							cIngredient::iIngredientPhosphorus, -1	},
	{	"<td>Kupfer</td>",								cIngredient::iIngredientCopper, -1	},
	{	"<td>Zink</td>",								cIngredient::iIngredientZinc, -1	},
	{	"<td>Chlorid</td>",								cIngredient::iIngredientChloride, -1	},
	{	"<td>Fluorid</td>",								cIngredient::iIngredientFluoride, -1	},
	{	"<td>Jodid</td>",								cIngredient::iIngredientIodide, -1	},
	{	"<td>Selen</td>",								cIngredient::iIngredientSelenium, -1	},
	{	"<td>Mangan</td>",								cIngredient::iIngredientManganese, -1	},
	{	"<td>Schwefel</td>",							cIngredient::iIngredientSulphur, -1	},

	{	"<td>Arginin</td>",								cIngredient::iIngredientArginine, -1	},
	{	"<td>Cystin</td>",								cIngredient::iIngredientCystine, -1	},
	{	"<td>Histidin</td>",							cIngredient::iIngredientHistidine, -1	},
	{	"<td>Isoleucin</td>",							cIngredient::iIngredientIsoleucine, -1	},
	{	"<td>Leucin</td>",								cIngredient::iIngredientLeucine, -1	},
	{	"<td>Lysin</td>",								cIngredient::iIngredientLysine, -1	},
	{	"<td>Methionin</td>",							cIngredient::iIngredientMethionine, -1	},
	{	"<td>Phenylalanin</td>",						cIngredient::iIngredientPhenylalanine, -1	},
	{	"<td>Threonin</td>",							cIngredient::iIngredientThreonine, -1	},
	{	"<td>Tryptophan</td>",							cIngredient::iIngredientTryptophane, -1	},
	{	"<td>Tyrosin</td>",								cIngredient::iIngredientTyrosine, -1	},
	{	"<td>Valin</td>",								cIngredient::iIngredientValine, -1	},
	{	"<td>Alanin</td>",								cIngredient::iIngredientAlanine, -1	},
	{	"<td>Asparaginsäure</td>",						cIngredient::iIngredientAsparticacid, -1	},
	{	"<td>Glutaminsäure</td>",						cIngredient::iIngredientGlutamicacid, -1	},
	{	"<td>Glycin</td>",								cIngredient::iIngredientGlycine, -1	},
	{	"<td>Prolin</td>",								cIngredient::iIngredientProline, -1	},
	{	"<td>Serin</td>",								cIngredient::iIngredientSerine, -1	},
	{	"<td>sonst. essent. Aminosäuren</td>",			cIngredient::iIngredientotheressent_aminoacids, -1	},
	{	"<td>essent. Aminosäuren</td>",					cIngredient::iIngredientessent_aminoacids, -1	},
	{	"<td>sonst. n. essent. Aminosäuren</td>",		cIngredient::iIngredientothernonessent_aminoacids, -1	},
	{	"<td>n. essent. Aminosäuren</td>",				cIngredient::iIngredientnonessent_aminoacids, -1	},

	{	"<td>Ges. Fettsäuren</td>",						cIngredient::iIngredientSaturatedfattyacids, -1	},
	{	"<td>einfach unges. Fettsäuren</td>",			cIngredient::iIngredientMonounsaturatedfattyacids, -1	},
	{	"<td>mehrf. unges. Fettsäuren</td>",			cIngredient::iIngredientPolyunsaturatedfattyacids, -1	},
	{	"<td>Buttersäure</td>",							cIngredient::iIngredientButyricacid, -1	},
	{	"<td>Capronsäure</td>",							cIngredient::iIngredientCaproicacid, -1	},
	{	"<td>Caprylsäure</td>",							cIngredient::iIngredientCaprylicacid, -1	},
	{	"<td>Caprinsäure</td>",							cIngredient::iIngredientCapricacid, -1	},
	{	"<td>Laurinsäure</td>",							cIngredient::iIngredientLauricacid, -1	},
	{	"<td>Myristinsäure</td>",						cIngredient::iIngredientMyristicacid, -1	},
	{	"<td>C15:O Fettsäure</td>",						cIngredient::iIngredientC15_O_fattyacid, -1	},
	{	"<td>Palmitinsäure</td>",						cIngredient::iIngredientPalmiticacid, -1	},
	{	"<td>Margarinsäure</td>",						cIngredient::iIngredientMargaricacid, -1	},
	{	"<td>Stearinsäure</td>",						cIngredient::iIngredientStearicacid, -1	},
	{	"<td>Arachinsäure</td>",						cIngredient::iIngredientArachicacid, -1	},
	{	"<td>Behensäure</td>",							cIngredient::iIngredientBehenicacid, -1	},
	{	"<td>Lignocerinsäure</td>",						cIngredient::iIngredientLignocericacid, -1	},
	{	"<td>Palmitoleinsäure</td>",					cIngredient::iIngredientPalmitoleicacid, -1	},
	{	"<td>Ölsäure</td>",								cIngredient::iIngredientOleicacid, -1	},
	{	"<td>Eicosensäure</td>",						cIngredient::iIngredientEicosenicacid, -1	},
	{	"<td>C22:1 Fettsäure</td>",						cIngredient::iIngredientC22_1_fattyacid, -1	},
	{	"<td>C14:1 Fettsäure</td>",						cIngredient::iIngredientC14_1_fattyacid, -1	},
	{	"<td>C24:1 Fettsäure</td>",						cIngredient::iIngredientC24_1_fattyacid, -1	},
	{	"<td>Linolsäure</td>",							cIngredient::iIngredientLinoleicacid, -1	},
	{	"<td>Linolensäure</td>",						cIngredient::iIngredientLinolenicacid, -1	},
	{	"<td>Arachidonsäure</td>",						cIngredient::iIngredientArachidonicacid, -1	},
	{	"<td>C18:4 Fettsäure</td>",						cIngredient::iIngredientC18_4_fattyacid, -1	},
	{	"<td>C20:5 N-3 Fettsäure</td>",					cIngredient::iIngredientC20_5_N_3fattyacid, -1	},
	{	"<td>C22:5 N-3 Fettsäure</td>",					cIngredient::iIngredientC22_5_N_3fattyacid, -1	},
	{	"<td>C22:6 N-3 Fettsäure</td>",					cIngredient::iIngredientC22_6_N_3fattyacid, -1	},
	{	"<td>C16:2 Fettsäure</td>",						cIngredient::iIngredientC16_2_fattyacid, -1	},
	{	"<td>sonst. gesättigte Fettsäuren</td>",		cIngredient::iIngredientothersaturatedfattyacids, -1	},
	{	"<td>sonst. einfach unges. Fettsäuren</td>",	cIngredient::iIngredientothermonounsaturatedfattyacids, -1	},
	{	"<td>Nonadecatriensäure</td>",					cIngredient::iIngredientNonadecatrienicacid, -1	},
	{	"<td>Eicosadiensäure</td>",						cIngredient::iIngredientEicosadienicacid, -1	},
	{	"<td>Eicosatriensäure</td>",					cIngredient::iIngredientEicosatrienicacid, -1	},
	{	"<td>Docosadiensäure</td>",						cIngredient::iIngredientDocosadienicacid, -1	},
	{	"<td>Docosatriensäure</td>",					cIngredient::iIngredientDocosatrienicacid, -1	},
	{	"<td>Docosatetraensäure</td>",					cIngredient::iIngredientDocosatetraenicacid, -1	},
	{	"<td>sonst. mehrfach unges. Fettsäuren</td>",	cIngredient::iIngredientotherpolyunsat_fattyacids, -1	},
	{	"<td>sonst. kurzkettige Fettsäuren</td>",		cIngredient::iIngredientothershort_chainfattyacids, -1	},
	{	"<td>kurzkettige Fettsäuren</td>",				cIngredient::iIngredientshort_chainfattyacids, -1	},
	{	"<td>sonst. mittelkettige Fettsäuren</td>",		cIngredient::iIngredientothermedium_chainfattyacids, -1	},
	{	"<td>mittelkettige Fettsäuren</td>",			cIngredient::iIngredientmedium_chainfattyacids, -1	},
	{	"<td>sonst. langkettige Fettsäuren</td>",		cIngredient::iIngredientotherlong_chainfattyacids, -1	},
	{	"<td>langkettige Fettsäuren</td>",				cIngredient::iIngredientlong_chainfattyacids, -1	},
	{	"<td>Glycerin + Lipoide</td>",					cIngredient::iIngredientGlycerolandLipoides, -1	},

	{	"<td>Sorbit</td>",								cIngredient::iIngredientSorbitol, -1	},
	{	"<td>Glucose</td>",								cIngredient::iIngredientGlucose, -1	},
	{	"<td>Fructose</td>",							cIngredient::iIngredientFructose, -1	},
	{	"<td>Saccharose</td>",							cIngredient::iIngredientSucrose, -1	},
	{	"<td>Lactose</td>",								cIngredient::iIngredientLactose, -1	},
	{	"<td>Stärke</td>",								cIngredient::iIngredientStarch, -1	},
	{	"<td>Maltose</td>",								cIngredient::iIngredientMaltose, -1	},
	{	"<td>Galactose</td>",							cIngredient::iIngredientGalactose, -1	},
	{	"<td>Glycogen</td>",							cIngredient::iIngredientGlycogene, -1	},
	{	"<td>Pentosan</td>",							cIngredient::iIngredientPentosan, -1	},
	{	"<td>Hexosan</td>",								cIngredient::iIngredientHexosan, -1	},
	{	"<td>Cellulose</td>",							cIngredient::iIngredientCellulose, -1	},
	{	"<td>Polyuronsäure</td>",						cIngredient::iIngredientPolyuronicacid, -1	},
	{	"<td>Mannit</td>",								cIngredient::iIngredientMannitol, -1	},
	{	"<td>Xylit</td>",								cIngredient::iIngredientXylitol, -1	},
	{	"<td>sonst. Zuckeralkohole</td>",				cIngredient::iIngredientothersugaralcohols, -1	},
	{	"<td>Summe Zuckeralkohole</td>",				cIngredient::iIngredientTotalsugaralcohols, -1	},
	{	"<td>sonst. Monosaccharide</td>",				cIngredient::iIngredientothermonosaccharides, -1	},
	{	"<td>Monosaccharide</td>",						cIngredient::iIngredientMonosaccharides, -1	},
	{	"<td>sonst. Disaccharide</td>",					cIngredient::iIngredientotherdisaccharides, -1	},
	{	"<td>Disaccharide</td>",						cIngredient::iIngredientDisaccharides, -1	},
	{	"<td>Oligosaccharide resorb.</td>",				cIngredient::iIngredientOligosaccharidesresorb, -1	},
	{	"<td>Oligosaccharide n. resorb.</td>",			cIngredient::iIngredientOligosaccharidesnonresorb, -1	},
	{	"<td>sonst. Polysaccharide</td>",				cIngredient::iIngredientotherpolysaccharides, -1	},
	{	"<td>Polysaccharide</td>",						cIngredient::iIngredientPolysaccharides, -1	},

	{	"<td>Ballaststoffe wasserl.</td>",				cIngredient::iIngredientDietaryfibrewatersoluble, -1	},
	{	"<td>Ballaststoffe w.unlösl.</td>",				cIngredient::iIngredientDietaryfibrewaterinsoluble, -1	},
	{	"<td>Lignin</td>",								cIngredient::iIngredientLignin, -1	},
	{	"<td>Purinbasen-Stickstoff</td>",				cIngredient::iIngredientPurinebasesnitrogen, -1	},
	{	"<td>Kochsalz</td>",							cIngredient::iIngredientSodiumchloride, -1	},
	{	"<td>Küchenabfälle</td>",						cIngredient::iIngredientWaste, -1	},
	{	"<td>sonst. Eiweißstoffe</td>",					cIngredient::iIngredientotherproteins, -1	},
	{	"<td>tierisches Eiweiß</td>",					cIngredient::iIngredientanimalprotein, -1	},
	{	"<td>pflanzliches Eiweiß</td>",					cIngredient::iIngredientplantprotein, -1	},
	{	"<td>Harnsäure</td>",							cIngredient::iIngredientUricacid, -1	},
	{	"<td>sonst. organischen Säuren</td>",			cIngredient::iIngredientotherorganicacids, -1	},
	{	"<td>Mol-Diff. Kationen-Anionen</td>",			cIngredient::iIngredientMol_diff_cations_anions, -1	},
	{	"<td>Stickstoffaktor</td>",						cIngredient::iIngredientNitrogenfactor, -1	},
	{	"<td>Fettsäurenanteil</td>",					cIngredient::iIngredientFattyacidpart, -1	},
	{	"<td>Mineralstoffanteil</td>",					cIngredient::iIngredientMineralspart, -1	},
	{	"<td>P/S Verhältnis</td>",						cIngredient::iIngredientPS_Ratio, -1	},
	{	"<td>Biolog. Wertigkeit</td>",					cIngredient::iIngredientBiologicalvalue, -1	},
	{	"<td>fruktosefreie Broteinheiten</td>",			cIngredient::iIngredientFructosefreebreadunits, -1	},
	{	"<td>durchschn. Verzehr</td>",					cIngredient::iIngredientaverageconsumption, -1	},
};

QMap<QString, QString> cErnaehrungPlugin::detailsCapability()
{
	QMap<QString, QString>	map;
	map.insert("alle", "egal");
	map.insert("Bundeslebensmittelschlüssel", "bls");
	map.insert("Firmenprodukte", "produkte");
	return(map);
}

//http://www.ernaehrung.de/lebensmittel/suche/&nameInput=Milch&origin=egal&language=de
//Origin: egal, bls (Bundeslebensmittelschlüssel), produkte (Firmenprodukte)
QStringList cErnaehrungPlugin::search(const QString& szSearch, const QString& szDetails)
{
	m_szUrls.clear();
	m_szIngredients.clear();

	QNetworkAccessManager	networkManager;
	QUrlQuery				postData;

	postData.addQueryItem("nameInput", szSearch);
	if(szDetails.length())
		postData.addQueryItem("origin", szDetails);
	else
		postData.addQueryItem("origin", "egal");
	postData.addQueryItem("language", "de");

	QNetworkRequest			request(QUrl("http://www.ernaehrung.de/lebensmittel/suche/"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QNetworkReply*			reply   = networkManager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QByteArray				szData  = reply->readAll();
	delete reply;

	QList<QByteArray>		szList  = szData.split('\n');
	int						z;

	for(z = 0;z < szList.count();z++)
	{
		QString szLine  = QString::fromUtf8(szList.at(z));
		if(szLine.contains("Suchergebnisse"))
			break;
	}

	for(;z < szList.count();z++)
	{
		QString szLine  = QString::fromUtf8(szList.at(z));
		if(szLine.contains("<a href=\"http://www.ernaehrung.de/lebensmittel"))
		{
			QString	szReply;
			QString	szURL;

			szURL	= szLine.mid(szLine.indexOf("<a href")+9);
			szURL	= szURL.left(szURL.indexOf("\""));

			szReply	= szLine.mid(szLine.indexOf("\">")+2);
			szReply	= szReply.left(szReply.indexOf("<"));
			m_szIngredients.append(szReply);
			m_szUrls.append(szURL);
		}
	}
	return(m_szIngredients);
}

double toValue(const QString& sz)
{
	QString szTmp;
	szTmp = sz.mid(sz.indexOf("\">")+2);
	szTmp = szTmp.left(szTmp.indexOf("<"));
	szTmp.replace(",", ".");
	return(szTmp.toDouble());
}

bool cErnaehrungPlugin::load(qint16 iIndex)
{
	m_bLoaded	= false;
	if(iIndex > m_szUrls.count()-1)
		return(false);

	QNetworkAccessManager	networkManager;

	QNetworkRequest			request(QUrl(m_szUrls.at(iIndex)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QByteArray				szData  = reply->readAll();
	delete reply;

	QList<QByteArray>		szList;
	QString					szName;
	qreal					dFactor;

	for(int i = 0;i < (int)sizeof(g_values)/(int)sizeof(VALUES);i++)
		g_values[i].dValue	= -1;

	if(szData.length())
	{
		szList	= szData.split('\n');

		for(int z = 0;z < szList.count();z++)
		{
			if(szList.at(z).contains("<div id=\"contentHeader\"><h1>"))
			{
				szName	= szList.at(z).mid(szList.at(z).indexOf("<h1>")+4);
				szName	= szName.left(szName.indexOf("</h1>"));
			}
			else
			{
				//QString	szL0	= QString::fromUtf8(szList.at(z));
				QString	szL0	= szList.at(z);

				for(int i = 0;i < (int)sizeof(g_values)/(int)sizeof(VALUES);i++)
				{
					//QString	szL1	= g_values[i].szSearch;
					//bool x = szL0.contains(szL1);
					//x = false;
					if(szL0.contains(g_values[i].szSearch))
					{
						dFactor	= 1;
						QString	szL1	= QString::fromUtf8(szList.at(z+1));
						QString	szL2	= QString::fromUtf8(szList.at(z+2));

						if(szL2.contains(">g<"))
							dFactor	= 1;
						else if(szL2.contains(">mg<"))
							dFactor	= 1000;
						else if(szL2.contains(QString::fromUtf8(">µg<")))
							dFactor	= 1000000;

						g_values[i].dValue	= toValue(szL1)/dFactor;
						break;
					}
				}
			}
		}

	}

	m_bLoaded		= true;
	m_iLoadedIndex	= iIndex;
	return(true);
}

qreal cErnaehrungPlugin::value(cIngredient::iIngredient i)
{
	if(m_bLoaded)
	{
		for(int z = 0;z < (int)sizeof(g_values)/(int)sizeof(VALUES);z++)
		{
			if(g_values[z].iIngredient == i)
				return(g_values[z].dValue);
		}
	}
	return(-1);
}

QString cErnaehrungPlugin::ingredientName()
{
	if(m_bLoaded)
		return(m_szIngredients.at(m_iLoadedIndex));
	else
		return(QString(""));
}

bool cErnaehrungPlugin::config()
{
	return(true);
}

QString cErnaehrungPlugin::author()
{
	return("Herwig Birke");
}

QString cErnaehrungPlugin::company()
{
	return("WIN-DESIGN");
}

QString cErnaehrungPlugin::link()
{
	return("http://www.windesign.at");
}

QString cErnaehrungPlugin::description()
{
	return("This is the description.");
}

QString cErnaehrungPlugin::copyright()
{
	return("This is the copyright.");
}
