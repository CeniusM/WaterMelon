#pragma once

#include "Direction.h"
#include "Square.h"
#include "Bitboard.h"

#pragma region Queen
constexpr Bitboard QueenSquareToAllDir[]
{
9313761861428380670,180779649147209725,289501704256556795,578721933553179895,1157442771889699055,2314886638996058335,4630054752952049855,9332167099941961855,4693051017133293059,9386102034266586375,325459994840333070,578862399937640220,1157444424410132280,2315169224285282160,4702396038313459680,9404792076610076608,2382695595002168069,4765391190004401930,9530782384287059477,614821794359483434,1157867469641037908,2387511058326581416,4775021017124823120,9550042029937901728,1227517888139822345,2455035776296487442,4910072647826412836,9820426766351346249,1266167048752878738,2460276499189639204,4920271519124312136,9840541934442029200,649930110732142865,1299860225776030242,2600000831312176196,5272058161445620104,10544115227674579473,2641485286422881314,5210911883574396996,10421541192660455560,361411684042608929,722824471891812930,1517426162373248132,3034571949281478664,6068863523097809168,12137446670713758241,5827868887957914690,11583398706901190788,287670746360127809,575624067208594050,1079472019650937860,2087167920257370120,4102559721436811280,8133343319517438240,16194909420462031425,13871017173176583298,18303478847064064385,18232552689433215490,18090419998706369540,17806153522019305480,17237620560088797200,16100553540994408480,13826139127340482880,9205534180971414145
};

constexpr Bitboard QueenSquareToDir[]
{
0,0,0,0,0,0,0,0,1,2,4,8,16,32,64,128,257,514,1028,2056,4112,8224,16448,32896,65793,131586,263172,526344,1052688,2105376,4210752,8421504,16843009,33686018,67372036,134744072,269488144,538976288,1077952576,2155905152,4311810305,8623620610,17247241220,34494482440,68988964880,137977929760,275955859520,551911719040,1103823438081,2207646876162,4415293752324,8830587504648,17661175009296,35322350018592,70644700037184,141289400074368,282578800148737,565157600297474,1130315200594948,2260630401189896,4521260802379792,9042521604759584,18085043209519168,36170086419038336,254,252,248,240,224,192,128,0,65024,64512,63488,61440,57344,49152,32768,0,16646144,16515072,16252928,15728640,14680064,12582912,8388608,0,4261412864,4227858432,4160749568,4026531840,3758096384,3221225472,2147483648,0,1090921693184,1082331758592,1065151889408,1030792151040,962072674304,824633720832,549755813888,0,279275953455104,277076930199552,272678883688448,263882790666240,246290604621824,211106232532992,140737488355328,0,71494644084506624,70931694131085312,69805794224242688,67553994410557440,63050394783186944,54043195528445952,36028797018963968,0,18302628885633695744,18158513697557839872,17870283321406128128,17293822569102704640,16140901064495857664,13835058055282163712,9223372036854775808,0,72340172838076672,144680345676153344,289360691352306688,578721382704613376,1157442765409226752,2314885530818453504,4629771061636907008,9259542123273814016,72340172838076416,144680345676152832,289360691352305664,578721382704611328,1157442765409222656,2314885530818445312,4629771061636890624,9259542123273781248,72340172838010880,144680345676021760,289360691352043520,578721382704087040,1157442765408174080,2314885530816348160,4629771061632696320,9259542123265392640,72340172821233664,144680345642467328,289360691284934656,578721382569869312,1157442765139738624,2314885530279477248,4629771060558954496,9259542121117908992,72340168526266368,144680337052532736,289360674105065472,578721348210130944,1157442696420261888,2314885392840523776,4629770785681047552,9259541571362095104,72339069014638592,144678138029277184,289356276058554368,578712552117108736,1157425104234217472,2314850208468434944,4629700416936869888,9259400833873739776,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808,0,0,0,0,0,0,0,0,0,1,3,7,15,31,63,127,0,256,768,1792,3840,7936,16128,32512,0,65536,196608,458752,983040,2031616,4128768,8323072,0,16777216,50331648,117440512,251658240,520093696,1056964608,2130706432,0,4294967296,12884901888,30064771072,64424509440,133143986176,270582939648,545460846592,0,1099511627776,3298534883328,7696581394432,16492674416640,34084860461056,69269232549888,139637976727552,0,281474976710656,844424930131968,1970324836974592,4222124650659840,8725724278030336,17732923532771328,35747322042253312,0,72057594037927936,216172782113783808,504403158265495552,1080863910568919040,2233785415175766016,4539628424389459968,9151314442816847872,0,0,0,0,0,0,0,0,2,4,8,16,32,64,128,0,516,1032,2064,4128,8256,16512,32768,0,132104,264208,528416,1056832,2113664,4227072,8388608,0,33818640,67637280,135274560,270549120,541097984,1082130432,2147483648,0,8657571872,17315143744,34630287488,69260574720,138521083904,277025390592,549755813888,0,2216338399296,4432676798592,8865353596928,17730707128320,35461397479424,70918499991552,140737488355328,0,567382630219904,1134765260439552,2269530520813568,4539061024849920,9078117754732544,18155135997837312,36028797018963968,0,9241421688590303744,36099303471055872,141012904183808,550831656960,2151686144,8404992,32768,0,4620710844295151616,9241421688590303232,36099303471054848,141012904181760,550831652864,2151677952,8388608,0,2310355422147510272,4620710844295020544,9241421688590041088,36099303470530560,141012903133184,550829555712,2147483648,0,1155177711056977920,2310355422113955840,4620710844227911680,9241421688455823360,36099303202095104,141012366262272,549755813888,0,577588851233521664,1155177702467043328,2310355404934086656,4620710809868173312,9241421619736346624,36099165763141632,140737488355328,0,288793326105133056,577586652210266112,1155173304420532224,2310346608841064448,4620693217682128896,9241386435364257792,36028797018963968,0,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808,0,0,0,0,0,0,0,0,0,0,256,66048,16909312,4328785920,1108169199616,283691315109888,72624976668147712,0,65536,16908288,4328783872,1108169195520,283691315101696,72624976668131328,145249953336262656,0,16777216,4328521728,1108168671232,283691314053120,72624976666034176,145249953332068352,290499906664136704,0,4294967296,1108101562368,283691179835392,72624976397598720,145249952795197440,290499905590394880,580999811180789760,0,1099511627776,283673999966208,72624942037860352,145249884075720704,290499768151441408,580999536302882816,1161999072605765632,0,281474976710656,72620543991349248,145241087982698496,290482175965396992,580964351930793984,1161928703861587968,2323857407723175936,0,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,4,8,16,32,64,0,256,513,1026,2052,4104,8208,16416,0,65536,131328,262657,525314,1050628,2101256,4202512,0,16777216,33619968,67240192,134480385,268960770,537921540,1075843080,0,4294967296,8606711808,17213489152,34426978560,68853957121,137707914242,275415828484,0,1099511627776,2203318222848,4406653222912,8813306511360,17626613022976,35253226045953,70506452091906,0,281474976710656,564049465049088,1128103225065472,2256206466908160,4512412933881856,9024825867763968,18049651735527937,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
constexpr Bitboard GetQueenAllDirBitboard(Square square)
{
	return QueenSquareToAllDir[square];
}
constexpr Bitboard GetQueenBitboardFromInDir(Square square, DirectionIndex dirIndex)
{
	return QueenSquareToDir[square | (dirIndex << 6)];
}
#pragma endregion

#pragma region Rook
constexpr Bitboard RookSquareToAllDir[]
{
72340172838076926,144680345676153597,289360691352306939,578721382704613623,1157442765409226991,2314885530818453727,4629771061636907199,9259542123273814143,72340172838141441,144680345676217602,289360691352369924,578721382704674568,1157442765409283856,2314885530818502432,4629771061636939584,9259542123273813888,72340172854657281,144680345692602882,289360691368494084,578721382720276488,1157442765423841296,2314885530830970912,4629771061645230144,9259542123273748608,72340177082712321,144680349887234562,289360695496279044,578721386714368008,1157442769150545936,2314885534022901792,4629771063767613504,9259542123257036928,72341259464802561,144681423712944642,289361752209228804,578722409201797128,1157443723186933776,2314886351157207072,4629771607097753664,9259542118978846848,72618349279904001,144956323094725122,289632270724367364,578984165983651848,1157687956502220816,2315095537539358752,4629910699613634624,9259541023762186368,143553341945872641,215330564830528002,358885010599838724,645993902138460168,1220211685215703056,2368647251370188832,4665518383679160384,9259260648297103488,18302911464433844481,18231136449196065282,18087586418720506884,17800486357769390088,17226286235867156496,16077885992062689312,13781085504453754944,9187484529235886208
};
constexpr Bitboard RookSquareToDir[]
{
0,0,0,0,0,0,0,0,1,2,4,8,16,32,64,128,257,514,1028,2056,4112,8224,16448,32896,65793,131586,263172,526344,1052688,2105376,4210752,8421504,16843009,33686018,67372036,134744072,269488144,538976288,1077952576,2155905152,4311810305,8623620610,17247241220,34494482440,68988964880,137977929760,275955859520,551911719040,1103823438081,2207646876162,4415293752324,8830587504648,17661175009296,35322350018592,70644700037184,141289400074368,282578800148737,565157600297474,1130315200594948,2260630401189896,4521260802379792,9042521604759584,18085043209519168,36170086419038336,254,252,248,240,224,192,128,0,65024,64512,63488,61440,57344,49152,32768,0,16646144,16515072,16252928,15728640,14680064,12582912,8388608,0,4261412864,4227858432,4160749568,4026531840,3758096384,3221225472,2147483648,0,1090921693184,1082331758592,1065151889408,1030792151040,962072674304,824633720832,549755813888,0,279275953455104,277076930199552,272678883688448,263882790666240,246290604621824,211106232532992,140737488355328,0,71494644084506624,70931694131085312,69805794224242688,67553994410557440,63050394783186944,54043195528445952,36028797018963968,0,18302628885633695744,18158513697557839872,17870283321406128128,17293822569102704640,16140901064495857664,13835058055282163712,9223372036854775808,0,72340172838076672,144680345676153344,289360691352306688,578721382704613376,1157442765409226752,2314885530818453504,4629771061636907008,9259542123273814016,72340172838076416,144680345676152832,289360691352305664,578721382704611328,1157442765409222656,2314885530818445312,4629771061636890624,9259542123273781248,72340172838010880,144680345676021760,289360691352043520,578721382704087040,1157442765408174080,2314885530816348160,4629771061632696320,9259542123265392640,72340172821233664,144680345642467328,289360691284934656,578721382569869312,1157442765139738624,2314885530279477248,4629771060558954496,9259542121117908992,72340168526266368,144680337052532736,289360674105065472,578721348210130944,1157442696420261888,2314885392840523776,4629770785681047552,9259541571362095104,72339069014638592,144678138029277184,289356276058554368,578712552117108736,1157425104234217472,2314850208468434944,4629700416936869888,9259400833873739776,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808,0,0,0,0,0,0,0,0,0,1,3,7,15,31,63,127,0,256,768,1792,3840,7936,16128,32512,0,65536,196608,458752,983040,2031616,4128768,8323072,0,16777216,50331648,117440512,251658240,520093696,1056964608,2130706432,0,4294967296,12884901888,30064771072,64424509440,133143986176,270582939648,545460846592,0,1099511627776,3298534883328,7696581394432,16492674416640,34084860461056,69269232549888,139637976727552,0,281474976710656,844424930131968,1970324836974592,4222124650659840,8725724278030336,17732923532771328,35747322042253312,0,72057594037927936,216172782113783808,504403158265495552,1080863910568919040,2233785415175766016,4539628424389459968,9151314442816847872,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
constexpr Bitboard GetRookAllDirBitboard(Square square)
{
	return RookSquareToAllDir[square];
}
constexpr Bitboard GetRookBitboardFromInDir(Square square, DirectionIndex dirIndex)
{
	return RookSquareToDir[square | (dirIndex << 6)];
}
#pragma endregion

#pragma region Bishop
constexpr Bitboard BishopSquareToAllDir[]
{
9241421688590303744,36099303471056128,141012904249856,550848566272,6480472064,1108177604608,283691315142656,72624976668147712,4620710844295151618,9241421688590368773,36099303487963146,141017232965652,1659000848424,283693466779728,72624976676520096,145249953336262720,2310355422147510788,4620710844311799048,9241421692918565393,36100411639206946,424704217196612,72625527495610504,145249955479592976,290499906664153120,1155177711057110024,2310355426409252880,4620711952330133792,9241705379636978241,108724279602332802,145390965166737412,290500455356698632,580999811184992272,577588851267340304,1155178802063085600,2310639079102947392,4693335752243822976,9386671504487645697,326598935265674242,581140276476643332,1161999073681608712,288793334762704928,577868148797087808,1227793891648880768,2455587783297826816,4911175566595588352,9822351133174399489,1197958188344280066,2323857683139004420,144117404414255168,360293502378066048,720587009051099136,1441174018118909952,2882348036221108224,5764696068147249408,11529391036782871041,4611756524879479810,567382630219904,1416240237150208,2833579985862656,5667164249915392,11334324221640704,22667548931719168,45053622886727936,18049651735527937
};
constexpr Bitboard BishopSquareToDir[]
{
0,0,0,0,0,0,0,0,2,4,8,16,32,64,128,0,516,1032,2064,4128,8256,16512,32768,0,132104,264208,528416,1056832,2113664,4227072,8388608,0,33818640,67637280,135274560,270549120,541097984,1082130432,2147483648,0,8657571872,17315143744,34630287488,69260574720,138521083904,277025390592,549755813888,0,2216338399296,4432676798592,8865353596928,17730707128320,35461397479424,70918499991552,140737488355328,0,567382630219904,1134765260439552,2269530520813568,4539061024849920,9078117754732544,18155135997837312,36028797018963968,0,9241421688590303744,36099303471055872,141012904183808,550831656960,2151686144,8404992,32768,0,4620710844295151616,9241421688590303232,36099303471054848,141012904181760,550831652864,2151677952,8388608,0,2310355422147510272,4620710844295020544,9241421688590041088,36099303470530560,141012903133184,550829555712,2147483648,0,1155177711056977920,2310355422113955840,4620710844227911680,9241421688455823360,36099303202095104,141012366262272,549755813888,0,577588851233521664,1155177702467043328,2310355404934086656,4620710809868173312,9241421619736346624,36099165763141632,140737488355328,0,288793326105133056,577586652210266112,1155173304420532224,2310346608841064448,4620693217682128896,9241386435364257792,36028797018963968,0,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808,0,0,0,0,0,0,0,0,0,0,256,66048,16909312,4328785920,1108169199616,283691315109888,72624976668147712,0,65536,16908288,4328783872,1108169195520,283691315101696,72624976668131328,145249953336262656,0,16777216,4328521728,1108168671232,283691314053120,72624976666034176,145249953332068352,290499906664136704,0,4294967296,1108101562368,283691179835392,72624976397598720,145249952795197440,290499905590394880,580999811180789760,0,1099511627776,283673999966208,72624942037860352,145249884075720704,290499768151441408,580999536302882816,1161999072605765632,0,281474976710656,72620543991349248,145241087982698496,290482175965396992,580964351930793984,1161928703861587968,2323857407723175936,0,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,4,8,16,32,64,0,256,513,1026,2052,4104,8208,16416,0,65536,131328,262657,525314,1050628,2101256,4202512,0,16777216,33619968,67240192,134480385,268960770,537921540,1075843080,0,4294967296,8606711808,17213489152,34426978560,68853957121,137707914242,275415828484,0,1099511627776,2203318222848,4406653222912,8813306511360,17626613022976,35253226045953,70506452091906,0,281474976710656,564049465049088,1128103225065472,2256206466908160,4512412933881856,9024825867763968,18049651735527937,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
constexpr Bitboard GetBishopAllDirBitboard(Square square)
{
	return BishopSquareToAllDir[square];
}

constexpr Bitboard GetBishopBitboardFromInDir(Square square, DirectionIndex dirIndex)
{
	return BishopSquareToDir[square | (dirIndex << 6)];
}
#pragma endregion

#pragma region King
constexpr Bitboard KingSquareToAllDir[]
{
770,1797,3594,7188,14376,28752,57504,49216,197123,460039,920078,1840156,3680312,7360624,14721248,12599488,50463488,117769984,235539968,471079936,942159872,1884319744,3768639488,3225468928,12918652928,30149115904,60298231808,120596463616,241192927232,482385854464,964771708928,825720045568,3307175149568,7718173671424,15436347342848,30872694685696,61745389371392,123490778742784,246981557485568,211384331665408,846636838289408,1975852459884544,3951704919769088,7903409839538176,15806819679076352,31613639358152704,63227278716305408,54114388906344448,216739030602088448,505818229730443264,1011636459460886528,2023272918921773056,4046545837843546112,8093091675687092224,16186183351374184448,13853283560024178688,144959613005987840,362258295026614272,724516590053228544,1449033180106457088,2898066360212914176,5796132720425828352,11592265440851656704,4665729213955833856
};
constexpr Bitboard GetKingAllDirBitboard(Square square)
{
	return KingSquareToAllDir[square];
}
#pragma endregion

#pragma region Knight
constexpr Bitboard KnightSquareToAllDir[]
{
132096,329728,659712,1319424,2638848,5277696,10489856,4202496,33816580,84410376,168886289,337772578,675545156,1351090312,2685403152,1075839008,8657044482,21609056261,43234889994,86469779988,172939559976,345879119952,687463207072,275414786112,2216203387392,5531918402816,11068131838464,22136263676928,44272527353856,88545054707712,175990581010432,70506185244672,567348067172352,1416171111120896,2833441750646784,5666883501293568,11333767002587136,22667534005174272,45053588738670592,18049583422636032,145241105196122112,362539804446949376,725361088165576704,1450722176331153408,2901444352662306816,5802888705324613632,11533718717099671552,4620693356194824192,288234782788157440,576469569871282176,1224997833292120064,2449995666584240128,4899991333168480256,9799982666336960512,1152939783987658752,2305878468463689728,1128098930098176,2257297371824128,4796069720358912,9592139440717824,19184278881435648,38368557762871296,4679521487814656,9077567998918656
};
constexpr Bitboard GetKnightAllDirBitboard(Square square)
{
	return KnightSquareToAllDir[square];
}
#pragma endregion

#pragma region Pawn
constexpr Bitboard WhitePawnAttacks[]
{
512,1280,2560,5120,10240,20480,40960,16384,131072,327680,655360,1310720,2621440,5242880,10485760,4194304,33554432,83886080,167772160,335544320,671088640,1342177280,2684354560,1073741824,8589934592,21474836480,42949672960,85899345920,171798691840,343597383680,687194767360,274877906944,2199023255552,5497558138880,10995116277760,21990232555520,43980465111040,87960930222080,175921860444160,70368744177664,562949953421312,1407374883553280,2814749767106560,5629499534213120,11258999068426240,22517998136852480,45035996273704960,18014398509481984,144115188075855872,360287970189639680,720575940379279360,1441151880758558720,2882303761517117440,5764607523034234880,11529215046068469760,4611686018427387904,0,0,0,0,0,0,0,0
};
constexpr Bitboard BlackPawnAttacks[]
{
0,0,0,0,0,0,0,0,2,5,10,20,40,80,160,64,512,1280,2560,5120,10240,20480,40960,16384,131072,327680,655360,1310720,2621440,5242880,10485760,4194304,33554432,83886080,167772160,335544320,671088640,1342177280,2684354560,1073741824,8589934592,21474836480,42949672960,85899345920,171798691840,343597383680,687194767360,274877906944,2199023255552,5497558138880,10995116277760,21990232555520,43980465111040,87960930222080,175921860444160,70368744177664,562949953421312,1407374883553280,2814749767106560,5629499534213120,11258999068426240,22517998136852480,45035996273704960,18014398509481984
};
constexpr Bitboard GetWhitePawnAttacks(Square square)
{
	return WhitePawnAttacks[square];
}
constexpr Bitboard GetBlackPawnAttacks(Square square)
{
	return BlackPawnAttacks[square];
}
#pragma endregion

#pragma region DistanceToBoard
constexpr char GetDistanceToBoardInDirection(Square square, DirectionIndex direction)
{
	ThrowNotImplementedException("");
	return DistanceToBoardInDirection[square | (direction << 6)];
}
constexpr char DistanceToBoardInDirection[]
{
	2,
};
#pragma endregion

#pragma region GetDirectionIndex
constexpr char GetDirectionIndexFromSquareToSquare(Square start, Square target)
{
	ThrowNotImplementedException("");
	return DirectionIndexFromSquareToSquare[start | (target << 6)];
}
constexpr char DirectionIndexFromSquareToSquare[]
{
	2,
};
#pragma endregion
