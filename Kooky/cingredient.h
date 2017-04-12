/**
  * \class cIngredient
  *
  * \brief This class holds data of an ingredient.
  *
  * \ingroup KOOKY
  *
  * This class holds data of an ingredient.
  *
  * \note
  *
  * \author Herwig Birke
  *
  * \version 1.0
  *
  * \date 2016/02/09
  */

#ifndef CINGREDIENT_H
#define CINGREDIENT_H


#include <QDate>
#include <QString>
#include <QStringList>


class cPlugin;

/*!
 \brief

*/
class cIngredient
{
public:
	/*!
	 \brief

	*/
	enum iIngredient
	{
		iIngredientBreadUnits						= 0,
		iIngredientCalories							= 1,
		iIngredientProtein							= 2,
		iIngredientFat								= 3,
		iIngredientCarbohydrates					= 4,
		iIngredientAlcohol							= 5,
		iIngredientWater							= 6,
		iIngredientTotalDietaryFibre				= 7,
		iIngredientCholesterol						= 8,
		iIngredientMineral							= 9,
		iIngredientVitaminARetinol					= 10,
		iIngredientVitaminD							= 11,
		iIngredientVitaminEactiv					= 12,
		iIngredientFolicacid						= 13,
		iIngredientVitaminB1						= 14,
		iIngredientVitaminB2						= 15,
		iIngredientVitaminB6						= 16,
		iIngredientVitaminC							= 17,
		iIngredientaTocopherol						= 18,
		iIngredientVitaminK							= 19,
		iIngredientNicotinamide						= 20,
		iIngredientPantothenicacid					= 21,
		iIngredientBiotin							= 22,
		iIngredientVitaminB12						= 23,
		iIngredientRetinolequivalent				= 24,
		iIngredientbCarotene						= 25,
		iIngredientNiacinequivalent					= 26,
		iIngredientfreefolicacidequivalent			= 27,
		iIngredientfreefolicacid					= 28,
		iIngredientSodium							= 29,
		iIngredientPotassium						= 30,
		iIngredientMagnesium						= 31,
		iIngredientCalcium							= 32,
		iIngredientIron								= 33,
		iIngredientPhosphorus						= 34,
		iIngredientCopper							= 35,
		iIngredientZinc								= 36,
		iIngredientChloride							= 37,
		iIngredientFluoride							= 38,
		iIngredientIodide							= 39,
		iIngredientSelenium							= 40,
		iIngredientManganese						= 41,
		iIngredientSulphur							= 42,
		iIngredientArginine							= 43,
		iIngredientCystine							= 44,
		iIngredientHistidine						= 45,
		iIngredientIsoleucine						= 46,
		iIngredientLeucine							= 47,
		iIngredientLysine							= 48,
		iIngredientMethionine						= 49,
		iIngredientPhenylalanine					= 50,
		iIngredientThreonine						= 51,
		iIngredientTryptophane						= 52,
		iIngredientTyrosine							= 53,
		iIngredientValine							= 54,
		iIngredientAlanine							= 55,
		iIngredientAsparticacid						= 56,
		iIngredientGlutamicacid						= 57,
		iIngredientGlycine							= 58,
		iIngredientProline							= 59,
		iIngredientSerine							= 60,
		iIngredientotheressent_aminoacids			= 61,
		iIngredientessent_aminoacids				= 62,
		iIngredientothernonessent_aminoacids		= 63,
		iIngredientnonessent_aminoacids				= 64,
		iIngredientSaturatedfattyacids				= 65,
		iIngredientMonounsaturatedfattyacids		= 66,
		iIngredientPolyunsaturatedfattyacids		= 67,
		iIngredientButyricacid						= 68,
		iIngredientCaproicacid						= 69,
		iIngredientCaprylicacid						= 70,
		iIngredientCapricacid						= 71,
		iIngredientLauricacid						= 72,
		iIngredientMyristicacid						= 73,
		iIngredientC15_O_fattyacid					= 74,
		iIngredientPalmiticacid						= 75,
		iIngredientMargaricacid						= 76,
		iIngredientStearicacid						= 77,
		iIngredientArachicacid						= 78,
		iIngredientBehenicacid						= 79,
		iIngredientLignocericacid					= 80,
		iIngredientPalmitoleicacid					= 81,
		iIngredientOleicacid						= 82,
		iIngredientEicosenicacid					= 83,
		iIngredientC22_1_fattyacid					= 84,
		iIngredientC14_1_fattyacid					= 85,
		iIngredientC24_1_fattyacid					= 86,
		iIngredientLinoleicacid						= 87,
		iIngredientLinolenicacid					= 88,
		iIngredientArachidonicacid					= 89,
		iIngredientC18_4_fattyacid					= 90,
		iIngredientC20_5_N_3fattyacid				= 91,
		iIngredientC22_5_N_3fattyacid				= 92,
		iIngredientC22_6_N_3fattyacid				= 93,
		iIngredientC16_2_fattyacid					= 94,
		iIngredientothersaturatedfattyacids			= 95,
		iIngredientothermonounsaturatedfattyacids	= 96,
		iIngredientNonadecatrienicacid				= 97,
		iIngredientEicosadienicacid					= 98,
		iIngredientEicosatrienicacid				= 99,
		iIngredientDocosadienicacid					= 100,
		iIngredientDocosatrienicacid				= 101,
		iIngredientDocosatetraenicacid				= 102,
		iIngredientotherpolyunsat_fattyacids		= 103,
		iIngredientothershort_chainfattyacids		= 104,
		iIngredientshort_chainfattyacids			= 105,
		iIngredientothermedium_chainfattyacids		= 106,
		iIngredientmedium_chainfattyacids			= 107,
		iIngredientotherlong_chainfattyacids		= 108,
		iIngredientlong_chainfattyacids				= 109,
		iIngredientGlycerolandLipoides				= 110,
		iIngredientSorbitol							= 111,
		iIngredientGlucose							= 112,
		iIngredientFructose							= 113,
		iIngredientSucrose							= 114,
		iIngredientLactose							= 115,
		iIngredientStarch							= 116,
		iIngredientMaltose							= 117,
		iIngredientGalactose						= 118,
		iIngredientGlycogene						= 119,
		iIngredientPentosan							= 120,
		iIngredientHexosan							= 121,
		iIngredientCellulose						= 122,
		iIngredientPolyuronicacid					= 123,
		iIngredientMannitol							= 124,
		iIngredientXylitol							= 125,
		iIngredientothersugaralcohols				= 126,
		iIngredientTotalsugaralcohols				= 127,
		iIngredientothermonosaccharides				= 128,
		iIngredientMonosaccharides					= 129,
		iIngredientotherdisaccharides				= 130,
		iIngredientDisaccharides					= 131,
		iIngredientOligosaccharidesresorb			= 132,
		iIngredientOligosaccharidesnonresorb		= 133,
		iIngredientotherpolysaccharides				= 134,
		iIngredientPolysaccharides					= 135,
		iIngredientDietaryfibrewatersoluble			= 136,
		iIngredientDietaryfibrewaterinsoluble		= 137,
		iIngredientLignin							= 138,
		iIngredientPurinebasesnitrogen				= 139,
		iIngredientSodiumchloride					= 140,
		iIngredientWaste							= 141,
		iIngredientotherproteins					= 142,
		iIngredientanimalprotein					= 143,
		iIngredientplantprotein						= 144,
		iIngredientUricacid							= 145,
		iIngredientotherorganicacids				= 146,
		iIngredientMol_diff_cations_anions			= 147,
		iIngredientNitrogenfactor					= 148,
		iIngredientFattyacidpart					= 149,
		iIngredientMineralspart						= 150,
		iIngredientPS_Ratio							= 151,
		iIngredientBiologicalvalue					= 152,
		iIngredientFructosefreebreadunits			= 153,
		iIngredientaverageconsumption				= 154,
		iIngredientSugar							= 155,
		iIngredientAspartid							= 156,
		iIngredientGlutamid							= 157,
		iIngredientMax,
	};

	/*!
	 \brief

	*/
	enum UNIT
	{
		UNIT_None		= 0,
		UNIT_Weight		= 1,
		UNIT_Volume		= 2,
		UNIT_Fluid		= 3,
		UNIT_Peace		= 4,
		UNIT_Calories	= 5,
		UNIT_Joule		= 6,
	};

	cIngredient();
	/*!
	 \brief

	 \param szIngredientName
	 \param szIngredientGroup
	*/
	cIngredient(const QString& szIngredientName, const QString& szIngredientGroup);

	/*!
	 \brief

	 \param i
	 \param dValue
	*/
	void	setValue(cIngredient::iIngredient i, qreal dValue);
	/*!
	 \brief

	 \param i
	 \return qreal
	*/
	qreal	value(cIngredient::iIngredient i);
	/*!
	 \brief

	 \param i
	 \return QString
	*/
	QString	valueFormatted(cIngredient::iIngredient i);
	/*!
	 \brief

	 \param i
	 \return UNIT
	*/
	UNIT	unit(cIngredient::iIngredient i);
	/*!
	 \brief

	 \return bool
	*/
	bool	load(qint32 iIngredient, cPlugin* lpDB);
	/*!
	 \brief

	 \return bool
	*/
	bool	reload(cPlugin* lpDB);
	/*!
	 \brief

	 \return bool
	*/
	bool	save(cPlugin* lpDB);

	qint32	ingredientID();
	/*!
	 \brief

	 \param szIngredientName
	*/
	void	setIngredientName(const QString& szIngredientName);
	/*!
	 \brief

	 \return QString
	*/
	QString	ingredientName();
	/*!
	 \brief

	 \param szIngredientGroup
	*/
	void	setIngredientGroup(const QString& szIngredientGroup);
	/*!
	 \brief

	 \return QString
	*/
	QString	ingredientGroup();
	/*!
	 \brief

	 \return QStringList
	*/
	QStringList	groups();
	/*!
	 \brief

	 \param i
	 \return QString
	*/
	static QString	group(cIngredient::iIngredient i);
	/*!
	 \brief

	 \param i
	 \return QString
	*/
	static QString	name(cIngredient::iIngredient i);

	void			operator=(const cIngredient& D)
	{
		m_szIngredientName	= D.m_szIngredientName;
		m_szIngredientGroup	= D.m_szIngredientGroup;
		m_iID				= D.m_iID;
		for(int z = 0;z < iIngredientMax;z++)
			m_dValue[z]	= D.m_dValue[z];
	}

	/*!
	 \brief

	 \param D
	 \return bool operator
	*/
	bool			operator==(const cIngredient& D)
	{
		if(m_szIngredientName != D.m_szIngredientName)
			return(false);

		if(m_szIngredientGroup != D.m_szIngredientGroup)
			return(false);

		if(m_iID != D.m_iID)
			return(false);

		for(int z = 0;z < iIngredientMax;z++)
		{
			if(m_dValue[z] != D.m_dValue[z])
				return(false);
		}
		return(true);
	}

	/*!
	 \brief

	 \param D
	 \return bool operator
	*/
	bool			operator!=(const cIngredient& D)
	{
		return(!(*this == D));
	}

private:
	QString		m_szIngredientName; /*!< TODO: describe */
	QString		m_szIngredientGroup; /*!< TODO: describe */
	qint32		m_iID; /*!< TODO: describe */
	qreal		m_dValue[iIngredientMax]; /*!< TODO: describe */
};

#endif // CINGREDIENT_H
