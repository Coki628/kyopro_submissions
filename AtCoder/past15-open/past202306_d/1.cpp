/*
・きっちり自力AC。
・ちょっとゴチャゴチャした設定だが、
　幸いにも制約が全探索を許すので、やる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll a, b, c, d, r;
    cin >> a >> b >> c >> d >> r;

    ll T = 3000;
    vector<int> covered(T);
    rep(t, a, a + r) {
        covered[t] = true;
    }
    bool changed = false;
    rep(t, T) {
        if (t == b) {
            changed = true;
        }
        if (t % d == 0) {
            if (changed) {
                rep(t, c, c + r) {
                    covered[t] = true;
                }
                changed = false;
            }
        }
        if (c <= t and t < c + r) {
            if (not covered[t]) {
                No();
                return;
            }
        }
    }
    Yes();
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
