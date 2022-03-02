/*
参考：https://opt-cp.com/fps-problem-list/
・FPS演習
・式変形のお気持ちはほぼoptさんの記事に。
　個別の遷移じゃなくて「いくつか連続して止まること」と「いくつか連続してまらないこと」
　を1つの遷移みたいに解釈するのが、これは知らなきゃ思いつけないよなーって感じ。
　立式できたら、無限和みたいな1/(1-x)の形に落とせるように式変形する。
　で、この2つの遷移を交互に当てる行為も無限にやるとして1/(1-x)の形に落とす。
　さてこの後、遷移を当てる初期値の列は何にすればいいのか悩んだ。
　最初x[1] = 1にしてたら合わなくて、x[0] = 1で答えがx[N]としたら合った。
　駅1から駅Nに行くのにこれだと1回多くない？って思ったんだけど、
　「無」から駅1に遷移するところも上記の式に織り込んでるから、
　「無」にあたるような、乗算の単位元になる「1=x^0」が初期値でいいんだね。
・で、これはTLE。多項式乗算でNが100万あるとやっぱきついぽい。。
・さて、optさんも言及してるけど、ここでもうひと変形必要。
　WolframAlphaに ((x-x^k)/(1-x))/(1-((x-x^k)/(1-x))*(x/(1-x))) とか投げると、
　((x-1)(x^k-x))/(x^(k+1)-2x+1) みたいに変形してくれる。
　これでF*Gみたいなまともな多項式乗算をしなくて済むので、通る。
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
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;

    // (x-1)(x^k-x)
    FPS<mint> ans(N+1);
    ans[K] = 1;
    ans[1] = -1;
    ans *= SFPS<mint>{{0, -1}, {1, 1}};
    // x^(k+1)-2x+1
    ans /= SFPS<mint>{{0, 1}, {1, -2}, {K+1, 1}};
    print(ans[N]);
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
