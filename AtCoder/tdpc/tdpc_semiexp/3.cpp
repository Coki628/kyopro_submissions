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

    // F = (x-x^K)/(1-x)
    FPS<mint> F(N+1);
    F[1] = 1;
    F[K] = -1;
    F /= SFPS<mint>{{0, 1}, {1, -1}};
    // G = x/(1-x)
    FPS<mint> G(N+1);
    G[1] = 1;
    G /= SFPS<mint>{{0, 1}, {1, -1}};
    // F/(1-FG)
    FPS<mint> ans(N+1);
    ans += 1;
    ans *= F;
    ans.shrink(N+1);
    FPS<mint> tmp(N+1);
    tmp += 1;
    tmp -= F*G;
    tmp.shrink(N+1);
    ans *= tmp.inv();
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
