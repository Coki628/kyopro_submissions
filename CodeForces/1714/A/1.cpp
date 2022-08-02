/*
・きっちり自力AC！
・制約小さいのでループ回した。setに詰めといて当たるまでやる。
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

void solve() {
    ll N, sh, sm;
    cin >> N >> sh >> sm;

    HashSet<pll> se;
    rep(i, N) {
        ll h, m;
        cin >> h >> m;
        se.insert({h, m});
    }
    
    ll ch = sh, cm = sm;
    ll cnt = 0;
    while (not se.count({ch, cm})) {
        cm++;
        if (cm == 60) {
            cm = 0;
            ch++;
            if (ch == 24) {
                ch = 0;
            }
        }
        cnt++;
    }
    auto [th, tm] = divmod(cnt, 60LL);
    print(mkp(th, tm));
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
