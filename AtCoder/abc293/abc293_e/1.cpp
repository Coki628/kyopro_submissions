/*
・なんとか自力AC！危なかった…。
・任意MOD、BM
・WolframAlphaに式を突っ込んでも有力な手掛かりは得られず、
　しばらく右往左往した後いったんスキップ。
　G通してから帰ってきて、きれいな式だしいけないかなーって、
　ダメ元でBMに突っ込んだら無事AC。
　任意MODにBM使ったの多分初めてなので、ちゃんと動くのが確認できたのは収穫かな。
　(少なくとも内部で割り算はしてないんだろう。)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;
#include "math/FormalPowerSeries.hpp"
#include "math/BM.hpp"

void solve() {
    ll A, X, M;
    cin >> A >> X >> M;
    mint::set_mod(M);

    ll N = 100;
    FPS<mint> F(N);
    F[0] = 1;
    rep(i, 1, N) {
        F[i] = F[i - 1] + pow(A, i, M);
    }
    auto ans = BM(F, X - 1);
    print(ans);
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
