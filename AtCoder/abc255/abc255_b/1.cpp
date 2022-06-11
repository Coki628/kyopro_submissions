/*
・Bでにぶたんマジ？実は要らないやつ？って思いながらも、
　考察する時間のがもったいないと思ってにぶたんして通した。
　1000^2の判定を雑に100回回したら1.92秒でTLギリギリ…。
・やっぱりにぶたんは要らなかったそう。
　2乗全探索して、みんなの最小値のうち、最大のものが答え。言われたら確かに。。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "common/bisearch_real.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(K);
    rep(i, K) A[i]--;
    vector<pll> XY;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        XY.eb(x, y);
    }

    ld res = bisearch_min(0, INF, [&](ld x) {
        vector<ll> ok(N);
        for (auto a : A) {
            auto [sx, sy] = XY[a];
            rep(i, N) {
                auto [tx, ty] = XY[i];
                if (hypot(sx-tx, sy-ty) <= x) {
                    ok[i] = true;
                }
            }
        }
        return sum(ok) == N;
    }, 100);
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
