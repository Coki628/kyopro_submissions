/*
・きっちり自力AC！
・適切に優先度付けしてソートすればOK。
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

void solve() {
    ll N, M, H;
    cin >> N >> M >> H;
    vector<array<ll, 3>> vec;
    rep(i, N) {
        ll score = 0, pena = 0;
        vector<ll> cur(M);
        cin >> cur;
        sort(ALL(cur));
        ll t = 0;
        rep(j, M) {
            t += cur[j];
            if (t > H) break;
            score++;
            pena += t;
        }
        vec.pb({-score, pena, i});
    }
    sort(ALL(vec));
    rep(i, N) {
        if (vec[i][2] == 0) {
            print(i + 1);
            return;
        }
    }
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
