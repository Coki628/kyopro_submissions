/*
・自力AC！
・ロリハでぶん殴った。
・なんかtitiaさんがUFで解いてたらしい。全然見えなかった…。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    RollingHash rh;
    auto table = rh.build(S);
    set<ull> se;
    rep(i, N - 2 + 1) {
        ll j = i + 2;
        auto h1 = rh.query(table, 0, i);
        auto h2 = rh.query(table, j, N);
        auto h = rh.combine(h1, h2, N - j);
        se.insert(h);
    }
    print(se.size());
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
