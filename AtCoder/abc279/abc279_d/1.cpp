/*
・きっちり自力AC！
・三分探索
・単調性はなさそうだし、こんなん(制約のでかさ的にも)凸じゃなきゃ無理だろー、
　とほぼ無思考で三分探索へ。なんだけど、y=f(x)でいう所のxは整数だけどyは実数って感じなので、
　整数さぶたんのライブラリを少しいじって無事AC。(上界ミスって1WA。。)
・前にここの戻り値テンプレートにしようか悩んだけど結局やってなかったんだよね…。
　ということで、終了後ライブラリ整備して<ld>って与えれば戻り値側で実数も取れるように改修。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX / 2;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "common/trisearch.hpp"

void solve() {
    ld a, b;
    cin >> a >> b;

    ld g = 1;
    auto [i, val] = trisearch_min<ld>(0, INF, [&](ll x) -> ld {
        return a / sqrt(g+x) + b*x;
    }, 100);
    print(val);
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
