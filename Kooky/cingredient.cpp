#include "cingredient.h"
#include "cplugin.h"


typedef struct tagGROUPNAME
{
	QString						szName;
	QString						szGroup;
	cIngredient::UNIT			unit;
	cIngredient::iIngredient	iIngredient;
}	GROUPNAME;

static GROUPNAME			g_groupname[] =
{
	{	QString::fromUtf8("Bread Units"),						QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_None,		cIngredient::iIngredientBreadUnits	},
	{	QString::fromUtf8("Calories"),							QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Calories,	cIngredient::iIngredientCalories	},
	{	QString::fromUtf8("Protein"),							QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientProtein	},
	{	QString::fromUtf8("Fat"),								QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientFat	},
	{	QString::fromUtf8("Carbohydrates"),						QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientCarbohydrates	},
	{	QString::fromUtf8("Alcohol"),							QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientAlcohol	},
	{	QString::fromUtf8("Water"),								QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientWater	},
	{	QString::fromUtf8("Total Dietary Fibre"),				QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientTotalDietaryFibre	},
	{	QString::fromUtf8("Cholesterol"),						QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientCholesterol	},
	{	QString::fromUtf8("Mineral"),							QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientMineral	},
	{	QString::fromUtf8("Sugar"),								QString::fromUtf8("Main Ingredients"),				cIngredient::UNIT_Weight,	cIngredient::iIngredientSugar	},

	{	QString::fromUtf8("Vitamin A Retinol"),					QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminARetinol	},
	{	QString::fromUtf8("Vitamin D"),							QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminD	},
	{	QString::fromUtf8("Vitamin E activ."),					QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminEactiv	},
	{	QString::fromUtf8("Folic acid"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientFolicacid	},
	{	QString::fromUtf8("Vitamin B1"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminB1	},
	{	QString::fromUtf8("Vitamin B2"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminB2	},
	{	QString::fromUtf8("Vitamin B6"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminB6	},
	{	QString::fromUtf8("Vitamin C"),							QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminC	},
	{	QString::fromUtf8("a-Tocopherol"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientaTocopherol	},
	{	QString::fromUtf8("Vitamin K"),							QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminK	},
	{	QString::fromUtf8("Nicotinamide"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientNicotinamide	},
	{	QString::fromUtf8("Pantothenic acid"),					QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientPantothenicacid	},
	{	QString::fromUtf8("Biotin"),							QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientBiotin	},
	{	QString::fromUtf8("Vitamin B12"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientVitaminB12	},
	{	QString::fromUtf8("Retinolequivalent"),					QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientRetinolequivalent	},
	{	QString::fromUtf8("ß-Carotene"),						QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientbCarotene	},
	{	QString::fromUtf8("Niacinequivalent"),					QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientNiacinequivalent	},
	{	QString::fromUtf8("free folic acid equivalent"),		QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientfreefolicacidequivalent	},
	{	QString::fromUtf8("free folic acid"),					QString::fromUtf8("Vitamins"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientfreefolicacid	},

	{	QString::fromUtf8("Sodium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientSodium	},
	{	QString::fromUtf8("Potassium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientPotassium	},
	{	QString::fromUtf8("Magnesium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientMagnesium	},
	{	QString::fromUtf8("Calcium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientCalcium	},
	{	QString::fromUtf8("Iron"),								QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientIron	},
	{	QString::fromUtf8("Phosphorus"),						QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientPhosphorus	},
	{	QString::fromUtf8("Copper"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientCopper	},
	{	QString::fromUtf8("Zinc"),								QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientZinc	},
	{	QString::fromUtf8("Chloride"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientChloride	},
	{	QString::fromUtf8("Fluoride"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientFluoride	},
	{	QString::fromUtf8("Iodide"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientIodide	},
	{	QString::fromUtf8("Selenium"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientSelenium	},
	{	QString::fromUtf8("Manganese"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientManganese	},
	{	QString::fromUtf8("Sulphur"),							QString::fromUtf8("Minerals and Trace Elements"),	cIngredient::UNIT_Weight,	cIngredient::iIngredientSulphur	},

	{	QString::fromUtf8("Arginine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientArginine	},
	{	QString::fromUtf8("Cystine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientCystine	},
	{	QString::fromUtf8("Histidine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientHistidine	},
	{	QString::fromUtf8("Isoleucine"),						QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientIsoleucine	},
	{	QString::fromUtf8("Leucine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientLeucine	},
	{	QString::fromUtf8("Lysine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientLysine	},
	{	QString::fromUtf8("Methionine"),						QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientMethionine	},
	{	QString::fromUtf8("Phenylalanine"),						QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientPhenylalanine	},
	{	QString::fromUtf8("Threonine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientThreonine	},
	{	QString::fromUtf8("Tryptophane"),						QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientTryptophane	},
	{	QString::fromUtf8("Tyrosine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientTyrosine	},
	{	QString::fromUtf8("Valine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientValine	},
	{	QString::fromUtf8("Alanine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientAlanine	},
	{	QString::fromUtf8("Aspartic"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientAspartid	},
	{	QString::fromUtf8("Aspartic acid"),						QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientAsparticacid	},
	{	QString::fromUtf8("Glutamic"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientGlutamid	},
	{	QString::fromUtf8("Glutamic acid"),						QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientGlutamicacid	},
	{	QString::fromUtf8("Glycine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientGlycine	},
	{	QString::fromUtf8("Proline"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientProline	},
	{	QString::fromUtf8("Serine"),							QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientSerine	},
	{	QString::fromUtf8("other essent. amino acids"),			QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientotheressent_aminoacids	},
	{	QString::fromUtf8("essent. amino acids"),				QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientessent_aminoacids	},
	{	QString::fromUtf8("other nonessent. amino acids"),		QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientothernonessent_aminoacids	},
	{	QString::fromUtf8("nonessent. amino acids"),			QString::fromUtf8("Aminos Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientnonessent_aminoacids	},

	{	QString::fromUtf8("Saturated fatty acids"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientSaturatedfattyacids	},
	{	QString::fromUtf8("Monounsaturated fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientMonounsaturatedfattyacids	},
	{	QString::fromUtf8("Polyunsaturated fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientPolyunsaturatedfattyacids	},
	{	QString::fromUtf8("Butyric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientButyricacid	},
	{	QString::fromUtf8("Caproic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientCaproicacid	},
	{	QString::fromUtf8("Caprylic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientCaprylicacid	},
	{	QString::fromUtf8("Capric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientCapricacid	},
	{	QString::fromUtf8("Lauric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientLauricacid	},
	{	QString::fromUtf8("Myristic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientMyristicacid	},
	{	QString::fromUtf8("C15:O fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC15_O_fattyacid	},
	{	QString::fromUtf8("Palmitic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientPalmiticacid	},
	{	QString::fromUtf8("Margaric acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientMargaricacid	},
	{	QString::fromUtf8("Stearic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientStearicacid	},
	{	QString::fromUtf8("Arachic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientArachicacid	},
	{	QString::fromUtf8("Behenic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientBehenicacid	},
	{	QString::fromUtf8("Lignoceric acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientLignocericacid	},
	{	QString::fromUtf8("Palmitoleic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientPalmitoleicacid	},
	{	QString::fromUtf8("Oleic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientOleicacid	},
	{	QString::fromUtf8("Eicosenic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientEicosenicacid	},
	{	QString::fromUtf8("C22:1 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC22_1_fattyacid	},
	{	QString::fromUtf8("C14:1 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC14_1_fattyacid	},
	{	QString::fromUtf8("C24:1 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC24_1_fattyacid	},
	{	QString::fromUtf8("Linoleic acid"),						QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientLinoleicacid	},
	{	QString::fromUtf8("Linolenic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientLinolenicacid	},
	{	QString::fromUtf8("Arachidonic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientArachidonicacid	},
	{	QString::fromUtf8("C18:4 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC18_4_fattyacid	},
	{	QString::fromUtf8("C20:5 N-3 fatty acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC20_5_N_3fattyacid	},
	{	QString::fromUtf8("C22:5 N-3 fatty acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC22_5_N_3fattyacid	},
	{	QString::fromUtf8("C22:6 N-3 fatty acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC22_6_N_3fattyacid	},
	{	QString::fromUtf8("C16:2 fatty acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientC16_2_fattyacid	},
	{	QString::fromUtf8("other saturated fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientothersaturatedfattyacids	},
	{	QString::fromUtf8("other monounsaturated fatty acids"),	QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientothermonounsaturatedfattyacids	},
	{	QString::fromUtf8("Nonadecatrienic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientNonadecatrienicacid	},
	{	QString::fromUtf8("Eicosadienic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientEicosadienicacid	},
	{	QString::fromUtf8("Eicosatrienic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientEicosatrienicacid	},
	{	QString::fromUtf8("Docosadienic acid"),					QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientDocosadienicacid	},
	{	QString::fromUtf8("Docosatrienic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientDocosatrienicacid	},
	{	QString::fromUtf8("Docosatetraenic acid"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientDocosatetraenicacid	},
	{	QString::fromUtf8("other polyunsat. fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientotherpolyunsat_fattyacids	},
	{	QString::fromUtf8("other short-chain fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientothershort_chainfattyacids	},
	{	QString::fromUtf8("short-chain fatty acids"),			QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientshort_chainfattyacids	},
	{	QString::fromUtf8("other medium-chain fatty acids"),	QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientothermedium_chainfattyacids	},
	{	QString::fromUtf8("medium-chain fatty acids"),			QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientmedium_chainfattyacids	},
	{	QString::fromUtf8("other long-chain fatty acids"),		QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientotherlong_chainfattyacids	},
	{	QString::fromUtf8("long-chain fatty acids"),			QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientlong_chainfattyacids	},
	{	QString::fromUtf8("Glycerol and Lipoides"),				QString::fromUtf8("Fatty Acids"),					cIngredient::UNIT_Weight,	cIngredient::iIngredientGlycerolandLipoides	},

	{	QString::fromUtf8("Sorbitol"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientSorbitol	},
	{	QString::fromUtf8("Glucose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientGlucose	},
	{	QString::fromUtf8("Fructose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientFructose	},
	{	QString::fromUtf8("Sucrose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientSucrose	},
	{	QString::fromUtf8("Lactose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientLactose	},
	{	QString::fromUtf8("Starch"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientStarch	},
	{	QString::fromUtf8("Maltose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientMaltose	},
	{	QString::fromUtf8("Galactose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientGalactose	},
	{	QString::fromUtf8("Glycogene"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientGlycogene	},
	{	QString::fromUtf8("Pentosan"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientPentosan	},
	{	QString::fromUtf8("Hexosan"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientHexosan	},
	{	QString::fromUtf8("Cellulose"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientCellulose	},
	{	QString::fromUtf8("Polyuronic acid"),					QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientPolyuronicacid	},
	{	QString::fromUtf8("Mannitol"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientMannitol	},
	{	QString::fromUtf8("Xylitol"),							QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientXylitol	},
	{	QString::fromUtf8("other sugar alcohols"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientothersugaralcohols	},
	{	QString::fromUtf8("Total sugar alcohols"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientTotalsugaralcohols	},
	{	QString::fromUtf8("other monosaccharides"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientothermonosaccharides	},
	{	QString::fromUtf8("Monosaccharides"),					QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientMonosaccharides	},
	{	QString::fromUtf8("other disaccharides"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientotherdisaccharides	},
	{	QString::fromUtf8("Disaccharides"),						QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientDisaccharides	},
	{	QString::fromUtf8("Oligosaccharides resorb."),			QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientOligosaccharidesresorb	},
	{	QString::fromUtf8("Oligosaccharides nonresorb."),		QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientOligosaccharidesnonresorb	},
	{	QString::fromUtf8("other polysaccharides"),				QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientotherpolysaccharides	},
	{	QString::fromUtf8("Polysaccharides"),					QString::fromUtf8("Special Carbohydrates"),			cIngredient::UNIT_Weight,	cIngredient::iIngredientPolysaccharides	},

	{	QString::fromUtf8("Dietary fibre water soluble"),		QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientDietaryfibrewatersoluble	},
	{	QString::fromUtf8("Dietary fibre water insoluble"),		QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientDietaryfibrewaterinsoluble	},
	{	QString::fromUtf8("Lignin"),							QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientLignin	},
	{	QString::fromUtf8("Purine bases nitrogen"),				QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientPurinebasesnitrogen	},
	{	QString::fromUtf8("Sodium chloride"),					QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientSodiumchloride	},
	{	QString::fromUtf8("Waste"),								QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientWaste	},
	{	QString::fromUtf8("other proteins"),					QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientotherproteins	},
	{	QString::fromUtf8("animal protein"),					QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientanimalprotein	},
	{	QString::fromUtf8("plant protein"),						QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientplantprotein	},
	{	QString::fromUtf8("Uric acid"),							QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientUricacid	},
	{	QString::fromUtf8("other organic acids"),				QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientotherorganicacids	},
	{	QString::fromUtf8("Mol-diff. cations-anions"),			QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientMol_diff_cations_anions	},
	{	QString::fromUtf8("Nitrogen factor"),					QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientNitrogenfactor	},
	{	QString::fromUtf8("Fatty acid part"),					QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientFattyacidpart	},
	{	QString::fromUtf8("Minerals part"),						QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientMineralspart	},
	{	QString::fromUtf8("P/S Ratio"),							QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientPS_Ratio	},
	{	QString::fromUtf8("Biological value"),					QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientBiologicalvalue	},
	{	QString::fromUtf8("Fructose free bread units"),			QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientFructosefreebreadunits	},
	{	QString::fromUtf8("average consumption"),				QString::fromUtf8("Others"),						cIngredient::UNIT_Weight,	cIngredient::iIngredientaverageconsumption	},
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
	m_iID(-1)
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

	if(m_szIngredientName.isEmpty())
		return(false);

	cDBInterface*	lpInterface	= lpDB->dbInterface();

	lpInterface->beginTransaction();

	if(m_iID == -1)
	{
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

		m_iID	= id;
	}
	else
	{
		lpInterface->setName(m_iID, m_szIngredientName);
		lpInterface->setGroup(m_iID, m_szIngredientGroup);

		for(int z = 0;z < cIngredient::iIngredientMax;z++)
		{
			if(m_dValue[z] != -1)
			{
				if(!lpInterface->set(m_iID, z, m_dValue[z]))
					return(false);
			}
		}
	}

	lpInterface->endTransaction();

	return(true);
}

qint32 cIngredient::ingredientID()
{
	return(m_iID);
}

void cIngredient::setIngredientName(const QString& szIngredientName)
{
	m_szIngredientName	= szIngredientName;
}

QString cIngredient::ingredientName()
{
	return(m_szIngredientName);
}

void cIngredient::setIngredientGroup(const QString& szIngredientGroup)
{
	m_szIngredientGroup	= szIngredientGroup;
}

QString cIngredient::ingredientGroup()
{
	return(m_szIngredientGroup);
}

QStringList cIngredient::groups()
{
	QStringList	groupsList;

	for(int z = 0;z < (int)sizeof(g_groupname)/(int)sizeof(GROUPNAME);z++)
		groupsList.append(g_groupname[z].szGroup);

	groupsList.removeDuplicates();
	return(groupsList);
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

qreal cIngredient::value(cIngredient::iIngredient i)
{
	return(m_dValue[i]);
}

QString cIngredient::valueFormatted(cIngredient::iIngredient i)
{
	qreal	dValue	= m_dValue[i];
	QString	str;
	QString	unit("g");
	qint16	factor;

	switch(g_groupname[i].unit)
	{
	case UNIT_Calories:
		str	= QString("%1 kCal").arg(dValue);
		break;
	case UNIT_Joule:
		str	= QString("%1 kJoule").arg(dValue);
		break;
	case UNIT_Fluid:
		str	= QString("%1 l").arg(dValue);
		break;
	case UNIT_None:
		str	= QString("%1").arg(dValue);
		break;
	case UNIT_Peace:
		str	= QString("%1 pcs").arg(dValue);
		break;
	case UNIT_Weight:
		factor	= 1;
		if(dValue == 0)
			str	= QString("%1 g").arg(dValue);
		else
		{
			while(dValue < 1)
			{
				dValue *= 1000;
				factor++;
			}

			switch(factor)
			{
			case 1:
				str	= QString("%1 g").arg(dValue);
				break;
			case 2:
				str	= QString("%1 mg").arg(dValue);
				break;
			case 3:
				str	= QString("%1 µg").arg(dValue);
				break;
			case 4:
				str	= QString("%1 ng").arg(dValue);
				break;
			case 5:
				str	= QString("%1 pg").arg(dValue);
				break;
			}
		}
		break;
	default:
		str	= QString("%1").arg(dValue);
		break;
	}

	return(str);
}

cIngredient::UNIT cIngredient::unit(cIngredient::iIngredient i)
{
	for(int z = 0;z < (int)sizeof(g_groupname)/(int)sizeof(GROUPNAME);z++)
	{
		if(g_groupname[z].iIngredient == i)
			return(g_groupname[z].unit);
	}
	return(cIngredient::UNIT::UNIT_None);
}

void cIngredient::setValue(cIngredient::iIngredient i, qreal dValue)
{
	m_dValue[i]	= dValue;
}
