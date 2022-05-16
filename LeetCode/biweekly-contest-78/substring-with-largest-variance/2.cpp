/*
参考：https://ark4rk.hatenablog.com/entry/2018/01/08/002508
・自力ならず。。
・最大部分配列問題、連続部分列のDP
・前提として、文字種の全ペアを(最小出現数, 最大出現数)として全探索する。
　そもそもこれが出なかったからね…。で、そしたら各ペアは、-1,+1に変換した列で、
　最大部分配列問題ってのをやることになる。ようは連続部分列の値の最大化。
　調べてたら分割統治法が紹介されていたので、とりあえずやってみる。
・なんかTLでsiさんがlog付きでTLEになるって言ってたのはこれのことか…。
・公式はKadane's algorithmっていうのを紹介してたけど、
　今回は「ある文字を1回でも使ったか」を状態に持たないといけないので、
　結局そのまま適用できなくてアドホックっぽい感じになっちゃう。
・よくよく考えると、連続部分列で(開始前,継続中,終了後)の3状態を持つDPが、
　今回のやつに適用できそうだと気付く。
　実際合ってるっぽいんだけど、なんかTLEする。
　26*26*10000=676万で、これに定数添字乗るくらいでC++がTLEするとは思えないんだけどね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

int dp[10007][3][2];

class Solution {
public:
    int largestVariance(string S) {
        ll N = S.size();
        vector<ll> A(N);
        rep(i, N) {
            A[i] = S[i] - 'a';
        }
        ll M = 26;
        vector<int> B(N);
        int ans = 0;
        rep(c1, M) {
            rep(c2, M) {
                if (c1 == c2) continue;
                rep(i, N) {
                    if (A[i] == c1) {
                        B[i] = -1;
                    } elif (A[i] == c2) {
                        B[i] = 1;
                    } else {
                        B[i] = 0;
                    }
                }

                rep(i, N+1) rep(j, 3) rep(k, 2) dp[i][j][k] = -MOD;
                dp[0][0][0] = 0;
                rep(i, N) {
                    rep(j, 3) {
                        rep(k, 2) {
                            ll jj = j == 0 ? 0 : 2;
                            chmax(dp[i+1][jj][k], dp[i][j][k]);
                            if (j != 2) {
                                chmax(dp[i+1][1][k|(B[i] == -1)], dp[i][j][k]+B[i]);
                            }
                        }
                    }
                }
                chmax(ans, max(dp[N][1][1], dp[N][2][1]));
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        // auto res = sol.largestVariance("aababbb");
        auto res = sol.largestVariance("fzvpszwyavklghcedpgnygnqmxotgpcowkzvinkthpsmuvdhdmbcgaeeeqqdqocxesblxpkdpzeutiawmxqctnhemffgivsvdsledgsrybsflgzptfcjulnwiuownzpdoyncrhtcvdrgwtqogceftgrocjbtfvivzdlnzbjegniwnndepuuoqxtiydjkoyngqvmshmmawiapqhibbfwijlqagssoamnrvlgkyatyijdairipcacoxgpknahwhkcwzcwxtrqhhsyluiahgyfmfbjxxumaackpwkkaxcmvgupfnbqalrmpcwarkeztxvcbafwzmivecrjvorywnvjjoefebxmxfpsbszeeywncmultdlcortdohtkvbngtxonkmfbrgfanyzhfmcaavppctcqapehicqryqtvwafifkergimfqefbwrfumrezjnphjmgrtwjsezttksstnwwouleqovmkzmcofkieemptajedhmqwbybzsfgzjjxdnmgwhgwevldrmnnafhjzrbtczldfsdngompxbuyhtiznnvhtawueiuezuhnvhyfshtkcsjmgpelotpmiwunnrukeniouuqlprydcjlowvuwirdrfstvlgpbzaixgynjxumffsswjjtiiseyfcdlbvszoqizdtzfmiwpctrritnlpqxrqqjhtgvqdgiqducskrwqlivqrhpgwnvqydgpvihdffjuuopwaacmrknutjgjbckovgioifdevlayynjshmprmqgjdpmijwkhwhdvgbayeuccvstdlxzdxjtyexsdedarlqdnxlxeblfwirkxtebqkqgoogngyzauqeltsqteskucoqmdhndzlyanzswxdhzhfsdktuwhagnzlifatnnwccaddapuuvzmkcyhzgvwljqenrplbgnqpbnsswptstxospqkootogdwynhlthxqncmoixbbtvgyvqfcpawayfxtcnvimzlijvservsctwktykkzpbytlmdcwbzztgdsbtfzmrxzijoshsbjcjpvrwgimlgiqgfuvydhzwurfifotzpihdlnmhafsjpvnfizacilwwzrvahztliynxafirnbosvvmmisvktlckagiaaqswezavoxapzfolsmxhrqwxhrsgopnbtjgyivhkcrlcjiuuuaywmvefkntliexntpfsnmgllulffxvnpoffxaaykozqufiegagdtmootlrzkvsheexacneunbpvcficounhhyiavhyzyblfcyykwtamjglseibxxwfzpwphafmspclzdbfixzythluoiehivxdqnhmfhekmxfgpfaapmknwiukvabvkcysbtllgkxvkliqqgmjgpjanzjbvsykvskvdadhgejdhqeluewqjzvayxcgsghxpuyszncrlfxjckgfoygrabkrbryuaqesyobfoduyjqhizztnnkqnqprcwcssqerqcxcfsovcxeeilxxtrhfwptqxbpemnydsqdxggctotpzdseofpetoktexyhgxxasjhpaqrkuxdauaqujkuvtmhlmmiflivtsqspmarblnmuwfnnniqkfsbrnsftdftyatzuzuwpkhrmbswyuupytrqngvdjwiceazrrurkfawaupldfeptwewekvumgijlrywjjdyfmvgxwddbwwncdjdxjpmtcakcnzowceofjfnpcldtotrctmcyzwyxdsgagvblybfecisqubnaurtwbiedsryizhpnotkqoywdjhjgnhdkxcwvtnkmfrcgirgajibjzjhohnfjenxqjblwzrvozwksgulcfeuuabcavjsftxwxdzppnbqehnrxsqlpicenpemhudvrxaqpluxotbvpyqipuelazcenrqcrrmdcorbhqplqgsjrgbdfdfchsjvncyxyhuntyelhdxlkayniuwdxzauhazqdrqjskdugssujzygcnyhuyeaktvdqlvtamzqwyyqxmluhfsuhguzdhmyvrycwcuxuhrulmefovbecgqknhghbxfrtboptalfxwuqynfmgsppmfgiynwuyoxyqydgwxhvmobjayjucvnuamufjdtbxinlrmchkqfvsvavgyenwtqffmuscqffhlqodagqrfhfomutdsccwnfwexzqyhagoqquxjdyeggnudfcepenkqudfjlbodmexhjehxgcvnvsnljbnhwbjkjytffezukhnljmuzfrospjgrtmewvjzftuwrvjkavkgllmunxyfktvwbgzjqssakwaaxeqjjsowrtdfulxpfdkjykqnursrdakcvnkiojtpkhllsmnctpeqhbsycpvaqsfdvlellespcwzzfqhzxitrkrfauhzibeqlbwmqerkqvorioeornedysqbtnjiybqovgecsohpgrylppwtercxeenovetiltytoldzwjbrqibnjlgxapohvmtrnxyjfhcadvnvdsjskcszucyctnnevlsqtrlxronbtpqqogquhfeykpgumdlcswcocffzxsgtjfmxzwfhrmmjusjpxicqqwweugxpzxzwqhdrpgtuebdwdbiirxzunvryhcfabugimifaucznrbmuhsdswpepwdpvnbakleeqshnikuljwlrorzzzpbzvrlifrsdwwkmnyjoigfcmzkukhjfzmqxebdsyfhwtqyetuqvnefwfmdkmzggeqhqfgkkyiybjeqznvrhcoulypctjslphyqsanrygdhvkwgiyqgnflrvvtsxzjpxmwhbfojjguyttyuetcxpyukkkoxrhbeemjwwuzofmmrygvktxhjzadlovhmyocfxjfsruhfqjrncolzoqehuhyqmoqmdbplbscjknlxryuxwmifhlxvguknisuhmbcaclmfgteebbypcyemqimolnznhwcktjqzwsfulapbkmmgkgtnqotffjegxwvcvunohfqgczmalhhlizpidqkeaoyglwxqkrppytcscxmbbcpfmktxfynayzfcqmyalxuocgvvawgigxlfonotrxjfuhfduexixsaihpfdnanqtiftvskqwhkobpaceorxrljstbyeehummkxxhqptixtdkaueippjueidlhychhacsrgadxhcaonclmrgnnmxddumcdscyhijigcewbvvulyzohfdvqbcphgoqqcxvskpwwnmnqmldowiijxretntlrdlodstbryjpnfcavipexdlunwycbemgkrgupbgycootkgydalojqtsbxatberwdjptfdtnvqkahyihiazmtdrzhbggyiamowpgcmydcktszykvkgxlztrfgdaajqngcsvehzyjwjqrymwqvznsphstowbgvwirtngdjevqbdacxngapsvercnjxcobqhmpgpwfkrowlpgirvzpmtsqcxjmakhqzsvplidhsdguisbikpcahxebtucrcpsopzvlpsqrrlkteeiavjyqvapkktbzdgtcbgjiiocenzgytqfdbzxjqualawzigagsknlsgbztvsmspesbohoprpguetopmcwkokxqghovnelfgflgphoighgssqlteiwyyezmyslzgveyycbhobgzgruvyqxwgqspakymawjxvonsexnqrxbmnplvaqaznomerdklcgadxoyvpofrpkirfcjfooowlovnjxkyuohzpjnxxwtjhganlqcdpzbleralupwfnbybznvefwhnlttfyhnoxwwrpyftbggpruwsppjxblppxctoyhltffockgyskdwfgopehzdljxmlhtrlgjdchsikwkaksezbeyzbncjduqroxyatfhldibqifgicahwmahdhofcppurvtezsqchxslnsqqylmfahlavfrivmezixtxicieovcsajdfjmkqwaqdbelswwdqqzjyefhxgmzlzidnkovrrfqoytizhppwdtlybtvfogwuxqjayelbielflelmorpjxbotpyjjhgwweknojesyghbxaycjoqoyqjpogwbxdjtexztsbiynquxhpmwkikoftlxvnlpqyqcublehyotrncuorczsehnqqnxrntjkztwhlfrqouvzewqyonorfummfzsbkbwlzrasscasdzccymjuwrjxpyaosdnxwrjoehphfrdxplpnesamtronxdiktamhzbhskhjwsfxcynnpvjrunkocyiecqtkkvfuxhzoxbmskrclogrxwwwkfqqmkkxejryczrihzqoptqozfddslsgrwfbtajgddevyexzecjlcyyyjgmacjludzolcalapyizcfjqeizzuijrfuxuotyafemhqxbivcnfesumcgqlcauqivxxtftxxfyhxqkaspzxeuhaazizwpvcjledbrenveqtyclyjnfnyoarrnbwssphmeuptwvvvcziixegexyyitgsmjjcsnnmoppqojgpdssotqdyyxwrnwigrxhngekunrmjjzecbgjqbxtkyjrzbpgbhuuhbhwrecgcsxzshdjoxcktoddxywtznuqavthodgdqdqmjlxquhyezgebxmnjdheqjwvpgghbifrzflaltfdiyevkzhpgvjrioxvievxylgqzwffaqdqgmpludcgzveusclpjcqwqrawueyqzwcjltgdszrdygzrxuicmawhaghtwduafygnwuxdsbjbrdqdyakslcsunxswudanuwkrkhviyajmwmpoihqkibyrodnmixdjtbhjbzjaskdsfarvuzyxjoxhhfaikgilmsxikjbnywcyrahftpbxckhhomjmsyynksoyeryvzybubbiihahqnnzjgqgrfzvrixlszqsvxtlcthadkhuxjzmaigewvaagicqlegxvlwvfzydebuwxofaxkvljzoxvbipuhzamoncjitetsnvywzwryeuqupvrudgrwlrutxyumwxecgyvkuwwalluoqqohpldrukzvjbenizoxcgvlzatvptoccxgoxzcejeyocapeumciacljnnxwtqsnkfwjugnfohbqupowgmhnsjhwtwmjrqqawyrrbmkucrpivillwjvxaonwnkkkdxqffopzyfayzjaypzjhjstrylngdhwizzgeuogtzmdjmfnkjxirsnfxctbgizcnsqcuvbazqrlqbtuycrxjmyscfiftbxtzahfuazwffcexwzsrykimcsmsysgjukybmwmuahbpezqvllznjpoffliuphwaqsdtpfqaqlmyhnwzxidllbafsnjmyaijcjedpjeddakicylmaflearcdmfrznkwhtsbyobyduytbdaymohadykujrhmkenomcphstuhxcndcujwdtkdzgpkrmalnxiuoqlvlyntmdygewbuqinouxrazqiiwkfnntflcdujqzbpcaiyjpurtcraxtjhkfdodtxbdbepmrmwheogxmcskcjxhschamrsmxrzahtdurdebfmctdankssnpzsvbrmfumboqmcfgwzwjinfmiqymnzhxuxebftnyutosuhtoicopcifvfvfprhczbjrwfuxvmzdynzasqgdjcsrspfvnpbwgkuofjloxxtfvglvyeczasnyoxquebyaupyhilchbtuhzargkotxpmtcewcbmnzkexpkxoponqrbzbcvyhtnkmxgzdpitzaljgtfuzltyfxqvnznqpxmliqjubkzgwqgoltqntjlwmelvplbgljojrfimuurvwmcfibrqaedobcbjizwjmqxtgqwlwnpbhvsbeawqxoipzlokrzroibgryvqukmtafqhqqnrfkdnyexmfibltjczqvviwmwhofazjqyvhjwjiqngtonratdrfghqovddteejgnixrtawttkgdxnxhlcbxedmsipijtlehdixatqhgskwagqzgvoralqataxztiuxmjdzurnevgojftcdmcfrcvihugkutfljnjgnajbtydmfxqnqllstwqugtmxfsjelqjqvfvlegdomygjqjehmvmglowbislmfuihsybxuwnqgzuuabexpnqkgvjtinxacdcxhyhslddhflxrwaspzsetsvbrtzqoupmiwnehojxhrpfkyoxxiklxjpzhbtyjoejdeeuelquhstvqrwtnlsurdyitlchvxrbxhljzbryehtmqttcodrpantdsqjneddylcmdzbotuyqnqbzipdyxzappcfqpsykzzfvtjzurnetoslorhpzcetqrmbshuecdjyobzcsvzpeqbxwslzqrvcpehqtchirchqzeetiyqydatdtdwsvvcilwpexkhetlkmoynknxsicrmqcnpsoekqbapvuioeqdfnpajmdvjennzfnghnadcebjnvebhhiakqyshodzmipspylgtqcipabyqyrzkkbqfheacculvfekttoefqqhbqxvbhfvsfrjqasdvqvlcafjxhjowbrnoblyfiuksvizrdytobrbojypgdhgnbjcbrdryxdqgywuulqdbwhxcxobkmznhfhrvplugwekgnlkzfyskjqdcsxqcygqhqulgnnidistiekrdiawvphicordpkkpkalcbnxetjazgyzladgvnvpoqhbghbvueejrbzxypmugxuetscgzdvsuavypkgascriidvyefjpfxmlvnnvaswcpjqmagwzxnkquaefxcsmqhttnytunjhxbkvilplbrijqzyevpxbxkwpzhtacbefvtzpwagndspeukxfhnmrzxnxmkposnkhgfkhwqdubenplrqwrgpavimdetagrvoyenkdozucmygmokhlocijhtwxwzqdcwhmpmqllvejowpmijkbtebwvogyehnpebiasrpxnsfqdztmkmpxqhgwnacucdfewwnjdzoeebpepkhfmxoxovxpsabjllnpxnlvsoaxvxsdyungcpvegqmafnkzfnuwyvquhkrypkwjjrjnnmekolbokszcqsgjskerwytflfqqtfiidkz");
        print(res);
        return 0;
    }
#endif
