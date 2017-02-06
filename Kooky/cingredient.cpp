#include "cingredient.h"
#include "cplugin.h"


typedef struct tagGROUPNAME
{
	QString						szName;
	QString						szGroup;
	cIngredient::iIngredient	iIngredient;
}	GROUPNAME;

static GROUPNAME			g_groupname[] =
{
	{	QString::fromUtf8("Bread Units"),						QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientBreadUnits	},
	{	QString::fromUtf8("Calories"),							QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientCalories	},
	{	QString::fromUtf8("Joule"),								QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientJoule		},
	{	QString::fromUtf8("Bread Units"),						QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientBreadUnits	},
	{	QString::fromUtf8("Calories"),							QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientCalories	},
	{	QString::fromUtf8("Protein"),							QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientProtein	},
	{	QString::fromUtf8("Fat"),								QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientFat	},
	{	QString::fromUtf8("Carbohydrates"),						QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientCarbohydrates	},
	{	QString::fromUtf8("Alcohol"),							QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientAlcohol	},
	{	QString::fromUtf8("Water"),								QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientWater	},
	{	QString::fromUtf8("Total Dietary Fibre"),				QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientTotalDietaryFibre	},
	{	QString::fromUtf8("Cholesterol"),						QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientCholesterol	},
	{	QString::fromUtf8("Mineral"),							QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientMineral	},
	{	QString::fromUtf8("Sugar"),								QString::fromUtf8("Main Ingredients"),				cIngredient::iIngredientSugar	},

	{	QString::fromUtf8("Vitamin A Retinol"),					QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminARetinol	},
	{	QString::fromUtf8("Vitamin D"),							QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminD	},
	{	QString::fromUtf8("Vitamin E activ."),					QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminEactiv	},
	{	QString::fromUtf8("Folic acid"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientFolicacid	},
	{	QString::fromUtf8("Vitamin B1"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminB1	},
	{	QString::fromUtf8("Vitamin B2"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminB2	},
	{	QString::fromUtf8("Vitamin B6"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminB6	},
	{	QString::fromUtf8("Vitamin C"),							QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminC	},
	{	QString::fromUtf8("a-Tocopherol"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientaTocopherol	},
	{	QString::fromUtf8("Vitamin K"),							QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminK	},
	{	QString::fromUtf8("Nicotinamide"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientNicotinamide	},
	{	QString::fromUtf8("Pantothenic acid"),					QString::fromUtf8("Vitamins"),						cIngredient::iIngredientPantothenicacid	},
	{	QString::fromUtf8("Biotin"),							QString::fromUtf8("Vitamins"),						cIngredient::iIngredientBiotin	},
	{	QString::fromUtf8("Vitamin B12"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientVitaminB12	},
	{	QString::fromUtf8("Retinolequivalent"),					QString::fromUtf8("Vitamins"),						cIngredient::iIngredientRetinolequivalent	},
	{	QString::fromUtf8("ß-Carotene"),						QString::fromUtf8("Vitamins"),						cIngredient::iIngredientbCarotene	},
	{	QString::fromUtf8("Niacinequivalent"),					QString::fromUtf8("Vitamins"),						cIngredient::iIngredientNiacinequivalent	},
	{	QString::fromUtf8("free folic acid equivalent"),		QString::fromUtf8("Vitamins"),						cIngredient::iIngredientfreefolicacidequivalent	},
	{	QString::fromUtf8("free folic acid"),					QString::fromUtf8("Vitamins"),						cIngredient::iIngredientfreefolicacid	},

	{	QString::fromUtf8("Sodium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientSodium	},
	{	QString::fromUtf8("Potassium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientPotassium	},
	{	QString::fromUtf8("Magnesium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientMagnesium	},
	{	QString::fromUtf8("Calcium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientCalcium	},
	{	QString::fromUtf8("Iron"),								QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientIron	},
	{	QString::fromUtf8("Phosphorus"),						QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientPhosphorus	},
	{	QString::fromUtf8("Copper"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientCopper	},
	{	QString::fromUtf8("Zinc"),								QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientZinc	},
	{	QString::fromUtf8("Chloride"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientChloride	},
	{	QString::fromUtf8("Fluoride"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientFluoride	},
	{	QString::fromUtf8("Iodide"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientIodide	},
	{	QString::fromUtf8("Selenium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientSelenium	},
	{	QString::fromUtf8("Manganese"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientManganese	},
	{	QString::fromUtf8("Sulphur"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::iIngredientSulphur	},

	{	QString::fromUtf8("Arginine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientArginine	},
	{	QString::fromUtf8("Cystine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientCystine	},
	{	QString::fromUtf8("Histidine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientHistidine	},
	{	QString::fromUtf8("Isoleucine"),						QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientIsoleucine	},
	{	QString::fromUtf8("Leucine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientLeucine	},
	{	QString::fromUtf8("Lysine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientLysine	},
	{	QString::fromUtf8("Methionine"),						QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientMethionine	},
	{	QString::fromUtf8("Phenylalanine"),						QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientPhenylalanine	},
	{	QString::fromUtf8("Threonine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientThreonine	},
	{	QString::fromUtf8("Tryptophane"),						QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientTryptophane	},
	{	QString::fromUtf8("Tyrosine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientTyrosine	},
	{	QString::fromUtf8("Valine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientValine	},
	{	QString::fromUtf8("Alanine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientAlanine	},
	{	QString::fromUtf8("Aspartic"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientAspartid	},
	{	QString::fromUtf8("Aspartic acid"),						QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientAsparticacid	},
	{	QString::fromUtf8("Glutamic"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientGlutamid	},
	{	QString::fromUtf8("Glutamic acid"),						QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientGlutamicacid	},
	{	QString::fromUtf8("Glycine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientGlycine	},
	{	QString::fromUtf8("Proline"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientProline	},
	{	QString::fromUtf8("Serine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientSerine	},
	{	QString::fromUtf8("other essent. amino acids"),			QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientotheressent_aminoacids	},
	{	QString::fromUtf8("essent. amino acids"),				QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientessent_aminoacids	},
	{	QString::fromUtf8("other nonessent. amino acids"),		QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientothernonessent_aminoacids	},
	{	QString::fromUtf8("nonessent. amino acids"),			QString::fromUtf8("Aminos Acids"),					cIngredient::iIngredientnonessent_aminoacids	},

	{	QString::fromUtf8("Saturated fatty acids"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientSaturatedfattyacids	},
	{	QString::fromUtf8("Monounsaturated fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientMonounsaturatedfattyacids	},
	{	QString::fromUtf8("Polyunsaturated fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientPolyunsaturatedfattyacids	},
	{	QString::fromUtf8("Butyric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientButyricacid	},
	{	QString::fromUtf8("Caproic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientCaproicacid	},
	{	QString::fromUtf8("Caprylic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientCaprylicacid	},
	{	QString::fromUtf8("Capric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientCapricacid	},
	{	QString::fromUtf8("Lauric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientLauricacid	},
	{	QString::fromUtf8("Myristic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientMyristicacid	},
	{	QString::fromUtf8("C15:O fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC15_O_fattyacid	},
	{	QString::fromUtf8("Palmitic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientPalmiticacid	},
	{	QString::fromUtf8("Margaric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientMargaricacid	},
	{	QString::fromUtf8("Stearic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientStearicacid	},
	{	QString::fromUtf8("Arachic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientArachicacid	},
	{	QString::fromUtf8("Behenic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientBehenicacid	},
	{	QString::fromUtf8("Lignoceric acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientLignocericacid	},
	{	QString::fromUtf8("Palmitoleic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientPalmitoleicacid	},
	{	QString::fromUtf8("Oleic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientOleicacid	},
	{	QString::fromUtf8("Eicosenic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientEicosenicacid	},
	{	QString::fromUtf8("C22:1 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC22_1_fattyacid	},
	{	QString::fromUtf8("C14:1 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC14_1_fattyacid	},
	{	QString::fromUtf8("C24:1 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC24_1_fattyacid	},
	{	QString::fromUtf8("Linoleic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientLinoleicacid	},
	{	QString::fromUtf8("Linolenic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientLinolenicacid	},
	{	QString::fromUtf8("Arachidonic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientArachidonicacid	},
	{	QString::fromUtf8("C18:4 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC18_4_fattyacid	},
	{	QString::fromUtf8("C20:5 N-3 fatty acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC20_5_N_3fattyacid	},
	{	QString::fromUtf8("C22:5 N-3 fatty acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC22_5_N_3fattyacid	},
	{	QString::fromUtf8("C22:6 N-3 fatty acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC22_6_N_3fattyacid	},
	{	QString::fromUtf8("C16:2 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientC16_2_fattyacid	},
	{	QString::fromUtf8("other saturated fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientothersaturatedfattyacids	},
	{	QString::fromUtf8("other monounsaturated fatty acids"),	QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientothermonounsaturatedfattyacids	},
	{	QString::fromUtf8("Nonadecatrienic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientNonadecatrienicacid	},
	{	QString::fromUtf8("Eicosadienic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientEicosadienicacid	},
	{	QString::fromUtf8("Eicosatrienic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientEicosatrienicacid	},
	{	QString::fromUtf8("Docosadienic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientDocosadienicacid	},
	{	QString::fromUtf8("Docosatrienic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientDocosatrienicacid	},
	{	QString::fromUtf8("Docosatetraenic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientDocosatetraenicacid	},
	{	QString::fromUtf8("other polyunsat. fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientotherpolyunsat_fattyacids	},
	{	QString::fromUtf8("other short-chain fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientothershort_chainfattyacids	},
	{	QString::fromUtf8("short-chain fatty acids"),			QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientshort_chainfattyacids	},
	{	QString::fromUtf8("other medium-chain fatty acids"),	QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientothermedium_chainfattyacids	},
	{	QString::fromUtf8("medium-chain fatty acids"),			QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientmedium_chainfattyacids	},
	{	QString::fromUtf8("other long-chain fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientotherlong_chainfattyacids	},
	{	QString::fromUtf8("long-chain fatty acids"),			QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientlong_chainfattyacids	},
	{	QString::fromUtf8("Glycerol and Lipoides"),				QString::fromUtf8("Fatty Acids"),					cIngredient::iIngredientGlycerolandLipoides	},

	{	QString::fromUtf8("Sorbitol"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientSorbitol	},
	{	QString::fromUtf8("Glucose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientGlucose	},
	{	QString::fromUtf8("Fructose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientFructose	},
	{	QString::fromUtf8("Sucrose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientSucrose	},
	{	QString::fromUtf8("Lactose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientLactose	},
	{	QString::fromUtf8("Starch"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientStarch	},
	{	QString::fromUtf8("Maltose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientMaltose	},
	{	QString::fromUtf8("Galactose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientGalactose	},
	{	QString::fromUtf8("Glycogene"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientGlycogene	},
	{	QString::fromUtf8("Pentosan"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientPentosan	},
	{	QString::fromUtf8("Hexosan"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientHexosan	},
	{	QString::fromUtf8("Cellulose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientCellulose	},
	{	QString::fromUtf8("Polyuronic acid"),					QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientPolyuronicacid	},
	{	QString::fromUtf8("Mannitol"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientMannitol	},
	{	QString::fromUtf8("Xylitol"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientXylitol	},
	{	QString::fromUtf8("other sugar alcohols"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientothersugaralcohols	},
	{	QString::fromUtf8("Total sugar alcohols"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientTotalsugaralcohols	},
	{	QString::fromUtf8("other monosaccharides"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientothermonosaccharides	},
	{	QString::fromUtf8("Monosaccharides"),					QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientMonosaccharides	},
	{	QString::fromUtf8("other disaccharides"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientotherdisaccharides	},
	{	QString::fromUtf8("Disaccharides"),						QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientDisaccharides	},
	{	QString::fromUtf8("Oligosaccharides resorb."),			QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientOligosaccharidesresorb	},
	{	QString::fromUtf8("Oligosaccharides nonresorb."),		QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientOligosaccharidesnonresorb	},
	{	QString::fromUtf8("other polysaccharides"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientotherpolysaccharides	},
	{	QString::fromUtf8("Polysaccharides"),					QString::fromUtf8("Special Carbohydrates"),			cIngredient::iIngredientPolysaccharides	},

	{	QString::fromUtf8("Dietary fibre water soluble"),		QString::fromUtf8("Others"),						cIngredient::iIngredientDietaryfibrewatersoluble	},
	{	QString::fromUtf8("Dietary fibre water insoluble"),		QString::fromUtf8("Others"),						cIngredient::iIngredientDietaryfibrewaterinsoluble	},
	{	QString::fromUtf8("Lignin"),							QString::fromUtf8("Others"),						cIngredient::iIngredientLignin	},
	{	QString::fromUtf8("Purine bases nitrogen"),				QString::fromUtf8("Others"),						cIngredient::iIngredientPurinebasesnitrogen	},
	{	QString::fromUtf8("Sodium chloride"),					QString::fromUtf8("Others"),						cIngredient::iIngredientSodiumchloride	},
	{	QString::fromUtf8("Waste"),								QString::fromUtf8("Others"),						cIngredient::iIngredientWaste	},
	{	QString::fromUtf8("other proteins"),					QString::fromUtf8("Others"),						cIngredient::iIngredientotherproteins	},
	{	QString::fromUtf8("animal protein"),					QString::fromUtf8("Others"),						cIngredient::iIngredientanimalprotein	},
	{	QString::fromUtf8("plant protein"),						QString::fromUtf8("Others"),						cIngredient::iIngredientplantprotein	},
	{	QString::fromUtf8("Uric acid"),							QString::fromUtf8("Others"),						cIngredient::iIngredientUricacid	},
	{	QString::fromUtf8("other organic acids"),				QString::fromUtf8("Others"),						cIngredient::iIngredientotherorganicacids	},
	{	QString::fromUtf8("Mol-diff. cations-anions"),			QString::fromUtf8("Others"),						cIngredient::iIngredientMol_diff_cations_anions	},
	{	QString::fromUtf8("Nitrogen factor"),					QString::fromUtf8("Others"),						cIngredient::iIngredientNitrogenfactor	},
	{	QString::fromUtf8("Fatty acid part"),					QString::fromUtf8("Others"),						cIngredient::iIngredientFattyacidpart	},
	{	QString::fromUtf8("Minerals part"),						QString::fromUtf8("Others"),						cIngredient::iIngredientMineralspart	},
	{	QString::fromUtf8("P/S Ratio"),							QString::fromUtf8("Others"),						cIngredient::iIngredientPS_Ratio	},
	{	QString::fromUtf8("Biological value"),					QString::fromUtf8("Others"),						cIngredient::iIngredientBiologicalvalue	},
	{	QString::fromUtf8("Fructose free bread units"),			QString::fromUtf8("Others"),						cIngredient::iIngredientFructosefreebreadunits	},
	{	QString::fromUtf8("average consumption"),				QString::fromUtf8("Others"),						cIngredient::iIngredientaverageconsumption	},
};

cIngredient::cIngredient() :
	m_szIngredientName(""),
	m_szIngredientGroup(""),
	m_iID(-1)
{
}

cIngredient::cIngredient(const QString &szIngredientName, const QString& szIngredientGroup) :
	m_szIngredientName(szIngredientName),
	m_szIngredientGroup(szIngredientGroup),
	m_iID(0)
{
	for(int z = 0;z < iIngredientMax;z++)
		m_dValue[z] = -1;
}

bool cIngredient::load(qint32 iIngredient, cPlugin* lpDB)
{
	if(!lpDB)
		return(false);

	cDBInterface*	lpInterface	= lpDB->dbInterface();

	m_iID				= iIngredient;
	m_szIngredientName	= lpInterface->name(iIngredient);
	m_szIngredientGroup	= lpInterface->group(iIngredient);

	for(int z = 0;z < cIngredient::iIngredientMax;z++)
		m_dValue[z]	= lpInterface->get(iIngredient, z);

	return(true);
}

bool cIngredient::reload(cPlugin* /*lpDB*/)
{
	return(true);
}

bool cIngredient::save(cPlugin* lpDB)
{
	if(!lpDB)
		return(false);

	cDBInterface*	lpInterface	= lpDB->dbInterface();

	lpInterface->beginTransaction();

	qint32	id	= lpInterface->create(m_szIngredientName, m_szIngredientGroup);
	if(id == -1)
		return(false);

	for(int z = 0;z < cIngredient::iIngredientMax;z++)
	{
		if(m_dValue[z] != -1)
		{
			if(!lpInterface->set(id, z, m_dValue[z]))
				return(false);
		}
	}

	lpInterface->endTransaction();

	return(true);
}

QString cIngredient::ingredientName()
{
	return(m_szIngredientName);
}

QString cIngredient::ingredientGroup()
{
	return(m_szIngredientGroup);
}

QString cIngredient::group(cIngredient::iIngredient i)
{
	for(int z = 0;z < (int)sizeof(g_groupname)/(int)sizeof(GROUPNAME);z++)
	{
		if(g_groupname[z].iIngredient == i)
			return(g_groupname[z].szGroup);
	}
	return("unknown");
}


QString cIngredient::name(cIngredient::iIngredient i)
{
	for(int z = 0;z < (int)sizeof(g_groupname)/(int)sizeof(GROUPNAME);z++)
	{
		if(g_groupname[z].iIngredient == i)
			return(g_groupname[z].szName);
	}
	return("unknown");
}

void cIngredient::setValue(cIngredient::iIngredient i, qreal dValue)
{
	m_dValue[i]	= dValue;
}
