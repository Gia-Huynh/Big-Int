#include "process.h"
//#include "process.cpp"

int main()
{
	double st = clock();
	bigint x;
	bigint y;
	//string t = 9541404811952600188108892643940113743366076576329869588487483741860909829432558124401104264550145125931683567105462264315676010841015160953103260105015274704853365044083958674582475301465440981464488108841078506677684450098922893338593855398613743606258564617543403968764648644030808644162231423732490497825171861340981295349980876427696082696415875221954009885612759532599057017134247020270450976453484439528288255676416298946812611315596822700256487545642076503478985625871769715630985773478075598026138694882343984899208384175061449315353156127307280458813435451834613624862013497625252151917382722209549819077362430267105615863803778895371179357592744395763580713447976201861316072426538380489089263321485094447089423483181202448918127101391135146563618816434792694047567112398087099405786264984260185651049635286027710444194350856659346130808182246971822427652348390235990075261220928791077071171192463645740010716075278735070442222876312109353300508658596967624196996392650720130888491446214113964329604588310931361566656816171368670582083155934110922517525438715586708567645755984269023824396866888932852699764728871972190316771359450905177774142954330145202126108682968343913809839510793834299934294871660812278274273711845631135224407992870050096466746401577419145185261160912201273722784716347354461820041541696461993395542790080623452729228168679016160158552954615932326128739311438902832173182082475143732239309674249229655274043918467272514219660140486823608252948195850326606099848344966848563010959623722953220366214510698484312910670892742008509121524571033779668730403363265674538535811717999262717341017431695334224100413017660275036932142405133731007872968370610010034397621011797709916002780236942181079347132774404473089288945867979249168180826549563563047600083399781073558058211067789400158245784648880677313144048129416318510735346354605728713617473660224434631952191425546778520879398245981070731299762496687984558036685759082107154922960645548265908189919144729858288179798139487340295929412553186253089308233604176728288384607917678668003215949632120178898875329760749181738753667451742817825559144266953630855580930874429319734967502816470615400292231870057405422967461128773967068753167269516287248739154487381671719231355510524897532761026786862401521829683373951635464132116286510792237281316775206257085456680487512346974808497434125961582770292109798604889465290549714987071944504969844091049586626984045730117448712007277239975582414966654580167348546312709118126649917537397390228507765650505745941158808160524579770857430088724455755279405353321136057554171384364104025638643563636188979674199338194495426954393185977440377124192129656929222809627618854865916320041476583727391253124518747910312202189322809530362545992276224171745977403372776558474004005775072417666148881294831481898506196773042965352727132217626314089407073741072353981980381689773357527256843";
	//string q = "1502222333333333301";
	string q = "15022233301";
	//string t = "123131231233087123124325234643333333339541404812311952600188108892643940113743366076576329869588487483741860909829432558124401104264550145125931683567105462264315676010841015160953103260105015274704853365044083958674582475301465440981464488108841078506677684450098922893338593855398613743606258564617543403968764648644030808644162231423732490497825171861340981295349980876427696082696415875221954009885612759532599057017134247020270450976453484439528287105462264315676010841015160953103260105015274704853365044083958674582475301465440981464488108841078506677684450098922893338593855398613743606258564617543403968764648644030808644162231423732490497825171861340981295349980876427696082696415875221954009885612759532599057017134247020270450976453484439528288255676416298946812611315596822700256487545642825567641629894681261131559682270025648754564207650347898562587176971563098577347807559802613869488234398489920838417506144931535315612730728045881343545183461362486201349762525215191738272220954981907736243026710561586380377889537117935759274439576358071344797620186131607242653838048908926332148509444708942348318120244891812710139113514656361881643479269404756711239808709940578626498426018565104963528602771044419435085665934613080818224697182242765234839023599007526122092879107707117119246364574001071607527873507044222287631210935333333333333333333333333333333333333333333333332222222222222222222222222222222222222223333333333333333333333333333333333333222222222222222222222222333333333333"
	//string t = "1231273123123812390124893024893257239058983904123123123120912";
	string t = "1231231241234325";
	//string t = "12312317687853933333333333323333333333333333333333333333333333\3333333333333333333302342076\33333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207687853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333231231231233333333333333333333333333333333333333333333333333333333333333333333333330234207687853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333231231231233333333333333333333333333333333333333333333333333333333333333333333333330234207687853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333231231231233333333333333333333333333333333333333333333333333333333333333333333333330234207687853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342073302342076878533333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333323123123123333333333333333333333333333333333333333333333333333333333333333333333333023420768785393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333302342076885393333333333332333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333023420768853933333333333323333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333330234207688539333333333333233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333222222222222222222222222222222222222222222222222222222264758679234234324234434444444444444444222222222222222222222222222222222222222222222222222222222222222224444433333333333333333322222222222222223432423423487";
	DecimalToBigint(x, t);
	DecimalToBigint(y, q); 
	bigint z;
	copy(z, x*y);
	cout << "x: " << BigintToDecimal(x) << "\n";
	cout << "y: " << BigintToDecimal(y) << "\n";
	cout << "x * y = " << BigintToDecimal(z);
	PrimeCheck(y);
	freedata(x);
	freedata(y);
	freedata(z);
	cout << "\ntime: " << (1.0 * clock() - st) / 1000 << '\n';
}
