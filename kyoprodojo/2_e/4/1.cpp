/*
・自力AC！やったね、嬉しい。
・主客転倒、数え上げDP、BM
・まず、1つの列の操作回数について考えると「ceil(01の切り替え回数, 2)」
　でよさそうな感じになる。しかしこれを全通りの列について見るのは当然無理なので、
　1つ1つの要素に注目して寄与で考えていく。割る2はとりあえず置いておいて、
　01の切り替え回数を全体で数えられないか検討する。
・切り替えが発生するのは直前の要素と今見ている要素が異なる時で、
　これは0/1で状態を持てる。切り替え回数とは別に、
　その状態になる通り数も数えておくと、切り替えの時に、
　その状態にある通り数を足し込むみたいな感じで切り替え回数も数えられる。
・これで切り替え回数は数えられたので、次は割る2切り上げをどうするか検討する。
　この切り上げが必要になるのは、最初の要素と最後の要素が異なる列である。
　なのでさっきのDPに先頭要素がどっちだったかも0/1で持たせておく。
・これで切り上げが必要な通り数が分かった。1つのパターンで
　割る2を切り上げるのに必要なのは+1することで、これを全てのパターンでやるので、
　結局通り数の分ちょうどを足せばいいことになる。
・全てのパターンが割る2で割り切れる状態になったので、後は割る2するだけ。
　多分状態毎に個別に割る2しても大丈夫だけど、MOD除算は計算量logがかかるし、
　最後にやっても変わらないので、全部足し込んでからまとめて割る2するようにした。
・さて、これが文字列S単体での話。実際はこれをK回繰り返すみたいにしないといけない。
　解説でtatyamさんが行列累乗できるよって書いてて、確かにそうかもとなったけど、
　自力ではBMを信じて殴りに行った。まあこれでも通ってよかった。
　最初50回でやってTLEして、30回にしたらなんとかAC。
　それにしても30*10万*2*2*2=2400万のDPがTLEでMLEとかおかしくない？って思ったけど、
　3次元vector2つを生配列にしたら爆速になった。1.33秒→0.17秒、メモリ894MB→98MB。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/math/FormalPowerSeries.hpp"
#include "../../../_lib/cpp/_src/math/BM.hpp"

const ll K2 = 30;
// dp1[i][j][k] := i番目まで見て、最初の要素の0/1がj、直前の要素の0/1がkの時の01を切り替えた回数
// dp2[i][j][k] := i番目まで見て、最初の要素の0/1がj、直前の要素の0/1がkの時の通り数
mint dp1[K2*100000+7][2][2], dp2[K2*100000+7][2][2];

void solve() {
    string S;
    cin >> S;
    ll N = S.size();
    ll K;
    cin >> K;

    FPS<mint> fps = {0};
    ll N2 = N*K2;
    // auto dp1 = list3d<mint>(N2+1, 2, 2, 0);
    // auto dp2 = list3d<mint>(N2+1, 2, 2, 0);
    if (S[0] != '0') {
        dp2[1][1][1] = 1;
    }
    if (S[0] != '1') {
        dp2[1][0][0] = 1;
    }
    rep(i, 1, N2) {
        rep(j, 2) {
            rep(k, 2) {
                rep(kk, 2) {
                    if (S[i%N] == '0' and kk == 1) continue;
                    if (S[i%N] == '1' and kk == 0) continue;
                    dp2[i+1][j][kk] += dp2[i][j][k];
                    if (k == kk) {
                        dp1[i+1][j][kk] += dp1[i][j][k];
                    } else {
                        dp1[i+1][j][kk] += dp1[i][j][k]+dp2[i][j][k];
                    }
                }
            }
        }
    }
    rep(i, N, N2+1, N) {
        mint cnt = 0;
        rep(j, 2) {
            rep(k, 2) {
                if (j == k) {
                    cnt += dp1[i][j][k];
                } else {
                    cnt += dp1[i][j][k]+dp2[i][j][k];
                }
            }
        }
        cnt /= 2;
        fps.eb(cnt);
    }
    auto res = BM(fps, K);
    print(res);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
